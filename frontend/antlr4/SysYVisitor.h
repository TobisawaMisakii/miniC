
// Generated from /home/lwx/Complier/miniC/frontend/antlr4/SysY.g4 by ANTLR 4.12.0

#pragma once


#include "antlr4-runtime.h"
#include "SysYParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by SysYParser.
 */
class  SysYVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by SysYParser.
   */
    virtual std::any visitCompileUnit(SysYParser::CompileUnitContext *context) = 0;

    virtual std::any visitMacroDecl(SysYParser::MacroDeclContext *context) = 0;

    virtual std::any visitDecl(SysYParser::DeclContext *context) = 0;

    virtual std::any visitConstDecl(SysYParser::ConstDeclContext *context) = 0;

    virtual std::any visitBasicType(SysYParser::BasicTypeContext *context) = 0;

    virtual std::any visitConstDef(SysYParser::ConstDefContext *context) = 0;

    virtual std::any visitSingleConstantInit(SysYParser::SingleConstantInitContext *context) = 0;

    virtual std::any visitArrayConstantInit(SysYParser::ArrayConstantInitContext *context) = 0;

    virtual std::any visitVarDecl(SysYParser::VarDeclContext *context) = 0;

    virtual std::any visitSimpleVarDef(SysYParser::SimpleVarDefContext *context) = 0;

    virtual std::any visitInitializedVarDef(SysYParser::InitializedVarDefContext *context) = 0;

    virtual std::any visitSingleVarInit(SysYParser::SingleVarInitContext *context) = 0;

    virtual std::any visitArrayVarInit(SysYParser::ArrayVarInitContext *context) = 0;

    virtual std::any visitFuncDef(SysYParser::FuncDefContext *context) = 0;

    virtual std::any visitFuncType(SysYParser::FuncTypeContext *context) = 0;

    virtual std::any visitFuncFParams(SysYParser::FuncFParamsContext *context) = 0;

    virtual std::any visitFuncFParam(SysYParser::FuncFParamContext *context) = 0;

    virtual std::any visitBlock(SysYParser::BlockContext *context) = 0;

    virtual std::any visitDeclarationBlockItem(SysYParser::DeclarationBlockItemContext *context) = 0;

    virtual std::any visitStatementBlockItem(SysYParser::StatementBlockItemContext *context) = 0;

    virtual std::any visitAssignmentStatement(SysYParser::AssignmentStatementContext *context) = 0;

    virtual std::any visitExpressionStatement(SysYParser::ExpressionStatementContext *context) = 0;

    virtual std::any visitNestedBlockStatement(SysYParser::NestedBlockStatementContext *context) = 0;

    virtual std::any visitIfStatement(SysYParser::IfStatementContext *context) = 0;

    virtual std::any visitWhileStatement(SysYParser::WhileStatementContext *context) = 0;

    virtual std::any visitBreakStatement(SysYParser::BreakStatementContext *context) = 0;

    virtual std::any visitContinueStatement(SysYParser::ContinueStatementContext *context) = 0;

    virtual std::any visitReturnStatement(SysYParser::ReturnStatementContext *context) = 0;

    virtual std::any visitExp(SysYParser::ExpContext *context) = 0;

    virtual std::any visitCond(SysYParser::CondContext *context) = 0;

    virtual std::any visitLVal(SysYParser::LValContext *context) = 0;

    virtual std::any visitGroupedExpression(SysYParser::GroupedExpressionContext *context) = 0;

    virtual std::any visitLeftValueExpression(SysYParser::LeftValueExpressionContext *context) = 0;

    virtual std::any visitNumberExpression(SysYParser::NumberExpressionContext *context) = 0;

    virtual std::any visitNumber(SysYParser::NumberContext *context) = 0;

    virtual std::any visitPrimaryUnaryExpression(SysYParser::PrimaryUnaryExpressionContext *context) = 0;

    virtual std::any visitFunctionCall(SysYParser::FunctionCallContext *context) = 0;

    virtual std::any visitUnaryOperatorExpression(SysYParser::UnaryOperatorExpressionContext *context) = 0;

    virtual std::any visitUnaryOp(SysYParser::UnaryOpContext *context) = 0;

    virtual std::any visitFuncRParams(SysYParser::FuncRParamsContext *context) = 0;

    virtual std::any visitMulExp(SysYParser::MulExpContext *context) = 0;

    virtual std::any visitAddExp(SysYParser::AddExpContext *context) = 0;

    virtual std::any visitRelExp(SysYParser::RelExpContext *context) = 0;

    virtual std::any visitEqExp(SysYParser::EqExpContext *context) = 0;

    virtual std::any visitLAndExp(SysYParser::LAndExpContext *context) = 0;

    virtual std::any visitLOrExp(SysYParser::LOrExpContext *context) = 0;

    virtual std::any visitConstExp(SysYParser::ConstExpContext *context) = 0;


};

