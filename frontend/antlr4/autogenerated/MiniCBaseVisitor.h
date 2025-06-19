
// Generated from /home/code/exp03-minic-basic/exp03-minic-basic/exp04-minic-expr/frontend/antlr4/MiniC.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "MiniCVisitor.h"


/**
 * This class provides an empty implementation of MiniCVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  MiniCBaseVisitor : public MiniCVisitor {
public:

  virtual std::any visitCompileUnit(MiniCParser::CompileUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncDef(MiniCParser::FuncDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnType(MiniCParser::ReturnTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParamList(MiniCParser::ParamListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParam(MiniCParser::ParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayParam(MiniCParser::ArrayParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(MiniCParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockItemList(MiniCParser::BlockItemListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockItem(MiniCParser::BlockItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDecl(MiniCParser::VarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDef(MiniCParser::VarDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArraySuffix(MiniCParser::ArraySuffixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBasicType(MiniCParser::BasicTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStatement(MiniCParser::ReturnStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignStatement(MiniCParser::AssignStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockStatement(MiniCParser::BlockStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionStatement(MiniCParser::ExpressionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStatement(MiniCParser::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStatement(MiniCParser::WhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreakStatement(MiniCParser::BreakStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinueStatement(MiniCParser::ContinueStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForStatement(MiniCParser::ForStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForInit(MiniCParser::ForInitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDeclNoSemi(MiniCParser::VarDeclNoSemiContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignNoSemi(MiniCParser::AssignNoSemiContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpr(MiniCParser::ExprContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalOrExp(MiniCParser::LogicalOrExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalAndExp(MiniCParser::LogicalAndExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelExp(MiniCParser::RelExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelOp(MiniCParser::RelOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddExp(MiniCParser::AddExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddOp(MiniCParser::AddOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulExp(MiniCParser::MulExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulOp(MiniCParser::MulOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrefixUnary(MiniCParser::PrefixUnaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPostfixUnary(MiniCParser::PostfixUnaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCall(MiniCParser::FunctionCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryExp(MiniCParser::PrimaryExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRealParamList(MiniCParser::RealParamListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLVal(MiniCParser::LValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayIndexing(MiniCParser::ArrayIndexingContext *ctx) override {
    return visitChildren(ctx);
  }


};

