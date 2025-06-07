///
/// @file Antlr4CSTVisitor.cpp
/// @brief Antlr4的具体语法树的遍历产生AST
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

#include <string>

#include "Antlr4CSTVisitor.h"
#include "AST.h"
#include "AttrType.h"

#define Instanceof(res, type, var) auto res = dynamic_cast<type>(var)

/// @brief 构造函数
MiniCCSTVisitor::MiniCCSTVisitor()
{}

/// @brief 析构函数
MiniCCSTVisitor::~MiniCCSTVisitor()
{}

/// @brief 遍历CST产生AST
/// @param root CST语法树的根结点
/// @return AST的根节点
ast_node * MiniCCSTVisitor::run(MiniCParser::CompileUnitContext * root)
{
    return std::any_cast<ast_node *>(visitCompileUnit(root));
}

/// @brief 非终结运算符compileUnit的遍历
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitCompileUnit(MiniCParser::CompileUnitContext * ctx)
{
    // compileUnit: (funcDef | varDecl)* EOF

    // 请注意这里必须先遍历全局变量后遍历函数。肯定可以确保全局变量先声明后使用的规则，但有些情况却不能检查出。
    // 事实上可能函数A后全局变量B后函数C，这时在函数A中是不能使用变量B的，需要报语义错误，但目前的处理不会。
    // 因此在进行语义检查时，可能追加检查行号和列号，如果函数的行号/列号在全局变量的行号/列号的前面则需要报语义错误
    // TODO 请追加实现。

    ast_node * temp_node;
    ast_node * compileUnitNode = create_contain_node(ast_operator_type::AST_OP_COMPILE_UNIT);

    // 可能多个变量，因此必须循环遍历
    for (auto varCtx: ctx->varDecl()) {

        // 变量函数定义
        temp_node = std::any_cast<ast_node *>(visitVarDecl(varCtx));
        (void) compileUnitNode->insert_son_node(temp_node);
    }

    // 可能有多个函数，因此必须循环遍历
    for (auto funcCtx: ctx->funcDef()) {

        // 变量函数定义
        temp_node = std::any_cast<ast_node *>(visitFuncDef(funcCtx));
        (void) compileUnitNode->insert_son_node(temp_node);
    }

    return compileUnitNode;
}

/// @brief 非终结运算符funcDef的遍历
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitFuncDef(MiniCParser::FuncDefContext * ctx)
{
    // 识别的文法产生式：funcDef: returnType T_ID T_L_PAREN (paramList)?  T_R_PAREN block;

    // 函数返回类型 returnType
    auto returnTypeAttr = std::any_cast<type_attr>(visitReturnType(ctx->returnType()));
    // 形参列表  paramList 
    ast_node * formalParamsNode = nullptr;
    if (ctx->paramList()) {
        formalParamsNode = std::any_cast<ast_node *>(visitParamList(ctx->paramList()));
    }

    // 创建函数名的标识符终结符节点，终结符
    char * id = strdup(ctx->T_ID()->getText().c_str());

    var_id_attr funcId{id, (int64_t) ctx->T_ID()->getSymbol()->getLine()};

    
    // 遍历block结点创建函数体节点，非终结符
    auto blockNode = std::any_cast<ast_node *>(visitBlock(ctx->block()));

    // 创建函数定义的节点，孩子有类型，函数名，语句块和形参
    // create_func_def函数内会释放funcId中指向的标识符空间，切记，之后不要再释放，之前一定要是通过strdup函数或者malloc分配的空间
    return create_func_def(returnTypeAttr, funcId, blockNode, formalParamsNode);
}

/// @brief 非终结运算符returnType(函数返回类型)的遍历
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitReturnType(MiniCParser::ReturnTypeContext * ctx)
{

    // 识别文法：returnType:T_INT| T_VOID;
    type_attr typeAttr;
    if (ctx->T_INT()) {
        typeAttr.type = BasicType::TYPE_INT;
        typeAttr.lineno = ctx->T_INT()->getSymbol()->getLine();
    } else if (ctx->T_VOID()) {
        typeAttr.type = BasicType::TYPE_VOID;
        typeAttr.lineno = ctx->T_VOID()->getSymbol()->getLine();
    }
    return typeAttr;
}

/// @brief 非终结运算符paramList（形式参数列表）的遍历
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitParamList(MiniCParser::ParamListContext * ctx)
{
    // 识别文法： paramList: param (T_COMMA param)*;
    auto formalParamsNode = create_contain_node(ast_operator_type::AST_OP_FUNC_FORMAL_PARAMS);
    for (auto paramCtx: ctx->param()) {
        auto paramNode = std::any_cast<ast_node *>(visitParam(paramCtx));
        formalParamsNode->insert_son_node(paramNode);
    }
    return formalParamsNode;
}


/// @brief 非终结运算符param（单个形式参数）的遍历
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitParam(MiniCParser::ParamContext * ctx)
{
    // 获取类型
    type_attr typeAttr = std::any_cast<type_attr>(visitBasicType(ctx->basicType()));
   // type_attr typeAttr = std::any_cast<type_attr>(ctx->basicType());

    // 创建类型节点
    ast_node * typeNode = create_type_node(typeAttr);

    // 创建变量名节点
    auto id = ctx->T_ID()->getText();
    int64_t lineNo = ctx->T_ID()->getSymbol()->getLine();
    ast_node * idNode = ast_node::New(id, lineNo);

    // 形参节点：类型 + 变量名 
    return ast_node::New(ast_operator_type::AST_OP_VAR_DECL, typeNode, idNode, nullptr);
}

/// @brief 非终结运算符block的遍历
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitBlock(MiniCParser::BlockContext * ctx)
{
    // 识别的文法产生式：block : T_L_BRACE blockItemList? T_R_BRACE';
    if (!ctx->blockItemList()) {
        // 语句块没有语句

        // 为了方便创建一个空的Block节点
        return create_contain_node(ast_operator_type::AST_OP_BLOCK);
    }

    // 语句块含有语句

    // 内部创建Block节点，并把语句加入，这里不需要创建Block节点
    return visitBlockItemList(ctx->blockItemList());
}

/// @brief 非终结运算符blockItemList的遍历
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitBlockItemList(MiniCParser::BlockItemListContext * ctx)
{
    // 识别的文法产生式：blockItemList : blockItem +;
    // 正闭包 循环 至少一个blockItem
    auto block_node = create_contain_node(ast_operator_type::AST_OP_BLOCK);

    for (auto blockItemCtx: ctx->blockItem()) {

        // 非终结符，需遍历
        auto blockItem = std::any_cast<ast_node *>(visitBlockItem(blockItemCtx));

        // 插入到块节点中
        (void) block_node->insert_son_node(blockItem);
    }

    return block_node;
}

///
/// @brief 非终结运算符blockItem的遍历
/// @param ctx CST上下文
///
std::any MiniCCSTVisitor::visitBlockItem(MiniCParser::BlockItemContext * ctx)
{
    // 识别的文法产生式：blockItem : statement | varDecl
    if (ctx->statement()) {
        // 语句识别

        return visitStatement(ctx->statement());
    } else if (ctx->varDecl()) {
        return visitVarDecl(ctx->varDecl());
    }

    return nullptr;
}

/// @brief 非终结运算符statement中的遍历
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitStatement(MiniCParser::StatementContext * ctx)
{
    // statement: T_ID T_ASSIGN expr T_SEMICOLON  # assignStatement
    // | T_RETURN expr T_SEMICOLON # returnStatement
    // | block  # blockStatement
    // | expr ? T_SEMICOLON #expressionStatement;
    // | T_IF T_L_PAREN expr T_R_PAREN statement (T_ELSE statement)?   # ifStatement
    // | T_WHILE T_L_PAREN expr T_R_PAREN statement #whileStatement 
	// | T_BREAK T_SEMICOLON #breakStatement 
    // |  T_CONTINUE T_SEMICOLON #continueStatement;

    if (Instanceof(assignCtx, MiniCParser::AssignStatementContext *, ctx)) {
        return visitAssignStatement(assignCtx);
    } else if (Instanceof(returnCtx, MiniCParser::ReturnStatementContext *, ctx)) {
        return visitReturnStatement(returnCtx);
    } else if (Instanceof(blockCtx, MiniCParser::BlockStatementContext *, ctx)) {
        return visitBlockStatement(blockCtx);
    } else if (Instanceof(exprCtx, MiniCParser::ExpressionStatementContext *, ctx)) {
        return visitExpressionStatement(exprCtx);
    } else if (Instanceof(ifCtx, MiniCParser::IfStatementContext *, ctx)) {
        return visitIfStatement(ifCtx);
    } else if (Instanceof(whileCtx, MiniCParser::WhileStatementContext *, ctx)) {
        return visitWhileStatement(whileCtx);
    } else if (Instanceof(breakCtx, MiniCParser::BreakStatementContext *, ctx)) {
        return visitBreakStatement(breakCtx);
    } else if (Instanceof(continueCtx, MiniCParser::ContinueStatementContext *, ctx)) {
        return visitContinueStatement(continueCtx);
    }
    return nullptr;
}

///
/// @brief 非终结运算符statement中的returnStatement的遍历
/// @param ctx CST上下文
///
std::any MiniCCSTVisitor::visitReturnStatement(MiniCParser::ReturnStatementContext * ctx)
{
    // 识别的文法产生式：returnStatement -> T_RETURN expr? T_SEMICOLON

    ast_node * exprNode = nullptr;

    // 非终结符，表达式expr遍历
    if (ctx->expr()) {
        exprNode = std::any_cast<ast_node *>(visitExpr(ctx->expr()));
    }

    // 创建返回节点，其孩子为Expr
    return create_contain_node(ast_operator_type::AST_OP_RETURN, exprNode);
}

///
/// @brief 非终结运算符statement中的assignStatement的遍历
/// @param ctx CST上下文
///
std::any MiniCCSTVisitor::visitAssignStatement(MiniCParser::AssignStatementContext * ctx)
{
    // 识别文法产生式：assignStatement: lVal T_ASSIGN expr T_SEMICOLON

    // 赋值左侧左值Lval遍历产生节点
    auto lvalNode = std::any_cast<ast_node *>(visitLVal(ctx->lVal()));

    // 赋值右侧expr遍历
    auto exprNode = std::any_cast<ast_node *>(visitExpr(ctx->expr()));

    // 创建一个AST_OP_ASSIGN类型的中间节点，孩子为Lval和Expr
    return ast_node::New(ast_operator_type::AST_OP_ASSIGN, lvalNode, exprNode, nullptr);
}

std::any MiniCCSTVisitor::visitBlockStatement(MiniCParser::BlockStatementContext * ctx)
{
    // 识别文法产生式 blockStatement: block

    return visitBlock(ctx->block());
}

std::any MiniCCSTVisitor::visitIfStatement(MiniCParser::IfStatementContext * ctx)
{
    // statement -> T_IF T_L_PAREN expr T_R_PAREN statement (T_ELSE statement)?   # ifStatement
    //  处理条件表达式
    ast_node * cond = std::any_cast<ast_node *>(visitExpr(ctx->expr()));

    // 处理then块
    ast_node * thenBlock = std::any_cast<ast_node *>(visitStatement(ctx->statement(0)));

    // 处理else块（如果有）
    ast_node * elseBlock = nullptr;
    if (ctx->T_ELSE()) {
        elseBlock = std::any_cast<ast_node *>(visitStatement(ctx->statement(1)));
    }

    // 创建AST节点
    ast_operator_type op = elseBlock ? ast_operator_type::AST_OP_IF_ELSE : ast_operator_type::AST_OP_IF;
    //ast_operator_type op = ast_operator_type::AST_OP_IF;
   // return ast_node::New(op, cond, thenBlock, elseBlock);
    return create_contain_node(op, cond, thenBlock, elseBlock);
}

std::any MiniCCSTVisitor::visitWhileStatement(MiniCParser::WhileStatementContext * ctx)
{
    // 识别文法： statement -> T_WHILE T_L_PAREN expr T_R_PAREN statement    # whileStatement
    ast_node * cond = std::any_cast<ast_node *>(visitExpr(ctx->expr()));
    ast_node * body = std::any_cast<ast_node *>(visitStatement(ctx->statement()));
    ast_node * whileNode = create_contain_node(ast_operator_type::AST_OP_WHILE, cond, body);
    //whileNode->loopStartLabel = generateLabel(); // 循环入口标签
    //whileNode->loopEndLabel = generateLabel();   // 循环出口标签
    return whileNode;
}

std::any MiniCCSTVisitor::visitBreakStatement(MiniCParser::BreakStatementContext * ctx)
{
    //识别文法： statement ->  T_WHILE T_L_PAREN expr T_R_PAREN statement    # whileStatement
    ast_node * breakNode = create_contain_node(ast_operator_type::AST_OP_BREAK);
    //breakNode->loopEndLabel = currentLoopEndLabel(); // 从上下文获取当前循环出口标签
    return breakNode;
}

std::any MiniCCSTVisitor::visitContinueStatement(MiniCParser::ContinueStatementContext * ctx)
{
    //识别文法： statement ->  T_BREAK T_SEMICOLON #breakStatement | T_CONTINUE T_SEMICOLON #continueStatement;
    ast_node * continueNode = create_contain_node(ast_operator_type::AST_OP_CONTINUE);
    //continueNode->loopStartLabel = currentLoopStartLabel(); // 获取当前循环入口标签
    return continueNode;
}


/// @brief 非终结运算符expr的遍历
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitExpr(MiniCParser::ExprContext * ctx)
{
    // 识别产生式：expr: logicalOrExp;

    return visitLogicalOrExp(ctx->logicalOrExp());
}

std::any MiniCCSTVisitor::visitLogicalOrExp(MiniCParser::LogicalOrExpContext * ctx)
{
    // 识别产生式：logicalOrExp: logicalAndExp (T_OR logicalAndExp)*;
    if (ctx->T_OR().empty())
        return visitLogicalAndExp(ctx->logicalAndExp()[0]);

    ast_node *left, *right;
    for (size_t i = 0; i < ctx->T_OR().size(); i++) {
        if (i == 0)
            left = std::any_cast<ast_node *>(visitLogicalAndExp(ctx->logicalAndExp()[i]));
        right = std::any_cast<ast_node *>(visitLogicalAndExp(ctx->logicalAndExp()[i + 1]));
        left = ast_node::New(ast_operator_type::AST_OP_OR, left, right, nullptr);
       // left->trueLabel = generateLabel();  // 整个表达式为真时跳转
        //left->falseLabel = generateLabel(); // 假出口标签
    }
    return left;
}

std::any MiniCCSTVisitor::visitLogicalAndExp(MiniCParser::LogicalAndExpContext * ctx)
{
    // 识别文法： logicalAndExp: relExp (T_AND relExp)*;
    if (ctx->T_AND().empty())
        return visitRelExp(ctx->relExp()[0]);

    ast_node *left, *right;
    for (size_t i = 0; i < ctx->T_AND().size(); i++) {
        if (i == 0)
            left = std::any_cast<ast_node *>(visitRelExp(ctx->relExp()[i]));
        right = std::any_cast<ast_node *>(visitRelExp(ctx->relExp()[i + 1]));
        left = ast_node::New(ast_operator_type::AST_OP_AND, left, right, nullptr);
        //left->trueLabel = generateLabel();
       // left->falseLabel = generateLabel();
    }
    return left;
}

/// @brief 非终结运算符relExp的遍历
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitRelExp(MiniCParser::RelExpContext * ctx)
{

	// 识别文法： relExp: addExp (relOp addExp)*;
    if (ctx->relOp().empty()) {
        return visitAddExp(ctx->addExp()[0]);
    }

    ast_node *left, *right;
    auto ops = ctx->relOp();

    for (size_t i = 0; i < ops.size(); i++) {
        ast_operator_type op = std::any_cast<ast_operator_type>(visitRelOp(ops[i]));
        if (i == 0) {
            left = std::any_cast<ast_node *>(visitAddExp(ctx->addExp()[i]));
        }
        right = std::any_cast<ast_node *>(visitAddExp(ctx->addExp()[i + 1]));
        left = ast_node::New(op, left, right, nullptr);
    }
    return left;
}




/// @brief relOp
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitRelOp(MiniCParser::RelOpContext * ctx)
{
	//relop
    if (ctx->T_LT())
        return ast_operator_type::AST_OP_LT;
    if (ctx->T_GT())
        return ast_operator_type::AST_OP_GT;
    if (ctx->T_LE())
        return ast_operator_type::AST_OP_LE;
    if (ctx->T_GE())
        return ast_operator_type::AST_OP_GE;
    if (ctx->T_EQ())
        return ast_operator_type::AST_OP_EQ;
    return ast_operator_type::AST_OP_NE; // T_NE
}



std::any MiniCCSTVisitor::visitAddExp(MiniCParser::AddExpContext * ctx)
{
    if (ctx->addOp().empty()) {
        // 直接返回第一个mulExp（假设只有一个）
        return visitMulExp(ctx->mulExp()[0]);
    }

    ast_node *left, *right;
    auto ops = ctx->addOp();

    for (size_t i = 0; i < ops.size(); i++) { // 改为size_t
        ast_operator_type op = std::any_cast<ast_operator_type>(visitAddOp(ops[i]));
        if (i == 0) {
            left = std::any_cast<ast_node *>(visitMulExp(ctx->mulExp()[i]));
        }
        right = std::any_cast<ast_node *>(visitMulExp(ctx->mulExp()[i + 1]));
        left = ast_node::New(op, left, right, nullptr);
    }
    return left;
}

/// @brief 非终结运算符addOp的遍历
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitAddOp(MiniCParser::AddOpContext * ctx)
{
    // 识别的文法产生式：addOp : T_ADD | T_SUB

    if (ctx->T_ADD()) {
        return ast_operator_type::AST_OP_ADD;
    } else {
        return ast_operator_type::AST_OP_SUB;
    }
}

// 新增方法：处理乘除模表达式
std::any MiniCCSTVisitor::visitMulExp(MiniCParser::MulExpContext * ctx)
{
    if (ctx->mulOp().empty()) {
        return visitUnaryExp(ctx->unaryExp()[0]);
    }

    ast_node *left, *right;
    auto ops = ctx->mulOp();

    for (size_t i = 0; i < ops.size(); i++) {
        ast_operator_type op = std::any_cast<ast_operator_type>(visitMulOp(ops[i]));
        if (i == 0) {
            left = std::any_cast<ast_node *>(visitUnaryExp(ctx->unaryExp()[i]));
        }
        right = std::any_cast<ast_node *>(visitUnaryExp(ctx->unaryExp()[i + 1]));
        left = ast_node::New(op, left, right, nullptr);
    }
    return left;
}
// 处理乘除模操作符类型
std::any MiniCCSTVisitor::visitMulOp(MiniCParser::MulOpContext * ctx)
{
    if (ctx->T_MUL())
        return ast_operator_type::AST_OP_MUL;
    else if (ctx->T_DIV())
        return ast_operator_type::AST_OP_DIV;
    else
        return ast_operator_type::AST_OP_MOD; // T_MOD
}


std::any MiniCCSTVisitor::visitUnaryExp(MiniCParser::UnaryExpContext * ctx)
{
    if (ctx->primaryExp()) {
        // 处理基础表达式
        ast_node * node = std::any_cast<ast_node *>(visitPrimaryExp(ctx->primaryExp()));

        // 处理前置的负号
        for (size_t i = 0; i < ctx->T_SUB().size(); i++) {
            node = ast_node::New(ast_operator_type::AST_OP_NEG, node, nullptr, nullptr);
        }
       

        for (size_t i = 0; i < ctx->T_NOT().size(); i++) {
            node = ast_node::New(ast_operator_type::AST_OP_NOT, node, nullptr, nullptr);
           // node->swapLabels(); // 翻转真/假出口标签
        }
        return node;

    } else if (ctx->T_ID()) {
        // 处理函数调用
        ast_node * funcname_node = ast_node::New(ctx->T_ID()->getText(), (int64_t) ctx->T_ID()->getSymbol()->getLine());
        ast_node * paramListNode = nullptr;
        if (ctx->realParamList()) {
            paramListNode = std::any_cast<ast_node *>(visitRealParamList(ctx->realParamList()));
        }
        return create_func_call(funcname_node, paramListNode);

    } else {
        return nullptr;
    }
}

std::any MiniCCSTVisitor::visitPrimaryExp(MiniCParser::PrimaryExpContext * ctx)
{
    ast_node * node = nullptr;
    int64_t lineNo;

    if (ctx->T_DECIMAL()) {
        // 十进制（直接解析）
        std::string text = ctx->T_DECIMAL()->getText();
        uint32_t val = stoul(text, nullptr, 10);
        lineNo = ctx->T_DECIMAL()->getSymbol()->getLine();
        node = ast_node::New(digit_int_attr{val, IntBase::DEC, lineNo});

    } else if (ctx->T_OCTAL()) {
        // 八进制（去掉开头的0，按8进制解析）
        std::string text = ctx->T_OCTAL()->getText().substr(1);
        uint32_t val = stoul(text, nullptr, 8);
        lineNo = ctx->T_OCTAL()->getSymbol()->getLine();
        node = ast_node::New(digit_int_attr{val, IntBase::OCT, lineNo});

    } else if (ctx->T_HEX()) {
        // 十六进制（去掉0x/0X，按16进制解析）
        std::string text = ctx->T_HEX()->getText().substr(2);
        uint32_t val = stoul(text, nullptr, 16);
        lineNo = ctx->T_HEX()->getSymbol()->getLine();
        node = ast_node::New(digit_int_attr{val, IntBase::HEX, lineNo});

    } else if (ctx->lVal()) {
        // 左值（变量名）
        node = std::any_cast<ast_node *>(visitLVal(ctx->lVal()));
    } else if (ctx->expr()) {
        // 括号表达式
        node = std::any_cast<ast_node *>(visitExpr(ctx->expr()));
    }

    return node;
}

std::any MiniCCSTVisitor::visitLVal(MiniCParser::LValContext * ctx)
{
    // 识别文法产生式：lVal: T_ID;
    // 获取ID的名字
    auto varId = ctx->T_ID()->getText();

    // 获取行号
    int64_t lineNo = (int64_t) ctx->T_ID()->getSymbol()->getLine();

    return ast_node::New(varId, lineNo);
}
/*
std::any MiniCCSTVisitor::visitVarDecl(MiniCParser::VarDeclContext * ctx)
{
    // varDecl: basicType varDef (T_COMMA varDef)* T_SEMICOLON;

    // 声明语句节点
    ast_node * stmt_node = create_contain_node(ast_operator_type::AST_OP_DECL_STMT);

    // 类型节点
    type_attr typeAttr = std::any_cast<type_attr>(visitBasicType(ctx->basicType()));

    for (auto & varCtx: ctx->varDef()) {
        // 变量名节点
        ast_node * id_node = std::any_cast<ast_node *>(visitVarDef(varCtx));

        // 创建类型节点
        ast_node * type_node = create_type_node(typeAttr);

        // 创建变量定义节点
        ast_node * decl_node = ast_node::New(ast_operator_type::AST_OP_VAR_DECL, type_node, id_node, nullptr);

        // 插入到变量声明语句
        (void) stmt_node->insert_son_node(decl_node);
    }

    return stmt_node;
}

std::any MiniCCSTVisitor::visitVarDef(MiniCParser::VarDefContext * ctx)
{
    // varDef: T_ID;

    auto varId = ctx->T_ID()->getText();

    // 获取行号
    int64_t lineNo = (int64_t) ctx->T_ID()->getSymbol()->getLine();

    return ast_node::New(varId, lineNo);
}
*/

/// @brief 非终结运算符basicType的遍历
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitBasicType(MiniCParser::BasicTypeContext * ctx)
{
    // 识别文法：basicType: T_INT;
    type_attr attr{BasicType::TYPE_VOID, -1};
    if (ctx->T_INT()) {
        attr.type = BasicType::TYPE_INT;
        attr.lineno = (int64_t) ctx->T_INT()->getSymbol()->getLine();
    }

    return attr;
}

/// @brief 非终结运算符varDef的遍历
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitVarDef(MiniCParser::VarDefContext * ctx)
{ 
	//识别文法varDef: T_ID (T_ASSIGN expr)?;  变量  a=0 b
    auto varId = ctx->T_ID()->getText();//a
    int64_t lineNo = (int64_t) ctx->T_ID()->getSymbol()->getLine();//行号

    // 如果有初始化表达式 a
    if (ctx->expr()) { // 创建赋值节点 (AST_OP_ASSIGN)
        ast_node * initExpr = std::any_cast<ast_node *>(visitExpr(ctx->expr()));
        ast_node * idNode = ast_node::New(varId, lineNo);
        return ast_node::New(ast_operator_type::AST_OP_ASSIGN, idNode, initExpr, nullptr);
    }
      //返回a 或者 a=0 节点
    // 没有初始化表达式 a=0
    return ast_node::New(varId, lineNo);
}

/// @brief 非终结运算符varDecl的遍历
/// @param ctx CST上下文
std::any MiniCCSTVisitor::visitVarDecl(MiniCParser::VarDeclContext * ctx)
{
	//识别文法 varDecl: basicType varDef (T_COMMA varDef)*  T_SEMICOLON;
    ast_node * stmt_node = create_contain_node(ast_operator_type::AST_OP_DECL_STMT); //decl-stmt
    type_attr typeAttr = std::any_cast<type_attr>(visitBasicType(ctx->basicType())); //type

    for (auto & varCtx: ctx->varDef()) {
        ast_node * defNode = std::any_cast<ast_node *>(visitVarDef(varCtx)); //变量的定义节点
        ast_node * typeNode = create_type_node(typeAttr);  //变量的类型节点 i32

        // 处理初始化
        ast_node * declNode; //var-decl
        if (defNode->node_type == ast_operator_type::AST_OP_ASSIGN) {
            // 创建变量声明节点 (类型 + 赋值语句)
            declNode = ast_node::New(ast_operator_type::AST_OP_VAR_DECL, typeNode,defNode, nullptr);

            // 将declNode到语句块
            stmt_node->insert_son_node(declNode);
           // 清理临时节点
           // delete defNode;
        } else {
            // 普通变量声明
            declNode = ast_node::New(ast_operator_type::AST_OP_VAR_DECL, typeNode, defNode, nullptr);
            stmt_node->insert_son_node(declNode);
        }
    }

    return stmt_node;
}

std::any MiniCCSTVisitor::visitRealParamList(MiniCParser::RealParamListContext * ctx)
{
    // 识别的文法产生式：realParamList : expr (T_COMMA expr)*;

    auto paramListNode = create_contain_node(ast_operator_type::AST_OP_FUNC_REAL_PARAMS);

    for (auto paramCtx: ctx->expr()) {

        auto paramNode = std::any_cast<ast_node *>(visitExpr(paramCtx));

        paramListNode->insert_son_node(paramNode);
    }

    return paramListNode;
}

std::any MiniCCSTVisitor::visitExpressionStatement(MiniCParser::ExpressionStatementContext * ctx)
{
    // 识别文法产生式  expr ? T_SEMICOLON #expressionStatement;
    if (ctx->expr()) {
        // 表达式语句

        // 遍历expr非终结符，创建表达式节点后返回
        return visitExpr(ctx->expr());
    } else {
        // 空语句

        // 直接返回空指针，需要再把语句加入到语句块时要注意判断，空语句不要加入
        return nullptr;
    }
}