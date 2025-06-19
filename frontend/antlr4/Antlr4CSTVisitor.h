///
/// @file Antlr4CSTVisitor.h
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
#pragma once

#include "AST.h"
#include "MiniCBaseVisitor.h"

/// @brief 遍历具体语法树产生抽象语法树
class MiniCCSTVisitor : public MiniCBaseVisitor {

public:
    /// @brief 构造函数
    MiniCCSTVisitor();

    /// @brief 析构函数
    virtual ~MiniCCSTVisitor();

    /// @brief 遍历CST产生AST
    /// @param root CST语法树的根结点
    /// @return AST的根节点
    ast_node * run(MiniCParser::CompileUnitContext * root);

protected:
    /* 下面的函数都是从MiniCBaseVisitor继承下来的虚拟函数，需要重载实现 */

    /// @brief 非终结运算符compileUnit的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitCompileUnit(MiniCParser::CompileUnitContext * ctx) override;

    /// @brief 非终结运算符funcDef的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitFuncDef(MiniCParser::FuncDefContext * ctx) override;

    /// @brief 非终结运算符block的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitBlock(MiniCParser::BlockContext * ctx) override;

    /// @brief 非终结运算符returnType（函数返回值） 的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitReturnType(MiniCParser::ReturnTypeContext * ctx) override;

    /// @brief 非终结运算符paramList（函数参数列表） 的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitParamList(MiniCParser::ParamListContext * ctx) override;

    /// @brief 非终结运算符param（单个函数参数） 的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitParam(MiniCParser::ParamContext * ctx) override;

    /// @brief 非终结运算符blockItemList的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitBlockItemList(MiniCParser::BlockItemListContext * ctx) override;

    /// @brief 非终结运算符blockItem的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitBlockItem(MiniCParser::BlockItemContext * ctx) override;

    /// @brief 非终结运算符statement中的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitStatement(MiniCParser::StatementContext * ctx);

    /// @brief 非终结运算符statement中的returnStatement的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitReturnStatement(MiniCParser::ReturnStatementContext * ctx) override;

    ///
    /// @brief 内部产生的非终结符assignStatement的分析
    /// @param ctx CST上下文
    /// @return std::any AST的节点
    ///
    std::any visitAssignStatement(MiniCParser::AssignStatementContext * ctx) override;

    ///
    /// @brief 内部产生的非终结符blockStatement的分析
    /// @param ctx CST上下文
    /// @return std::any AST的节点
    ///
    std::any visitBlockStatement(MiniCParser::BlockStatementContext * ctx) override;

    ///
    /// @brief 内部产生的非终结符ifStatement的分析
    /// @param ctx CST上下文
    /// @return std::any AST的节点
    ///
    std::any visitIfStatement(MiniCParser::IfStatementContext * ctx) override;

    ///
    /// @brief 内部产生的非终结符whileStatement的分析
    /// @param ctx CST上下文
    /// @return std::any AST的节点
    ///
    std::any visitWhileStatement(MiniCParser::WhileStatementContext * ctx) override;

    ///
    /// @brief 内部产生的非终结符breakStatement的分析
    /// @param ctx CST上下文
    /// @return std::any AST的节点
    ///
    std::any visitBreakStatement(MiniCParser::BreakStatementContext * ctx) override;

    ///
    /// @brief 内部产生的非终结符continueStatement的分析
    /// @param ctx CST上下文
    /// @return std::any AST的节点
    ///
    std::any visitContinueStatement(MiniCParser::ContinueStatementContext * ctx) override;

    ///
    /// @brief 内部产生的非终结符forStatement的分析
    /// @param ctx CST上下文
    /// @return std::any AST的节点
    ///
    std::any visitForStatement(MiniCParser::ForStatementContext * ctx) override;

    ///
    /// @brief 内部产生的非终结符varDeclNoSemi的分析
    /// @param ctx CST上下文
    /// @return std::any AST的节点
    ///
    std::any visitVarDeclNoSemi(MiniCParser::VarDeclNoSemiContext * ctx) override;
    

        ///
        /// @brief 内部产生的非终结符forInit的分析
        /// @param ctx CST上下文
        /// @return std::any AST的节点
        ///
    std::any visitForInit(MiniCParser::ForInitContext * ctx) override;

    std::any visitAssignNoSemi(MiniCParser::AssignNoSemiContext * ctx) override;

    /// @brief 非终结运算符expr的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitExpr(MiniCParser::ExprContext * ctx) override;

    /// @brief 非终结运算符logicalOrexpr的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitLogicalOrExp(MiniCParser::LogicalOrExpContext * ctx) override;

    /// @brief 非终结运算符logicalAndExp的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitLogicalAndExp(MiniCParser::LogicalAndExpContext * ctx) override;

    ///
    /// @brief 非终结符relExp的分析
    /// @param ctx CST上下文
    /// @return std::any AST的节点
    ///
    std::any visitRelExp(MiniCParser::RelExpContext * ctx) override;

    ///
    /// @brief 非终结符relOp的分析
    /// @param ctx CST上下文
    /// @return std::any AST的节点
    ///

    std::any visitRelOp(MiniCParser::RelOpContext * ctx) override;

    ///
    /// @brief 非终结符AddExp的分析
    /// @param ctx CST上下文
    /// @return std::any AST的节点
    ///
    std::any visitAddExp(MiniCParser::AddExpContext * ctx) override;

    ///
    /// @brief 非终结符addOp的分析
    /// @param ctx CST上下文
    /// @return std::any 类型
    ///
    std::any visitAddOp(MiniCParser::AddOpContext * ctx) override;

    ///
    /// @brief 非终结符MulExp的分析
    /// @param ctx CST上下文
    /// @return std::any AST的节点
    ///
    std::any visitMulExp(MiniCParser::MulExpContext * ctx) override;

    ///
    /// @brief 非终结符mulOp的分析
    /// @param ctx CST上下文
    /// @return std::any 类型
    ///
    std::any visitMulOp(MiniCParser::MulOpContext * ctx) override;

    ///
    /// @brief 非终结符unaryExp的分析:以上四条
    /// @param ctx CST上下文
    /// @return std::any AST的节点
    ///
    std::any visitUnaryExp(MiniCParser::UnaryExpContext * ctx) ;

    std::any visitFunctionCall(MiniCParser::FunctionCallContext * ctx) override;

    std::any visitPostfixUnary(MiniCParser::PostfixUnaryContext * ctx) override;

    std::any visitPrefixUnary(MiniCParser::PrefixUnaryContext * ctx) override;

    ///
    /// @brief 非终结符PrimaryExp的分析
    /// @param ctx CST上下文
    /// @return std::any AST的节点
    ///
    std::any visitPrimaryExp(MiniCParser::PrimaryExpContext * ctx) override;

    ///
    /// @brief 非终结符LVal的分析
    /// @param ctx CST上下文
    /// @return std::any AST的节点
    ///
    std::any visitLVal(MiniCParser::LValContext * ctx) override;

    ///
    /// @brief 非终结符VarDecl的分析
    /// @param ctx CST上下文
    /// @return std::any AST的节点
    ///
    std::any visitVarDecl(MiniCParser::VarDeclContext * ctx) override;

    ///
    /// @brief 非终结符VarDecl的分析
    /// @param ctx CST上下文
    /// @return std::any AST的节点
    ///
    std::any visitVarDef(MiniCParser::VarDefContext * ctx) override;

    ///
    /// @brief 非终结符BasicType的分析
    /// @param ctx CST上下文
    /// @return std::any AST的节点
    ///
    std::any visitBasicType(MiniCParser::BasicTypeContext * ctx) override;

    ///
    /// @brief 非终结符RealParamList的分析
    /// @param ctx CST上下文
    /// @return std::any AST的节点
    ///
    std::any visitRealParamList(MiniCParser::RealParamListContext * ctx) override;

    ///
    /// @brief 非终结符ExpressionStatement的分析
    /// @param ctx CST上下文
    /// @return std::any AST的节点
    ///
    std::any visitExpressionStatement(MiniCParser::ExpressionStatementContext * context) override;
    };
