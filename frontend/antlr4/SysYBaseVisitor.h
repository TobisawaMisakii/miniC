
// Generated from /home/lwx/Complier/miniC/frontend/antlr4/SysY.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "SysYVisitor.h"


/**
 * This class provides an empty implementation of SysYVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  SysYBaseVisitor : public SysYVisitor {
public:

  virtual std::any visitCompileUnit(SysYParser::CompileUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMacroDecl(SysYParser::MacroDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDecl(SysYParser::DeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstDecl(SysYParser::ConstDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBasicType(SysYParser::BasicTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstDef(SysYParser::ConstDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSingleConstantInit(SysYParser::SingleConstantInitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayConstantInit(SysYParser::ArrayConstantInitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVarDecl(SysYParser::VarDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleVarDef(SysYParser::SimpleVarDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInitializedVarDef(SysYParser::InitializedVarDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSingleVarInit(SysYParser::SingleVarInitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArrayVarInit(SysYParser::ArrayVarInitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncDef(SysYParser::FuncDefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncType(SysYParser::FuncTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncFParams(SysYParser::FuncFParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncFParam(SysYParser::FuncFParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlock(SysYParser::BlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclarationBlockItem(SysYParser::DeclarationBlockItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementBlockItem(SysYParser::StatementBlockItemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignmentStatement(SysYParser::AssignmentStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionStatement(SysYParser::ExpressionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNestedBlockStatement(SysYParser::NestedBlockStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIfStatement(SysYParser::IfStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhileStatement(SysYParser::WhileStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBreakStatement(SysYParser::BreakStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContinueStatement(SysYParser::ContinueStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReturnStatement(SysYParser::ReturnStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExp(SysYParser::ExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCond(SysYParser::CondContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLVal(SysYParser::LValContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGroupedExpression(SysYParser::GroupedExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLeftValueExpression(SysYParser::LeftValueExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumberExpression(SysYParser::NumberExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber(SysYParser::NumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryUnaryExpression(SysYParser::PrimaryUnaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCall(SysYParser::FunctionCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryOperatorExpression(SysYParser::UnaryOperatorExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryOp(SysYParser::UnaryOpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFuncRParams(SysYParser::FuncRParamsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMulExp(SysYParser::MulExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddExp(SysYParser::AddExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelExp(SysYParser::RelExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqExp(SysYParser::EqExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLAndExp(SysYParser::LAndExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLOrExp(SysYParser::LOrExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstExp(SysYParser::ConstExpContext *ctx) override {
    return visitChildren(ctx);
  }


};

