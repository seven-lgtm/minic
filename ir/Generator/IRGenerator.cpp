///
/// @file IRGenerator.cpp
/// @brief AST遍历产生线性IR的源文件
/// @author zenglj (zenglj@live.com)
/// @version 1.1
/// @date 2024-11-23
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-09-29 <td>1.0     <td>zenglj  <td>新建
/// <tr><td>2024-11-23 <td>1.1     <td>zenglj  <td>表达式版增强
/// </table>
///
#include <cstdint>
#include <cstdio>
#include <unordered_map>
#include <vector>
#include <iostream>
#include <stack>

#include "AST.h"
#include "Common.h"
#include "Function.h"
#include "IRCode.h"
#include "IRGenerator.h"
#include "Module.h"
#include "EntryInstruction.h"
#include "LabelInstruction.h"
#include "ExitInstruction.h"
#include "FuncCallInstruction.h"
#include "BinaryInstruction.h"
#include "MoveInstruction.h"
#include "GotoInstruction.h"
#include "MinusInstruction.h"
#include "BranchInstruction.h"
#include "ArgInstruction.h"
#include "PointerType.h"
#include "ScopeStack.h"
#include "LoadInstruction.h"
#include "StoreInstruction.h"

/// @brief 构造函数
/// @param _root AST的根
/// @param _module 符号表
IRGenerator::IRGenerator(ast_node * _root, Module * _module) : root(_root), module(_module)
{
    /* 叶子节点 */
    ast2ir_handlers[ast_operator_type::AST_OP_LEAF_LITERAL_UINT] = &IRGenerator::ir_leaf_node_uint;
    ast2ir_handlers[ast_operator_type::AST_OP_LEAF_VAR_ID] = &IRGenerator::ir_leaf_node_var_id;
    ast2ir_handlers[ast_operator_type::AST_OP_LEAF_TYPE] = &IRGenerator::ir_leaf_node_type;

    /* 表达式运算， 加减乘除  +- * / %   取负 neg */   
    ast2ir_handlers[ast_operator_type::AST_OP_SUB] = &IRGenerator::ir_sub;
    ast2ir_handlers[ast_operator_type::AST_OP_ADD] = &IRGenerator::ir_add;
    ast2ir_handlers[ast_operator_type::AST_OP_MUL] = &IRGenerator::ir_mul;
    ast2ir_handlers[ast_operator_type::AST_OP_DIV] = &IRGenerator::ir_div;
    ast2ir_handlers[ast_operator_type::AST_OP_DIV] = &IRGenerator::ir_div;
    ast2ir_handlers[ast_operator_type::AST_OP_MOD] = &IRGenerator::ir_mod;
    ast2ir_handlers[ast_operator_type::AST_OP_NEG] = &IRGenerator::ir_neg;

    /* 关系运算  < <= > >= == != */
    ast2ir_handlers[ast_operator_type::AST_OP_LT] = &IRGenerator::ir_lt;
    ast2ir_handlers[ast_operator_type::AST_OP_LE] = &IRGenerator::ir_le;
    ast2ir_handlers[ast_operator_type::AST_OP_GT] = &IRGenerator::ir_gt;
    ast2ir_handlers[ast_operator_type::AST_OP_GE] = &IRGenerator::ir_ge;
    ast2ir_handlers[ast_operator_type::AST_OP_EQ] = &IRGenerator::ir_eq;
    ast2ir_handlers[ast_operator_type::AST_OP_NE] = &IRGenerator::ir_ne;

    /* 逻辑运算  && || ! */
    ast2ir_handlers[ast_operator_type::AST_OP_AND] = &IRGenerator::ir_and;
    ast2ir_handlers[ast_operator_type::AST_OP_OR] = &IRGenerator::ir_or;
    ast2ir_handlers[ast_operator_type::AST_OP_NOT] = &IRGenerator::ir_not;
    
	/* 语句 */
    ast2ir_handlers[ast_operator_type::AST_OP_ASSIGN] = &IRGenerator::ir_assign;
    ast2ir_handlers[ast_operator_type::AST_OP_RETURN] = &IRGenerator::ir_return;
    
	/* if/ifelse语句 */
    ast2ir_handlers[ast_operator_type::AST_OP_IF] = &IRGenerator::ir_if;
    ast2ir_handlers[ast_operator_type::AST_OP_IF_ELSE] = &IRGenerator::ir_if_else;

    /* while break continue for 语句 */
    ast2ir_handlers[ast_operator_type::AST_OP_WHILE] = &IRGenerator::ir_while;
    ast2ir_handlers[ast_operator_type::AST_OP_BREAK] = &IRGenerator::ir_break;
    ast2ir_handlers[ast_operator_type::AST_OP_CONTINUE] = &IRGenerator::ir_continue;
    ast2ir_handlers[ast_operator_type::AST_OP_FOR] = &IRGenerator::ir_for;

    /* 自增自减运算符 */
    ast2ir_handlers[ast_operator_type::AST_OP_PRE_INC] = &IRGenerator::ir_pre_inc;
    ast2ir_handlers[ast_operator_type::AST_OP_PRE_DEC] = &IRGenerator::ir_pre_dec;
    ast2ir_handlers[ast_operator_type::AST_OP_POST_INC] = &IRGenerator::ir_post_inc;
    ast2ir_handlers[ast_operator_type::AST_OP_POST_DEC] = &IRGenerator::ir_post_dec;

    /* 函数调用 */
    ast2ir_handlers[ast_operator_type::AST_OP_FUNC_CALL] = &IRGenerator::ir_function_call;

    /* 函数定义 */
    ast2ir_handlers[ast_operator_type::AST_OP_FUNC_DEF] = &IRGenerator::ir_function_define;
    ast2ir_handlers[ast_operator_type::AST_OP_FUNC_FORMAL_PARAMS] = &IRGenerator::ir_function_formal_params;

    /* 变量定义语句 */
    ast2ir_handlers[ast_operator_type::AST_OP_DECL_STMT] = &IRGenerator::ir_declare_statment;
    ast2ir_handlers[ast_operator_type::AST_OP_VAR_DECL] = &IRGenerator::ir_variable_declare;

        /*数组相关*/
    ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_INDEX] = &IRGenerator::ir_array_index;
   

    /* 语句块 */
    ast2ir_handlers[ast_operator_type::AST_OP_BLOCK] = &IRGenerator::ir_block;

    /* 编译单元 */
    ast2ir_handlers[ast_operator_type::AST_OP_COMPILE_UNIT] = &IRGenerator::ir_compile_unit;
}

/// @brief 遍历抽象语法树产生线性IR，保存到IRCode中
/// @param root 抽象语法树
/// @param IRCode 线性IR
/// @return true: 成功 false: 失败
bool IRGenerator::run()
{
    ast_node * node;

    // 从根节点进行遍历
    node = ir_visit_ast_node(root);

    return node != nullptr;
}

/// @brief 根据AST的节点运算符查找对应的翻译函数并执行翻译动作
/// @param node AST节点
/// @return 成功返回node节点，否则返回nullptr
ast_node * IRGenerator::ir_visit_ast_node(ast_node * node)
{
    // 空节点
    if (nullptr == node) {
        return nullptr;
    }

    bool result;

    std::unordered_map<ast_operator_type, ast2ir_handler_t>::const_iterator pIter;
    pIter = ast2ir_handlers.find(node->node_type);
    if (pIter == ast2ir_handlers.end()) {
        // 没有找到，则说明当前不支持
        result = (this->ir_default)(node);
    } else {
        result = (this->*(pIter->second))(node);
    }

    if (!result) {
        // 语义解析错误，则出错返回
        node = nullptr;
    }

    return node;
}

/// @brief 未知节点类型的节点处理
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_default(ast_node * node)
{
    // 未知的节点
    printf("Unkown node(%d)\n", (int) node->node_type);
    return true;
}

/// @brief 编译单元AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败

bool IRGenerator::ir_compile_unit(ast_node * node)
{
    module->setCurrentFunction(nullptr);

    for (auto son: node->sons) { //son:decl-stmt  fuc-def
        if (son->node_type == ast_operator_type::AST_OP_DECL_STMT) { // 处理全局变量声明

            for (auto & decl: son->sons) { //son:var-decl
                ast_node * type_node = decl->sons[0];//i32
                ast_node * id_node = decl->sons[1];//a OR a=9 OR 数组节点
				ast_node*  id_node_son=nullptr; //a=9 时候的a

                Value * initValue = nullptr;  // 处理带初始化的全局变量
                if (id_node->node_type == ast_operator_type::AST_OP_ASSIGN) {//全局变量a=9的情况

                    ast_node * init_expr = id_node->sons[1]; // 处理初始化表达式
					id_node_son =id_node->sons[0]; //a=9的那个a
                    ast_node * init_node = ir_visit_ast_node(init_expr);

                    if (!init_node) {
                        minic_log(LOG_ERROR, "全局变量初始化表达式错误");
                        return false;
                    }

                    // 初始化值必须是常量
                    if (dynamic_cast<ConstInt *>(init_node->val)) {
                        initValue = init_node->val;
                    } 

                    GlobalVariable * globalVar = module->newGlobalVariable(type_node->type, id_node_son->name, initValue);
                    if (!globalVar) {
                        return false;
                    }
                } else if (id_node->node_type == ast_operator_type::AST_OP_ARRAY_DECL) {// 这里处理数组
                        int total_size = 4; // int类型大小
                        for (auto dim: id_node->array_dims) {
                            total_size *= dim;
                        }
                        GlobalVariable * globalVar =module->newGlobalVariable(type_node->type, id_node->sons[0]->name);
                        globalVar->setTotalSize(total_size);
                        globalVar->setArrayDimensions(id_node->array_dims);

                    } else { //全局变量：a 的情况
                        GlobalVariable * globalVar =
                            module->newGlobalVariable(type_node->type, id_node->name, initValue);
                        if (!globalVar) {
                            return false;
                        }
                    }
            }
        } else if (son->node_type == ast_operator_type::AST_OP_FUNC_DEF) {
            // 处理函数定义（保持不变）
            ast_node * func_node = ir_visit_ast_node(son);
            if (!func_node) {
                return false;
            }
        }
    }

    return true;
}


/// @brief 函数定义AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败

bool IRGenerator::ir_function_define(ast_node * node)
{
    bool result;

    // 创建一个函数，用于当前函数处理
    if (module->getCurrentFunction()) {
        // 函数中嵌套定义函数，这是不允许的，错误退出
        // TODO 自行追加语义错误处理
        return false;
    }

    // 函数定义的AST包含四个孩子
    // 第一个孩子：函数返回类型 void /int 
    // 第二个孩子：函数名字 main sum...
    // 第三个孩子：形参列表 
    // 第四个孩子：函数体即block
    ast_node * type_node = node->sons[0];  //函数的返回值类型
    ast_node * name_node = node->sons[1]; //函数名
    ast_node * param_node = node->sons[2]; //形参
    ast_node * block_node = node->sons[3]; //函数体block

    // 1. 创建一个新的函数定义 
    Function * newFunc = module->newFunction(name_node->name, type_node->type);
    if (!newFunc) {
        // 新定义的函数已经存在，则失败返回。
        // TODO 自行追加语义错误处理
        return false;
    }

    // 当前函数设置有效，变更为当前的函数
    module->setCurrentFunction(newFunc);

    // 进入函数的作用域
    module->enterScope();

    // 获取函数的IR代码列表，用于后面追加指令用，注意这里用的是引用传值
    InterCode & irCode = newFunc->getInterCode();

    // 2. 这里也可增加一个函数入口Label指令，便于后续基本块划分
    irCode.addInst(new LabelInstruction(newFunc));

    //  3. 创建并加入Entry入口指令   entry
    irCode.addInst(new EntryInstruction(newFunc));

    // 创建出口指令并不加入出口指令，等函数内的指令处理完毕后加入出口指令
    LabelInstruction * exitLabelInst = new LabelInstruction(newFunc); //exitLabelInst 要处理一下当函数返回值是void的时候

    // 函数出口指令保存到函数信息中，因为在语义分析函数体时return语句需要跳转到函数尾部，需要这个label指令
    newFunc->setExitLabel(exitLabelInst);

    // 4. 遍历形参，生成IR
    result = ir_function_formal_params(param_node);
    if (!result) {
        // 形参解析失败
        // TODO 自行追加语义错误处理
        return false;
    }
    node->blockInsts.addInst(param_node->blockInsts); //addInst：形式参数的ir

    //  5.  处理 返回值的问题
	// 新建一个Value，用于保存函数的返回值，如果没有返回值可不用申请
    LocalVariable * retValue = nullptr;

    if (!type_node->type->isVoidType()) {

        // 保存函数返回值变量到函数信息中，在return语句翻译时需要设置值到这个变量中
       retValue = static_cast<LocalVariable *>(module->newVarValue(type_node->type));
    }
     newFunc->setReturnValue(retValue);
    // 这里最好设置返回值变量的初值为0，以便在没有返回值时能够返回0
     if (newFunc->getName() == "main" && newFunc->getReturnType() == IntegerType::getTypeInt()) {
         ConstInt * zero = module->newConstInt(0);
         MoveInstruction * initMov = new MoveInstruction(newFunc, retValue, zero);
         newFunc->getInterCode().addInst(initMov);
     } // main函数的特殊处理 以及 返回值变量设置初值为0

    // 函数内已经进入作用域，内部不再需要做变量的作用域管理
    block_node->needScope = false;

    // 6.  遍历block 生成相应的IR


	// 注意这里对形式参数的操作： 要对局部变量的操作 而不是 临时变量

    result = ir_block(block_node);
    if (!result) {
        // block解析失败
        // TODO 自行追加语义错误处理
        return false;
    }

    node->blockInsts.addInst(block_node->blockInsts); // add block节点的IR到当前node

    // 此时，所有指令都加入到当前函数中，也就是node->blockInsts
  

	// 7. 后续操作
    // node节点的指令移动到函数的IR指令列表中
    irCode.addInst(node->blockInsts);

    // 8. 添加函数出口Label指令，主要用于return语句跳转到这里进行函数的退出
    irCode.addInst(exitLabelInst);

    // 9. 函数出口指令
   irCode.addInst(new ExitInstruction(newFunc, retValue));

    // 恢复成外部函数
    module->setCurrentFunction(nullptr);

    // 退出函数的作用域
    module->leaveScope();

    return true;
}
  

/// @brief 形式参数AST节点：formal_params翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_function_formal_params(ast_node * node)
{
    
    if (!node || node->sons.empty()) {
        return true;
    }

    // 获取当前函数
    Function * currentFunc = module->getCurrentFunction();
    if (!currentFunc) {
        return false;
    }
    auto & params = currentFunc->getParams();

    // 遍历所有形参声明
    for (auto son: node->sons) { // 形参声明节点 (AST_OP_VAR_DECL)

        ast_node * param_decl = son;

        // 获取类型节点和标识符节点
        ast_node * type_node = param_decl->sons[0];
        ast_node * id_node = param_decl->sons[1];
        if (id_node->node_type == ast_operator_type::AST_OP_ARRAY_DECL){ //处理数组作为形参的情况
            FormalParam * formalParam = new FormalParam(type_node->type, id_node->sons[0]->name);
			//formalParam->isFormalArr=true;
            formalParam->setArrayDimensions(id_node->array_dims);
            params.push_back(formalParam);
            LocalVariable * paramVar =
                currentFunc->newLocalVarValue(type_node->type, id_node->sons[0]->name, module->getScopeLevel());
           // paramVar->isFormalArr = true;
            paramVar->setArrayDimensions(id_node->array_dims);
            module->getScopeStack()->insertValue(paramVar);

            MoveInstruction * movInst = new MoveInstruction(currentFunc,
                                                            paramVar,   // 目标：局部变量
                                                            formalParam // 源：临时变量（由调用者设置）
            );

            node->blockInsts.addInst(movInst);
        }else{ //处理平常情况

           
        // 1. 将形参添加到函数的形参列表
        FormalParam * formalParam = new FormalParam(type_node->type, id_node->name);
        params.push_back(formalParam);

        // 2. 创建局部变量作为真实的形参
        LocalVariable * paramVar = 
            currentFunc->newLocalVarValue(type_node->type, id_node->name, module->getScopeLevel());

        module->getScopeStack()->insertValue(paramVar);

        // 3. 将形参添加到函数的形参列表
      
         // 5. 生成赋值指令：将临时变量值赋给局部变量
         // 这样函数体就可以使用形参的值了
        MoveInstruction * movInst = new MoveInstruction(currentFunc,
                                                        paramVar,   // 目标：局部变量
                                                        formalParam // 源：临时变量（由调用者设置）
        );

        // 6. 添加到IR指令列表（在Entry指令之后）
         node->blockInsts.addInst(movInst);
	}
    }

    return true;
}
/// @brief 函数调用AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败

bool IRGenerator::ir_function_call(ast_node * node)
{
    std::vector<Value *> realParams;

    // 获取当前正在处理的函数
    Function * currentFunc = module->getCurrentFunction();

    // 函数调用的节点包含两个节点：
    // 第一个节点：函数名节点
    // 第二个节点：实参列表节点

    std::string funcName = node->sons[0]->name; //函数名节点 eg:sum
    int64_t lineno = node->sons[0]->line_no;

    ast_node * paramsNode = node->sons[1]; // 实参列表节点:real-params

    // 根据函数名查找函数，看是否存在。若不存在则出错
    // 这里约定函数必须先定义后使用
    auto calledFunction = module->findFunction(funcName);
    if (nullptr == calledFunction) {
        minic_log(LOG_ERROR, "函数(%s)未定义或声明", funcName.c_str());
        return false;
    }

    // 当前函数存在函数调用
    currentFunc->setExistFuncCall(true);

    // 如果没有孩子，也认为是没有参数
    if (!paramsNode->sons.empty()) { // paramsNode 实际参数列表节点

        int32_t argsCount = (int32_t) paramsNode->sons.size(); //实际参数的个数

        // 当前函数中调用函数实参个数最大值统计，实际上是统计实参传参需在栈中分配的大小
        // 因为目前的语言支持的int和float都是四字节的，只统计个数即可
        if (argsCount > currentFunc->getMaxFuncCallArgCnt()) {
            currentFunc->setMaxFuncCallArgCnt(argsCount);
        }

        // 遍历参数列表，孩子是表达式
        // 这里自左往右计算表达式
        for (auto son: paramsNode->sons) {

            // 遍历Block的每个语句，进行显示或者运算
            ast_node * temp = ir_visit_ast_node(son);
            if (!temp) {
                return false;
            }
            Value * arrayVar = module->findVarValue(temp->val->getName());
            if (arrayVar) {
                // 将维度信息附加到Value中
                std::vector<int> dims;
                dims = arrayVar->getArrayDimensions();
                if (!dims.empty()) {
                    temp->val->setArrayDimensions(dims);
                }
            } //解决形式参数是数组问题

            realParams.push_back(temp->val); //加入实际参数列表

            node->blockInsts.addInst(temp->blockInsts);

        } //计算为孩子节点生成IR
    }

    // TODO 这里请追加函数调用的语义错误检查，这里只进行了函数参数的个数检查等，其它请自行追加。
    if (realParams.size() != calledFunction->getParams().size()) {
        // 函数参数的个数不一致，语义错误
        minic_log(LOG_ERROR, "第%lld行的被调用函数(%s)未定义或声明", (long long) lineno, funcName.c_str());
        return false;
    }

    // 返回调用有返回值，则需要分配临时变量，用于保存函数调用的返回值
    Type * type = calledFunction->getReturnType();

    //生成函数调用指令
    FuncCallInstruction * funcCallInst = new FuncCallInstruction(currentFunc, calledFunction, realParams, type);

    // 函数调用指令加入现在的node
    node->blockInsts.addInst(funcCallInst);

    // 函数调用结果Value保存到node中，可能为空，上层节点可利用这个值
    node->val = funcCallInst;

    return true;
}
/*
bool IRGenerator::ir_function_call(ast_node * node)
{
    std::vector<Value *> realParams;

    // 获取当前正在处理的函数
    Function * currentFunc = module->getCurrentFunction();

    // 函数调用的节点包含两个节点：
    // 第一个节点：函数名节点
    // 第二个节点：实参列表节点

    std::string funcName = node->sons[0]->name; //函数名节点 eg:sum
    int64_t lineno = node->sons[0]->line_no;

    ast_node * paramsNode = node->sons[1]; // 实参列表节点:real-params

    // 根据函数名查找函数，看是否存在。若不存在则出错
    // 这里约定函数必须先定义后使用
    auto calledFunction = module->findFunction(funcName);
    if (nullptr == calledFunction) {
        minic_log(LOG_ERROR, "函数(%s)未定义或声明", funcName.c_str());
        return false;
    }

    // 当前函数存在函数调用
    currentFunc->setExistFuncCall(true);

    // 如果没有孩子，也认为是没有参数
    if (!paramsNode->sons.empty()) { // paramsNode 实际参数列表节点

        int32_t argsCount = (int32_t) paramsNode->sons.size(); //实际参数的个数
        if (argsCount > currentFunc->getMaxFuncCallArgCnt()) {
            currentFunc->setMaxFuncCallArgCnt(argsCount);
        }
        
            // 遍历参数列表，孩子是表达式
            // 这里自左往右计算表达式
            for (auto son: paramsNode->sons) { //
                if (son->node_type == ast_operator_type::AST_OP_ARRAY_INDEX && paramsNode->sons.size() > 11) {
                    ast_node * temp = ir_visit_ast_node(son->sons[0]);
                    if (!temp) {
                        return false;
                    }

                    LocalVariable * paramVar = currentFunc->newLocalVarValue(IntegerType::getTypeInt(),
                                                                             son->sons[0]->name,
                                                                             module->getScopeLevel());
                   // FormalParam * paramVar = new FormalParam(IntegerType::getTypeInt(), son->sons[0]->name);

                    Value * baseArray = module->findVarValue(son->sons[0]->name);
                    if (baseArray) {
                        std::vector<int> dims = baseArray->getArrayDimensions(); // 3 0 1 2:2 2 2

                        // 计算降维后的维度（去掉已索引的维度）
                        int indexedDims = son->sons.size() - 1; // 减去数组名本身 2
                        std::vector<int> remainingDims;
                        //(dims.begin() + indexedDims, dims.end());
                        for (size_t i = static_cast<size_t>(indexedDims); i < dims.size(); i++) {
                            remainingDims.push_back(dims[i]);
                        }
                        paramVar->setArrayDimensions(remainingDims);
                    }
                 //   module->getScopeStack()->insertValue(paramVar);
                    realParams.push_back(paramVar);

                } else {

                    // 遍历Block的每个语句，进行显示或者运算
                    ast_node * temp = ir_visit_ast_node(son);
                    if (!temp) {
                        return false;
                    }
                    Value * arrayVar = module->findVarValue(temp->val->getName());
                    if (arrayVar) {
                        // 将维度信息附加到Value中
                        std::vector<int> dims;
                        dims = arrayVar->getArrayDimensions();
                        if (!dims.empty()) {
                            temp->val->setArrayDimensions(dims);
                        }
                    } //解决形式参数是数组问题

                    realParams.push_back(temp->val); //加入实际参数列表

                    node->blockInsts.addInst(temp->blockInsts);
                }

            } //计算为孩子节点生成IR
        }

    // TODO 这里请追加函数调用的语义错误检查，这里只进行了函数参数的个数检查等，其它请自行追加。
    if (realParams.size() != calledFunction->getParams().size()) {
        // 函数参数的个数不一致，语义错误
        minic_log(LOG_ERROR, "第%lld行的被调用函数(%s)未定义或声明", (long long) lineno, funcName.c_str());
        return false;
    }

    // 返回调用有返回值，则需要分配临时变量，用于保存函数调用的返回值
    Type * type = calledFunction->getReturnType();

    //生成函数调用指令
    FuncCallInstruction * funcCallInst = new FuncCallInstruction(currentFunc, calledFunction, realParams, type);

    // 函数调用指令加入现在的node
    node->blockInsts.addInst(funcCallInst);

    // 函数调用结果Value保存到node中，可能为空，上层节点可利用这个值
    node->val = funcCallInst;

    return true;
}
*/

/// @brief 语句块（含函数体）AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_block(ast_node * node)
{
    // 进入作用域
    if (node->needScope) {
        module->enterScope();
    }

    std::vector<ast_node *>::iterator pIter;
    for (pIter = node->sons.begin(); pIter != node->sons.end(); ++pIter) {

        // 遍历Block的每个语句，进行显示或者运算
        ast_node * temp = ir_visit_ast_node(*pIter);
        if (!temp) {
            return false;
        }

        node->blockInsts.addInst(temp->blockInsts);
    }

    // 离开作用域
    if (node->needScope) {
        module->leaveScope();
    }

    return true;
}

/// @brief 整数加法AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_add(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 加法节点，左结合，先计算左节点，后计算右节点

    // 加法的左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 加法的右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    BinaryInstruction * addInst = new BinaryInstruction(module->getCurrentFunction(),
                                                        IRInstOperator::IRINST_OP_ADD_I,
                                                        left->val,
                                                        right->val,
                                                        IntegerType::getTypeInt());

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(addInst);

    node->val = addInst;

    return true;
}

/// @brief 整数减法AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_sub(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 加法节点，左结合，先计算左节点，后计算右节点

    // 加法的左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 加法的右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    BinaryInstruction * subInst = new BinaryInstruction(module->getCurrentFunction(),
                                                        IRInstOperator::IRINST_OP_SUB_I,
                                                        left->val,
                                                        right->val,
                                                        IntegerType::getTypeInt());

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(subInst);

    node->val = subInst;

    return true;
}

/// @brief 整数乘法AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_mul(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 乘法节点，左结合，先计算左节点，后计算右节点

    // 乘法的左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 乘法的右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    BinaryInstruction * mulInst = new BinaryInstruction(module->getCurrentFunction(),
                                                        IRInstOperator::IRINST_OP_MUL_I,
                                                        left->val,
                                                        right->val,
                                                        IntegerType::getTypeInt());

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(mulInst);

    node->val = mulInst;

    return true;
}

/// @brief 整数除法AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_div(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 除法节点，左结合，先计算左节点，后计算右节点

    // 加法的左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 加法的右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    BinaryInstruction * divInst = new BinaryInstruction(module->getCurrentFunction(),
                                                        IRInstOperator::IRINST_OP_DIV_I,
                                                        left->val,
                                                        right->val,
                                                        IntegerType::getTypeInt());

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(divInst);

    node->val = divInst;

    return true;
}

/// @brief 整数取余AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_mod(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 取余节点，左结合，先计算左节点，后计算右节点

    // 左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    //右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    BinaryInstruction * modInst = new BinaryInstruction(module->getCurrentFunction(),
                                                        IRInstOperator::IRINST_OP_MOD_I,
                                                        left->val,
                                                        right->val,
                                                        IntegerType::getTypeInt());

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(modInst);

    node->val = modInst;

    return true;
}

/// @brief 整数取负AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_neg(ast_node * node)
{
    ast_node * src1_node = node->sons[0];


    // 左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }
	

    MinusInstruction * negInst = new MinusInstruction(module->getCurrentFunction(),
                                                        IRInstOperator::IRINST_OP_NEG_I,
                                                        left->val,
                                                        IntegerType::getTypeInt());

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(negInst);

    node->val = negInst;

    return true;
}


/// @brief 关系运算小于AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_lt(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 小于节点，左结合，先计算左节点，后计算右节点

    // 左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    BinaryInstruction * ltInst = new BinaryInstruction(module->getCurrentFunction(),
                                                       IRInstOperator::IRINST_OP_LT_I,
                                                       left->val,
                                                       right->val,
                                                       IntegerType::getTypeBool());

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(ltInst);

    node->val = ltInst;

    return true;
}

/// @brief 关系运算小于等于AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_le(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 小于节点，左结合，先计算左节点，后计算右节点

    // 左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    BinaryInstruction * leInst = new BinaryInstruction(module->getCurrentFunction(),
                                                       IRInstOperator::IRINST_OP_LE_I,
                                                       left->val,
                                                       right->val,
                                                       IntegerType::getTypeBool());

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(leInst);

    node->val = leInst;

    return true;
}

/// @brief 关系运算大于AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_gt(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 小于节点，左结合，先计算左节点，后计算右节点

    // 左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    BinaryInstruction * gtInst = new BinaryInstruction(module->getCurrentFunction(),
                                                       IRInstOperator::IRINST_OP_GT_I,
                                                       left->val,
                                                       right->val,
                                                       IntegerType::getTypeBool());

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(gtInst);

    node->val = gtInst;

    return true;
}

/// @brief 关系运算等于AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_eq(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 小于节点，左结合，先计算左节点，后计算右节点

    // 左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    BinaryInstruction * eqInst = new BinaryInstruction(module->getCurrentFunction(),
                                                       IRInstOperator::IRINST_OP_EQ_I,
                                                       left->val,
                                                       right->val,
                                                       IntegerType::getTypeBool());

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(eqInst);

    node->val = eqInst;

    return true;
}

/// @brief 关系运算不等于AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_ne(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 小于节点，左结合，先计算左节点，后计算右节点

    // 左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    BinaryInstruction * neInst = new BinaryInstruction(module->getCurrentFunction(),
                                                       IRInstOperator::IRINST_OP_NE_I,
                                                       left->val,
                                                       right->val,
                                                       IntegerType::getTypeBool());

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(neInst);

    node->val = neInst;

    return true;
}

/// @brief 关系运算大于等于AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_ge(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // 小于节点，左结合，先计算左节点，后计算右节点

    // 左边操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left) {
        // 某个变量没有定值
        return false;
    }

    // 右边操作数
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理

    BinaryInstruction * geInst = new BinaryInstruction(module->getCurrentFunction(),
                                                       IRInstOperator::IRINST_OP_GE_I,
                                                       left->val,
                                                       right->val,
                                                       IntegerType::getTypeBool());

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(geInst);

    node->val = geInst;

    return true;
}

/// @brief 赋值AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败

bool IRGenerator::ir_assign(ast_node * node)
{
    ast_node * son1_node = node->sons[0];
    ast_node * son2_node = node->sons[1];

    if (node->node_type == ast_operator_type::AST_OP_ASSIGN) {
        son1_node->fatherIsAssign = true;
        son2_node->fatherIsAssign = true;
    } //数组的索引要使用这个字段
   
    // 赋值运算符的左侧操作数
    ast_node * left = ir_visit_ast_node(son1_node);
    if (!left) {
        // 某个变量没有定值
        // 这里缺省设置变量不存在则创建，因此这里不会错误
        return false;
    }

    // 赋值运算符的右侧操作数
    ast_node * right = ir_visit_ast_node(son2_node);
    if (!right) {
        // 某个变量没有定值
        return false;
    }
   
        node->blockInsts.addInst(right->blockInsts);
        node->blockInsts.addInst(left->blockInsts);

       
    //对于左右两边都是赋值语句，要特殊处理，创建一个临时变量
        if (left->node_type == ast_operator_type::AST_OP_ARRAY_INDEX && right->node_type ==
       ast_operator_type::AST_OP_ARRAY_INDEX) {
		 MinusInstruction * LoadInst = new MinusInstruction(module->getCurrentFunction(),
                                                              IRInstOperator::IRINST_OP_LOAD,
                                                              right->val,
                                                              IntegerType::getTypeInt());

         MoveInstruction * StoreInst = new MoveInstruction(module->getCurrentFunction(),left->val, LoadInst);
         node->blockInsts.addInst(LoadInst);
         node->blockInsts.addInst(StoreInst);
         return true;         
        }

    MoveInstruction * movInst = new MoveInstruction(module->getCurrentFunction(), left->val, right->val);

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(movInst);

    // 这里假定赋值的类型是一致的
    node->val = movInst;

    return true;
    }

/// @brief return节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_return(ast_node * node)
{
    ast_node * right = nullptr;

    // return语句可能没有没有表达式，也可能有，因此这里必须进行区分判断
    if (!node->sons.empty()) {

        ast_node * son_node = node->sons[0];

        // 返回的表达式的指令保存在right节点中
        right = ir_visit_ast_node(son_node);
        if (!right) {

            // 某个变量没有定值
            return false;
        }
    }

    // 这里只处理整型的数据，如需支持实数，则需要针对类型进行处理
    Function * currentFunc = module->getCurrentFunction();

    // 返回值存在时则移动指令到node中
    if (right) {

        // 创建临时变量保存IR的值，以及线性IR指令
        node->blockInsts.addInst(right->blockInsts);

        // 返回值赋值到函数返回值变量上，然后跳转到函数的尾部
        node->blockInsts.addInst(new MoveInstruction(currentFunc, currentFunc->getReturnValue(), right->val));

        node->val = right->val;
    } else {
        // 没有返回值
        node->val = nullptr;
    }

    // 跳转到函数的尾部出口指令上
    node->blockInsts.addInst(new GotoInstruction(currentFunc, currentFunc->getExitLabel()));

    return true;
}


/// @brief 类型叶子节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_leaf_node_type(ast_node * node)
{
    // 不需要做什么，直接从节点中获取即可。

    return true;
    }

    /// @brief 标识符叶子节点翻译成线性中间IR，变量声明的不走这个语句
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool IRGenerator::ir_leaf_node_var_id(ast_node * node)
    {
        Value * val;

        // 查找ID型Value
        // 变量，则需要在符号表中查找对应的值

        val = module->findVarValue(node->name);

        node->val = val;

        return true;
    }

    /// @brief 无符号整数字面量叶子节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool IRGenerator::ir_leaf_node_uint(ast_node * node)
    {
        ConstInt * val;

        // 新建一个整数常量Value
        val = module->newConstInt((int32_t) node->integer_val);

        node->val = val;

        return true;
    }

    /// @brief 变量声明语句节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool IRGenerator::ir_declare_statment(ast_node * node)
    {
        bool result = false;

        for (auto & child: node->sons) {

            // 遍历每个变量声明
            result = ir_variable_declare(child);
            if (!result) {
                break;
            }
            node->blockInsts.addInst(child->blockInsts);
        }

        return result;
    }

    /// @brief 变量定声明节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool IRGenerator::ir_variable_declare(ast_node * node) //var-decl节点
    {
        // 共有两个孩子：第一个是类型节点，第二个是标识符节点或赋值节点
        ast_node * type_node = node->sons[0];
        ast_node * id_node = node->sons[1]; //id_node 可能是a 或者 a=0  或者 a[4][5]

        Function * currentFunc = module->getCurrentFunction();

        LocalVariable * var = nullptr;
		
            // 创建局部变量并加入符号表
        if (id_node->node_type == ast_operator_type::AST_OP_ASSIGN) // 处理已初始化变量
        {
            ast_node * id_node_son = id_node->sons[0];
            var = static_cast<LocalVariable *>(module->newVarValue(type_node->type, id_node_son->name));
        } else if (id_node->node_type == ast_operator_type::AST_OP_ARRAY_DECL) { //处理数组   
			var = static_cast<LocalVariable *>(module->newVarValue(type_node->type, id_node->sons[0]->name));
			var->setArrayDimensions(id_node->array_dims);
        } else { //处理未初始化变量
            var = static_cast<LocalVariable *>(module->newVarValue(type_node->type, id_node->name));
        }

        // 检查是否是带初始化的声明（赋值节点）
        if (id_node->node_type == ast_operator_type::AST_OP_ASSIGN) {
            // 获取赋值节点的左右操作数
            ast_node * right = id_node->sons[1];

            // 处理右侧初始化表达式
            ast_node * right_val_node = ir_visit_ast_node(right);
            if (!right_val_node)
                return false;

            // 生成赋值指令
            MoveInstruction * movInst = new MoveInstruction(currentFunc, var, right_val_node->val);
            // 将初始化指令添加到当前节点
            node->blockInsts.addInst(right_val_node->blockInsts);
            node->blockInsts.addInst(movInst);
        } 
        node->val = var;
        return true;
        }

    // @brief  生成分支AST（if）节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败

    bool IRGenerator::ir_if(ast_node * node)
    {
        // if节点结构：cond_node, then_block
        ast_node * cond_node = node->sons[0];
        ast_node * then_block = node->sons[1];

        Function * currentFunc = module->getCurrentFunction();

        // 创建标签：true_label（then块）、false_label（else/后续块）、end_label（合并点）
        LabelInstruction * trueLabel = new LabelInstruction(currentFunc);
        // LabelInstruction * falseLabel = new LabelInstruction(currentFunc);
        LabelInstruction * endLabel = new LabelInstruction(currentFunc);

        cond_node->trueLabel = trueLabel; // 把if节点的label传下去
        cond_node->falseLabel = endLabel;
        node->trueLabel = trueLabel;
        node->falseLabel = endLabel; //设置if的label

        // 生成条件表达式IR
        ast_node * cond_val_node = ir_visit_ast_node(cond_node);
        if (!cond_val_node)
            return false;
        node->trueLabel = cond_val_node->trueLabel;
        node->falseLabel = cond_val_node->falseLabel; //如果是取非节点

        BranchInstruction * branch = new BranchInstruction(currentFunc, cond_val_node->val, node->trueLabel, node->falseLabel);
										node->blockInsts.addInst(cond_val_node->blockInsts);
										node->blockInsts.addInst(branch);
        // 生成then块的IR
        node->blockInsts.addInst(trueLabel);
        if (then_block!=nullptr)
		{
			ir_visit_ast_node(then_block);
            node->blockInsts.addInst(then_block->blockInsts);
		} // 为了修复if(); 问题
        //then块末尾跳转到end_label
        node->blockInsts.addInst(new GotoInstruction(currentFunc, endLabel));
        // 添加结束标签
        node->blockInsts.addInst(endLabel);

        return true;
    }

    // @brief  生成分支AST（ifelse）节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败

    bool IRGenerator::ir_if_else(ast_node * node)
    {
        // if-else节点结构：cond_node, then_block, else_block
        ast_node * cond_node = node->sons[0];
        ast_node * then_block = node->sons[1];
        ast_node * else_block = node->sons[2];

        Function * currentFunc = module->getCurrentFunction();

        // 创建三个标签
        LabelInstruction * trueLabel = new LabelInstruction(currentFunc);
        LabelInstruction * falseLabel = new LabelInstruction(currentFunc);
        LabelInstruction * endLabel = new LabelInstruction(currentFunc);

        cond_node->trueLabel = trueLabel;
        cond_node->falseLabel = falseLabel; //用于逻辑运算
        //node->trueLabel = trueLabel;
        //node->falseLabel = falseLabel;

        // 1. 生成条件表达式IR
        ast_node * cond_val_node = ir_visit_ast_node(cond_node);
        if (!cond_val_node)
            return false;
        node->blockInsts.addInst(cond_val_node->blockInsts);//添加表达式的IR

        node->trueLabel =cond_node->trueLabel;
        node->falseLabel = cond_node->falseLabel;
        // 这里为什么这样呢 参考：if(!(a<b && b<0)) 这里在！取非节点 交换后truelabel 和falselabel 之后
        // 还要传上去，把父亲节点的truelabel 和falselabel 也交换

        //2. 有条件跳转指令
        node->blockInsts.addInst(new BranchInstruction(currentFunc, cond_val_node->val, node->trueLabel, node->falseLabel));

        // 3. 插入trueLabel，并输出then语句的ir
        node->blockInsts.addInst(trueLabel);
        ir_visit_ast_node(then_block);
        node->blockInsts.addInst(then_block->blockInsts);

        //4. 跳转到endLabel
        node->blockInsts.addInst(new GotoInstruction(currentFunc, endLabel));

        // 5. 插入falseLabel，，并输出else语句的ir
        node->blockInsts.addInst(falseLabel);
        ir_visit_ast_node(else_block);
        node->blockInsts.addInst(else_block->blockInsts);

		//6. 跳到endLabel
        node->blockInsts.addInst(new GotoInstruction(currentFunc, endLabel));

        // 结束标签
        node->blockInsts.addInst(endLabel);

        return true;
    }


    /// @brief while语句节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool IRGenerator::ir_while(ast_node * node)
    {
        // while的sons：cond_node, loop_block
        ast_node * cond_node = node->sons[0];
        ast_node * loop_block = node->sons[1];

        Function * currentFunc = module->getCurrentFunction();

        // 创建三个标签：条件入口、循环体入口、循环出口
        LabelInstruction * condLabel = new LabelInstruction(currentFunc);
        LabelInstruction * bodyLabel = new LabelInstruction(currentFunc);
        LabelInstruction * exitLabel = new LabelInstruction(currentFunc);

        cond_node->trueLabel = bodyLabel;
        cond_node->falseLabel = exitLabel; //while左右节点

        node->trueLabel = bodyLabel;
        node->falseLabel = exitLabel;   //while节点

        // 压入循环标签栈（exitLabel, condLabel）
        loopStack.push({exitLabel, condLabel});

        // 1. 添加循环入口点 conLabel
        node->blockInsts.addInst(condLabel);

        // 2. 生成条件表达式IR 
        ast_node * cond_val_node = ir_visit_ast_node(cond_node);
        if (!cond_val_node)
            return false;
        node->blockInsts.addInst(cond_val_node->blockInsts);

        // 3. 条件跳转：若条件为真，进入循环体；否则跳转到出口
		// 为了解决while(1)问题 直接无条件跳转
        if (cond_node->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT)
		{
            node->blockInsts.addInst(new GotoInstruction(currentFunc, bodyLabel));

        }else{
            node->blockInsts.addInst(new BranchInstruction(currentFunc, cond_val_node->val, bodyLabel, exitLabel));
		}
        // 4. 生成循环体入口点 bodyLabel
        node->blockInsts.addInst(bodyLabel);
		 //5. 生成循环体的IR
        ir_visit_ast_node(loop_block);
        node->blockInsts.addInst(loop_block->blockInsts);

        // 6. 生成无条件条件跳转 循环入口点condLabel的ir
        node->blockInsts.addInst(new GotoInstruction(currentFunc, condLabel));

        // 7. 循环出口标签 exitLabel
        node->blockInsts.addInst(exitLabel);

        // 弹出循环标签栈
        loopStack.pop();

        return true;
    }

    /// @brief break语句节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool IRGenerator::ir_break(ast_node * node)
    {
        if (loopStack.empty()) {
            return false;
        }
        Function * currentFunc = module->getCurrentFunction();
        LabelInstruction * exitLabel = loopStack.top().first;

        //无条件跳转循环出口点
        node->blockInsts.addInst(new GotoInstruction(currentFunc, exitLabel));
        return true;
    }

    /// @brief continue语句节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool IRGenerator::ir_continue(ast_node * node)
    {
        if (loopStack.empty()) {
            return false;
        }
        Function * currentFunc = module->getCurrentFunction();
        LabelInstruction * condLabel = loopStack.top().second;

		//无条件跳转循环入口点
        node->blockInsts.addInst(new GotoInstruction(currentFunc, condLabel));
        return true;
    }

    /// @brief  && 逻辑与节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool IRGenerator::ir_and(ast_node * node)
    {
        ast_node * left = node->sons[0];
        ast_node * right = node->sons[1];

        Function * currentFunc = module->getCurrentFunction();

        // 创建中间标签
        LabelInstruction * shortCircuitLabel = new LabelInstruction(currentFunc);
        //LabelInstruction * falseLabel = node->falseLabel; //继承父节点的falseLabel
        left->falseLabel = node->falseLabel;
        left->trueLabel = shortCircuitLabel;
         //left 和right节点继承父节点的label
        right->falseLabel = node->falseLabel;
        right->trueLabel = node->trueLabel;

        // 1. 生成左表达式的IR
        ast_node * left_val_node = ir_visit_ast_node(left);
        if (!left_val_node)
            return false;
        left->falseLabel = left_val_node->falseLabel;  //new add
        left->trueLabel = left_val_node->trueLabel;  //这里新增为了解决exp07 这里是为了解决取非节点

        node->falseLabel = left_val_node->falseLabel;
        node->trueLabel = left_val_node->trueLabel;
        node->blockInsts.addInst(left_val_node->blockInsts); //添加左边表达式的IR

        // 2. 左表达式为假时直接跳转到父亲节点的falseLabel 否则跳到shortCircuitLabel
        //添加条件跳转指令
        // node->blockInsts.addInst(new BranchInstruction(currentFunc, left_val_node->val, node->trueLabel,node->falseLabel));

         node->blockInsts.addInst(new BranchInstruction(currentFunc, left_val_node->val, left->trueLabel,left->falseLabel));

        // 4. 插入 shortCircuitLabel
        node->blockInsts.addInst(shortCircuitLabel);

        // 5. 生成右表达式的IR
        ast_node * right_val_node = ir_visit_ast_node(right);
        if (!right_val_node)
            return false;
        //right->falseLabel = right_val_node->falseLabel;
        //right->trueLabel = right_val_node->trueLabel;
        node->falseLabel = right_val_node->falseLabel;  //解决exp08
        node->trueLabel = right_val_node->trueLabel;
        node->blockInsts.addInst(right_val_node->blockInsts); //添加右边表达式的IR
		//node->blockInsts.addInst(new BranchInstruction(currentFunc, right_val_node->val, shortCircuitLabel, node->falseLabel));

        node->val = right_val_node->val; //结果等于right_val_node->val

        return true;
    }

    /// @brief  || 逻辑或节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool IRGenerator::ir_or(ast_node * node)
    {
        ast_node * left = node->sons[0];
        ast_node * right = node->sons[1];

        Function * currentFunc = module->getCurrentFunction();

        //1.创建中间标签用于短路右表达式
        LabelInstruction * shortCircuitLabel = new LabelInstruction(currentFunc);
        //LabelInstruction * trueLabel = node->trueLabel; //继承父节点的trueLabel

        left->trueLabel = node->trueLabel; //继承父节点的trueLabel
        left->falseLabel = shortCircuitLabel;
       

        // 右表达式的真/假出口继承父节点的标签
        right->trueLabel = node->trueLabel;
        right->falseLabel = node->falseLabel;

        // 2. 生成左表达式
        ast_node * left_val_node = ir_visit_ast_node(left);
        if (!left_val_node)
            return false;
       left->falseLabel = left_val_node->falseLabel;  //new add
       left->trueLabel = left_val_node->trueLabel;  //这里新增为了解决exp07
       node->falseLabel = left_val_node->falseLabel;  //解决exp08
       node->trueLabel = left_val_node->trueLabel;

       node->blockInsts.addInst(left_val_node->blockInsts);

       // 3. 左表达式为真时直接跳转到trueLabel 否则跳到shortCircuitLabel
       node->blockInsts.addInst(new BranchInstruction(currentFunc, left_val_node->val, left->trueLabel, left->falseLabel));

	  // node->blockInsts.addInst(new BranchInstruction(currentFunc, left_val_node->val, left->trueLabel, left->falseLabel));


        // 4. 插入 shortCircuitLabel
        node->blockInsts.addInst(shortCircuitLabel);

        // 5. 生成右表达式
        ast_node * right_val_node = ir_visit_ast_node(right);
        if (!right_val_node)
            return false;

        node->falseLabel = right_val_node->falseLabel;
        node->trueLabel = right_val_node->trueLabel;
        node->blockInsts.addInst(right_val_node->blockInsts); //解决exp08

        node->val = right_val_node->val; //结果还是right_val_node->val

        return true;
    }

    /// @brief 逻辑非（!）节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
	
    bool IRGenerator::ir_not(ast_node * node)
    {
        ast_node * child = node->sons[0]; // 子表达式节点

        //Function * currentFunc = module->getCurrentFunction();

        // 反转父节点的真/假出口标签
        child->trueLabel = node->falseLabel; // 子表达式为真时，跳转到父节点的falseLabel
        child->falseLabel = node->trueLabel; // 子表达式为假时，跳转到父节点的trueLabel

        node->falseLabel = child->falseLabel ;
        node->trueLabel = child->trueLabel;

        // 生成子表达式的代码
        ast_node * child_val_node = ir_visit_ast_node(child);
        if (!child_val_node)
            return false;

        // 合并子表达式的IR指令
        node->blockInsts.addInst(child_val_node->blockInsts);

        // 逻辑非的结果即为子表达式的结果（但跳转标签已反转）
        node->val = child_val_node->val;

        return true;
    }

    /// @brief 数组访问节点array_index翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool IRGenerator::ir_array_index(ast_node * node)
    {
        Function * currentFunc = module->getCurrentFunction();

        // 1. 获取数组基地址
        ast_node * arrayNode = ir_visit_ast_node(node->sons[0]); // a[][] a 节点
        Value * baseAddr = arrayNode->val;
        std::vector<int> dims;
        dims = arrayNode->val->getArrayDimensions();

        // 2. 计算多维下标偏移
        Value * offset = nullptr;
        for (size_t i = 1; i < node->sons.size(); i++) {
            ast_node * indexNode = ir_visit_ast_node(node->sons[i]);
            node->blockInsts.addInst(indexNode->blockInsts);//如果节点是表达式 比如array[i-1]

            // 第一维：offset = index
            if (!offset) {
                offset = indexNode->val;
            }
            // 后续维：offset = offset * dim_size + index
            else {
                // 获取当前维度大小（从符号表中查询）
                int dim_size;
                dim_size = dims[i - 1]; // 修正：dims 索引从0开始
                Value * dimVal = module->newConstInt(dim_size);

                // offset = offset * dim_size
                BinaryInstruction * mulInst = new BinaryInstruction(currentFunc,
                                                                    IRInstOperator::IRINST_OP_MUL_I,
                                                                    offset,
                                                                    dimVal,
                                                                    IntegerType::getTypeInt());
                node->blockInsts.addInst(mulInst);

                // offset = offset + index
                BinaryInstruction * addInst = new BinaryInstruction(currentFunc,
                                                                    IRInstOperator::IRINST_OP_ADD_I,
                                                                    mulInst,
                                                                    indexNode->val,
                                                                    IntegerType::getTypeInt());
                node->blockInsts.addInst(addInst);
                offset = addInst;
            }
        } //多维度

        // 3. 计算元素偏移（考虑元素大小）
        Value * elemSize = module->newConstInt(4); // int类型大小
        BinaryInstruction * elemOffsetInst = new BinaryInstruction(currentFunc,
                                                                   IRInstOperator::IRINST_OP_MUL_I,
                                                                   offset,
                                                                   elemSize,
                                                                   IntegerType::getTypeInt());
        node->blockInsts.addInst(elemOffsetInst);

        
        const Type * elementType = baseAddr->getType()->getRootType();                   // 使用 const Type*
        const PointerType * ptrType = PointerType::get(const_cast<Type *>(elementType)); // 移除 const

        // 4. 计算最终地址最后加入基地址
        BinaryInstruction * addrInst =new BinaryInstruction(currentFunc,
                                  IRInstOperator::IRINST_OP_ADD_I,
                                  baseAddr,
                                  elemOffsetInst,
                                  const_cast<Type *>(reinterpret_cast<const Type *>(ptrType))); // 移除 const
        node->blockInsts.addInst(addrInst);

        if (!(node->fatherIsAssign))  //对于那些赋节点不是assign的数组索引：比如return + ,把数组的值赋给一个临时变量，这样上层直接使用这个临时变量就可以
		{
            MinusInstruction * LoadInst = new MinusInstruction(module->getCurrentFunction(),
                                                               IRInstOperator::IRINST_OP_LOAD,
                                                               addrInst,
                                                               IntegerType::getTypeInt());
            node->blockInsts.addInst(LoadInst);
            node->val = LoadInst;
			return true;
        }
        
       node->val = addrInst; 

        return true;
    }

/// @brief for语句翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
/*
    bool IRGenerator::ir_for(ast_node * node)
    {
        // for节点有四个孩子：初始化、条件、步进、循环体
        ast_node * forInit = node->sons[0];   // 初始化语句
        ast_node * cond_node = node->sons[1]; // 条件表达式
        ast_node * step_node = node->sons[2]; // 步进表达式
        ast_node * body_node = node->sons[3]; // 循环体

        Function * currentFunc = module->getCurrentFunction();
        if (!currentFunc) {
            return false;
        }

        // 创建标签
        LabelInstruction * condLabel = new LabelInstruction(currentFunc); // 条件标签
        LabelInstruction * bodyLabel = new LabelInstruction(currentFunc); // 循环体标签
        LabelInstruction * stepLabel = new LabelInstruction(currentFunc); // 步进标签
        LabelInstruction * exitLabel = new LabelInstruction(currentFunc); // 退出标签

        // 压入循环标签栈（用于break/continue）
        loopStack.push({exitLabel, stepLabel});

        // 进入for循环作用域
        module->enterScope();

        // 1. 初始化部分 int i=0;
        if (forInit) {
            ast_node * init_result = ir_visit_ast_node(forInit);
            if (!init_result) {
                module->leaveScope(); // 错误时退出作用域
                return false;
            }
            node->blockInsts.addInst(init_result->blockInsts);
        }

        // 2. 无条件跳转到条件判断
        node->blockInsts.addInst(new GotoInstruction(currentFunc, condLabel));

        // 条件判断标签
        node->blockInsts.addInst(condLabel);

        // 3. 条件表达式
        Value * condValue = nullptr;
        if (cond_node) {
            ast_node * cond_result = ir_visit_ast_node(cond_node);
            if (!cond_result) {
                return false;
            }
            node->blockInsts.addInst(cond_result->blockInsts);
            condValue = cond_result->val;
        } else {
            // 如果没有条件，则默认为真
            condValue = module->newConstInt(1);
        }

        // 4. 条件跳转：真则进入循环体，假则退出
        node->blockInsts.addInst(new BranchInstruction(currentFunc, condValue, bodyLabel, exitLabel));

        // 循环体标签
        node->blockInsts.addInst(bodyLabel);

        // 5. 循环体
        if (body_node) {
            ast_node * body_result = ir_visit_ast_node(body_node);
            if (!body_result) {
                return false;
            }
            node->blockInsts.addInst(body_result->blockInsts);
        }

        //5.  跳转到步进标签
        node->blockInsts.addInst(new GotoInstruction(currentFunc, stepLabel));

        // 步进标签
        node->blockInsts.addInst(stepLabel);

        // 6.  步进表达式 i++
        if (step_node) {
            ast_node * step_result = ir_visit_ast_node(step_node);
            if (!step_result) {
                return false;
            }
            node->blockInsts.addInst(step_result->blockInsts);
        }

        // 7. 跳转回条件判断 跳到判断是否 i<10
        node->blockInsts.addInst(new GotoInstruction(currentFunc, condLabel));

        // 退出标签
        node->blockInsts.addInst(exitLabel);

        module->leaveScope(); //退出作用域
        loopStack.pop(); //还得看这个


            return true;
    }


    bool IRGenerator::ir_for(ast_node * node)
    {
        // for节点有四个孩子：初始化、条件、步进、循环体
        ast_node * forInit = node->sons.size() > 0 ? node->sons[0] : nullptr;   // 初始化语句（可选）
        ast_node * cond_node = node->sons.size() > 1 ? node->sons[1] : nullptr; // 条件表达式（可选）
        ast_node * step_node = node->sons.size() > 2 ? node->sons[2] : nullptr; // 步进表达式（可选）
        ast_node * body_node = node->sons.size() > 3 ? node->sons[3] : nullptr; // 循环体（可选）

        Function * currentFunc = module->getCurrentFunction();
        if (!currentFunc) {
            return false;
        }

        // 创建标签
        LabelInstruction * condLabel = new LabelInstruction(currentFunc); // 条件标签
        LabelInstruction * bodyLabel = new LabelInstruction(currentFunc); // 循环体标签
        LabelInstruction * stepLabel = new LabelInstruction(currentFunc); // 步进标签
        LabelInstruction * exitLabel = new LabelInstruction(currentFunc); // 退出标签

        // 压入循环标签栈（用于break/continue）
        loopStack.push({exitLabel, stepLabel});

        // 进入for循环作用域（只在有初始化变量时创建作用域）
        bool hasScope = false;
        if (forInit && forInit->node_type == ast_operator_type::AST_OP_DECL_STMT) {
            module->enterScope();
            hasScope = true;
        }

        // 1. 初始化部分（如果有）
        if (forInit) {
            ast_node * init_result = ir_visit_ast_node(forInit);
            if (!init_result) {
                if (hasScope)
                    module->leaveScope();
                return false;
            }
            node->blockInsts.addInst(init_result->blockInsts);
        }

        // 2. 无条件跳转到条件判断
        node->blockInsts.addInst(new GotoInstruction(currentFunc, condLabel));

        // 条件判断标签
        node->blockInsts.addInst(condLabel);

        // 3. 条件表达式（如果有）
        Value * condValue = nullptr;
        if (cond_node) {
            ast_node * cond_result = ir_visit_ast_node(cond_node);
            if (!cond_result) {
                if (hasScope)
                    module->leaveScope();
                return false;
            }
            node->blockInsts.addInst(cond_result->blockInsts);
            condValue = cond_result->val;
        } else {
            // 如果没有条件，则默认为真（无限循环）
            condValue = module->newConstInt(1);
        }

        // 4. 条件跳转：真则进入循环体，假则退出
        node->blockInsts.addInst(new BranchInstruction(currentFunc, condValue, bodyLabel, exitLabel));

        // 循环体标签
        node->blockInsts.addInst(bodyLabel);

        // 5. 循环体（如果有）
        if (body_node) {
            ast_node * body_result = ir_visit_ast_node(body_node);
            if (!body_result) {
                if (hasScope)
                    module->leaveScope();
                return false;
            }
            node->blockInsts.addInst(body_result->blockInsts);
        }

        // 6. 跳转到步进标签
        node->blockInsts.addInst(new GotoInstruction(currentFunc, stepLabel));

        // 步进标签
        node->blockInsts.addInst(stepLabel);

        // 7. 步进表达式（如果有）
        if (step_node) {
            ast_node * step_result = ir_visit_ast_node(step_node);
            if (!step_result) {
                if (hasScope)
                    module->leaveScope();
                return false;
            }
            node->blockInsts.addInst(step_result->blockInsts);
        }

        // 8. 跳转回条件判断
        node->blockInsts.addInst(new GotoInstruction(currentFunc, condLabel));

        // 退出标签
        node->blockInsts.addInst(exitLabel);

        // 离开for循环作用域（如果之前创建了）
        if (hasScope) {
            module->leaveScope();
        }

        loopStack.pop();

        return true;
    }
	*/

    bool IRGenerator::ir_for(ast_node * node)
    {
        // for节点有四个孩子：初始化、条件、步进、循环体
		/*
        ast_node * forInit = node->sons.size() > 0 ? node->sons[0] : nullptr;
        ast_node * cond_node = node->sons.size() > 1 ? node->sons[1] : nullptr;
        ast_node * step_node = node->sons.size() > 2 ? node->sons[2] : nullptr;
        ast_node * body_node = node->sons.size() > 3 ? node->sons[3] : nullptr;		
*/
		ast_node * forInit = node->sons[0];
		ast_node * cond_node = node->sons[1];
		ast_node * step_node = node->sons[2];
		ast_node * body_node = node->sons[3];

		Function * currentFunc = module->getCurrentFunction();
		if (!currentFunc) {
			return false;
			}

        // 创建标签
        LabelInstruction * condLabel = new LabelInstruction(currentFunc);
        LabelInstruction * bodyLabel = new LabelInstruction(currentFunc);
        LabelInstruction * stepLabel = new LabelInstruction(currentFunc);
        LabelInstruction * exitLabel = new LabelInstruction(currentFunc);

        // 压入循环标签栈
        loopStack.push({exitLabel, stepLabel});

        // 进入for循环作用域（只在有初始化变量时创建）
        bool hasScope = false;
        if (forInit && forInit->node_type == ast_operator_type::AST_OP_DECL_STMT) {
            module->enterScope();
            hasScope = true;
        }

        // 1. 初始化部分
        if (!(forInit->node_type == ast_operator_type::AST_OP_NO)) {
            ast_node * init_result = ir_visit_ast_node(forInit);
            if (!init_result) {
                if (hasScope)
                    module->leaveScope();
                return false;
            }
            node->blockInsts.addInst(init_result->blockInsts);
        }

        // 2. 无条件跳转到条件判断
        node->blockInsts.addInst(new GotoInstruction(currentFunc, condLabel));

        // 条件判断标签
        node->blockInsts.addInst(condLabel);

        // 3. 条件表达式处理
        if (cond_node->node_type == ast_operator_type::AST_OP_NO) {
            // 无条件时：直接跳转到循环体
            node->blockInsts.addInst(new GotoInstruction(currentFunc, bodyLabel));   
        } else {
            // 有条件表达式时：正常处理条件
            ast_node * cond_result = ir_visit_ast_node(cond_node);
            if (!cond_result) {
                if (hasScope)
                    module->leaveScope();
                return false;
            }
            node->blockInsts.addInst(cond_result->blockInsts);

            // 使用条件跳转
            node->blockInsts.addInst(new BranchInstruction(currentFunc, cond_result->val, bodyLabel, exitLabel));
        }

        // 循环体标签
        node->blockInsts.addInst(bodyLabel);

        // 4. 循环体
        if (body_node) {
            ast_node * body_result = ir_visit_ast_node(body_node);
            if (!body_result) {
                if (hasScope)
                    module->leaveScope();
                return false;
            }
            node->blockInsts.addInst(body_result->blockInsts);
        }

        // 5. 跳转到步进标签
        node->blockInsts.addInst(new GotoInstruction(currentFunc, stepLabel));

        // 步进标签
        node->blockInsts.addInst(stepLabel);

        // 6. 步进表达式
        if (step_node) {
            ast_node * step_result = ir_visit_ast_node(step_node);
            if (!step_result) {
                if (hasScope)
                    module->leaveScope();
                return false;
            }
            node->blockInsts.addInst(step_result->blockInsts);
        }

        // 7. 跳转回条件判断
        node->blockInsts.addInst(new GotoInstruction(currentFunc, condLabel));

        // 退出标签
        node->blockInsts.addInst(exitLabel);

        // 离开作用域
        if (hasScope) {
            module->leaveScope();
        }

        loopStack.pop();

        return true;
    }
/// @brief 后置自增语句翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_post_inc(ast_node * node)
{
	// 后缀自增：a++
	ast_node * child = node->sons[0];

	
	ast_node * child_result = ir_visit_ast_node(child);
	if (!child_result) {
		return false;
	}

	node->blockInsts.addInst(child_result->blockInsts);

	Function * currentFunc = module->getCurrentFunction();

	// 1. 对于后置自增自减 先放到一个临时变量里面
	
    MinusInstruction * LoadInst = new MinusInstruction(module->getCurrentFunction(),
                                                       IRInstOperator::IRINST_OP_STORE,
                                                       child_result->val,
                                                       IntegerType::getTypeInt());

    node->blockInsts.addInst(LoadInst); // t3=l2

    // 2.  加1
	ConstInt * one = module->newConstInt(1);
    BinaryInstruction * addInst = new BinaryInstruction(currentFunc,
                                                        IRInstOperator::IRINST_OP_ADD_I,
                                                       child_result->val,
                                                       // LoadInst,
														 one,
                                                        IntegerType::getTypeInt());
    node->blockInsts.addInst(addInst);//t4

	// 3. 存回l2   l2=t4
    MoveInstruction * StoreInst = new MoveInstruction(module->getCurrentFunction(), child_result->val, addInst);
   
    node->blockInsts.addInst(StoreInst);

    // 后缀自增返回旧值
	
	if(node->fatherIsAssign)
	{
        node->val = LoadInst; //返回t3
    }else{
        node->val = StoreInst;
    }
   

    return true;
}

/// @brief 后置自减语句翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_post_dec(ast_node * node)
{
    // 后缀自增：a--
    ast_node * child = node->sons[0];

    ast_node * child_result = ir_visit_ast_node(child);
    if (!child_result) {
        return false;
    }

    node->blockInsts.addInst(child_result->blockInsts);

    Function * currentFunc = module->getCurrentFunction();

	// 1. 放在临时变量里面
    MinusInstruction * LoadInst = new MinusInstruction(module->getCurrentFunction(),
                                                       IRInstOperator::IRINST_OP_STORE,
                                                       child_result->val,
                                                       IntegerType::getTypeInt());

    node->blockInsts.addInst(LoadInst); // t3=l2

    // 1.  减1
    ConstInt * one = module->newConstInt(1);
    BinaryInstruction * addInst = new BinaryInstruction(currentFunc,
                                                        IRInstOperator::IRINST_OP_SUB_I,
                                                        child_result->val,
                                                        one,
                                                        IntegerType::getTypeInt());
    node->blockInsts.addInst(addInst); // t4

    // 2. 存回l2   l2=t4
    MoveInstruction * StoreInst = new MoveInstruction(module->getCurrentFunction(), child_result->val, addInst);

    node->blockInsts.addInst(StoreInst);

    // 后缀自减返回旧值
    if (node->fatherIsAssign) {
        node->val = LoadInst; //返回t3
    } else {
        node->val = StoreInst;
    }

    return true;
}

/// @brief 前缀自增语句翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_pre_inc(ast_node * node)
{
    // 前缀自增：++a
    ast_node * child = node->sons[0]; // 操作数节点

    // 标记需要地址
   // child->fatherIsAssign = true;

    ast_node * child_result = ir_visit_ast_node(child);
    if (!child_result) {
        return false;
    }

    node->blockInsts.addInst(child_result->blockInsts);

    Function * currentFunc = module->getCurrentFunction();


    // 1. 加1
    ConstInt * one = module->newConstInt(1);
    BinaryInstruction * addInst = new BinaryInstruction(currentFunc,
                                                        IRInstOperator::IRINST_OP_ADD_I,
                                                        child_result->val,
                                                        one,
                                                        IntegerType::getTypeInt());
    node->blockInsts.addInst(addInst);

    // 2.  存回原处
    
    MoveInstruction * StoreInst = new MoveInstruction(module->getCurrentFunction(), child_result->val, addInst);

    node->blockInsts.addInst(StoreInst);

    // 前缀自增返回新值
    node->val = addInst;

    return true;
}

/// @brief 前缀自减语句翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_pre_dec(ast_node * node)
{
    // 前缀自增：--a
    ast_node * child = node->sons[0]; // 操作数节点

    // 标记需要地址
    // child->fatherIsAssign = true;

    ast_node * child_result = ir_visit_ast_node(child);
    if (!child_result) {
        return false;
    }

    node->blockInsts.addInst(child_result->blockInsts);

    Function * currentFunc = module->getCurrentFunction();

    // 1. -1
    ConstInt * one = module->newConstInt(1);
    BinaryInstruction * addInst = new BinaryInstruction(currentFunc,
                                                        IRInstOperator::IRINST_OP_SUB_I,
                                                        child_result->val,
                                                        one,
                                                        IntegerType::getTypeInt());
    node->blockInsts.addInst(addInst);

    // 2.  存回原处

    MoveInstruction * StoreInst = new MoveInstruction(module->getCurrentFunction(), child_result->val, addInst);

    node->blockInsts.addInst(StoreInst);

    // 前缀自增返回新值
    node->val = addInst;

    return true;
}
