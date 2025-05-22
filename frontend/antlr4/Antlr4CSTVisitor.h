///
/// @file Antlr4CSTVisitor.h
/// @brief Antlr4的具体语法树的遍历产生AST
/// @author TobisawaMisakii (cpy040407@gmail.com)
/// @version 1.0
/// @date 2025-04-22
///

#pragma once

#include "AST.h"
#include "SysYBaseVisitor.h"
#include <unordered_map>

/// @brief 遍历具体语法树产生抽象语法树
class SysYCSTVisitor : public SysYBaseVisitor {

public:
    /// @brief 构造函数
    SysYCSTVisitor();

    /// @brief 析构函数
    ~SysYCSTVisitor() override;

    /// @brief 遍历CST产生AST
    /// @param root CST语法树的根结点
    /// @return AST的节点
    ast_node * run(SysYParser::CompileUnitContext * root);

protected:
    /* 下面的函数都是从SysYBaseVisitor继承下来的虚拟函数，需要重载实现 */

    /// @brief 非终结运算符compileUnit的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitCompileUnit(SysYParser::CompileUnitContext * ctx) override;

    /// @brief 非终结运算符macroDecl的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitMacroDecl(SysYParser::MacroDeclContext * ctx) override;

    // 宏表
    std::unordered_map<std::string, std::string> macroTable;

    /// @brief 非终结运算符decl的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitDecl(SysYParser::DeclContext * ctx) override;

    /// @brief 非终结运算符constDecl的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitConstDecl(SysYParser::ConstDeclContext * ctx) override;

    /// @brief 非终结运算符basicType的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitBasicType(SysYParser::BasicTypeContext * ctx) override;

    /// @brief 非终结运算符constDef的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitConstDef(SysYParser::ConstDefContext * ctx) override;

    /// @brief 非终结运算符constInitVal中的singleConstantInit的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitSingleConstantInit(SysYParser::SingleConstantInitContext * ctx) override;

    /// @brief 非终结运算符constInitVal中的arrayConstantInit的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitArrayConstantInit(SysYParser::ArrayConstantInitContext * ctx) override;

    /// @brief 非终结运算符varDecl的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitVarDecl(SysYParser::VarDeclContext * ctx) override;

    /// @brief 非终结运算符varDef中的simpleVarDef的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitSimpleVarDef(SysYParser::SimpleVarDefContext * ctx) override;

    /// @brief 非终结运算符varDef中的initializedVarDef的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitInitializedVarDef(SysYParser::InitializedVarDefContext * ctx) override;

    /// @brief 非终结运算符initVal中的singleVarInit的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitSingleVarInit(SysYParser::SingleVarInitContext * ctx) override;

    /// @brief 非终结运算符initVal中的arrayVarInit的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitArrayVarInit(SysYParser::ArrayVarInitContext * ctx) override;

    /// @brief 非终结运算符funcDef的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitFuncDef(SysYParser::FuncDefContext * ctx) override;

    /// @brief 非终结运算符funcType的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitFuncType(SysYParser::FuncTypeContext * ctx) override;

    /// @brief 非终结运算符funcFParams的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitFuncFParams(SysYParser::FuncFParamsContext * ctx) override;

    /// @brief 非终结运算符funcFParam的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitFuncFParam(SysYParser::FuncFParamContext * ctx) override;

    /// @brief 非终结运算符block的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitBlock(SysYParser::BlockContext * ctx) override;

    /// @brief 非终结运算符blockItem中的declarationBlockItem的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitDeclarationBlockItem(SysYParser::DeclarationBlockItemContext * ctx) override;

    /// @brief 非终结运算符blockItem中的statementBlockItem的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitStatementBlockItem(SysYParser::StatementBlockItemContext * ctx) override;

    /// @brief 非终结运算符statement中的assignmentStatement的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitAssignmentStatement(SysYParser::AssignmentStatementContext * ctx) override;

    /// @brief 非终结运算符statement中的expressionStatement的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitExpressionStatement(SysYParser::ExpressionStatementContext * ctx) override;

    /// @brief 非终结运算符statement中的blockStatement的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitNestedBlockStatement(SysYParser::NestedBlockStatementContext * ctx) override;

    /// @brief 非终结运算符statement中的ifStatement的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitIfStatement(SysYParser::IfStatementContext * ctx) override;

    /// @brief 非终结运算符statement中的whileStatement的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitWhileStatement(SysYParser::WhileStatementContext * ctx) override;

    /// @brief 非终结运算符statement中的breakStatement的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitBreakStatement(SysYParser::BreakStatementContext * ctx) override;

    /// @brief 非终结运算符statement中的continueStatement的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitContinueStatement(SysYParser::ContinueStatementContext * ctx) override;

    /// @brief 非终结运算符statement中的returnStatement的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitReturnStatement(SysYParser::ReturnStatementContext * ctx) override;

    /// @brief 非终结运算符exp的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitExp(SysYParser::ExpContext * ctx) override;

    /// @brief 非终结运算符cond的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitCond(SysYParser::CondContext * ctx) override;

    /// @brief 非终结运算符lVal的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitLVal(SysYParser::LValContext * ctx) override;

    /// @brief 非终结运算符primaryExp中的groupedExpression的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitGroupedExpression(SysYParser::GroupedExpressionContext * ctx) override;

    /// @brief 非终结运算符primaryExp中的leftValueExpression的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitLeftValueExpression(SysYParser::LeftValueExpressionContext * ctx) override;

    /// @brief 非终结运算符primaryExp中的numberExpression的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitNumberExpression(SysYParser::NumberExpressionContext * ctx) override;

    /// @brief 非终结运算符number的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitNumber(SysYParser::NumberContext * ctx) override;

    /// @brief 非终结运算符unaryExp中的primaryUnaryExpression的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitPrimaryUnaryExpression(SysYParser::PrimaryUnaryExpressionContext * ctx) override;

    /// @brief 非终结运算符unaryExp中的functionCall的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitFunctionCall(SysYParser::FunctionCallContext * ctx) override;

    /// @brief 非终结运算符unaryExp中的unaryOperatorExpression的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitUnaryOperatorExpression(SysYParser::UnaryOperatorExpressionContext * ctx) override;

    /// @brief 非终结运算符unaryOp的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitUnaryOp(SysYParser::UnaryOpContext * ctx) override;

    /// @brief 非终结运算符funcRParams的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitFuncRParams(SysYParser::FuncRParamsContext * ctx) override;

    /// @brief 非终结运算符mulExp的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitMulExp(SysYParser::MulExpContext * ctx) override;

    /// @brief 非终结运算符addOp的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitAddExp(SysYParser::AddExpContext * ctx) override;

    /// @brief 非终结运算符relExp的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitRelExp(SysYParser::RelExpContext * ctx) override;

    /// @brief 非终结运算符eqExp的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitEqExp(SysYParser::EqExpContext * ctx) override;

    /// @brief 非终结运算符lAndExp的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitLAndExp(SysYParser::LAndExpContext * ctx) override;

    /// @brief 非终结运算符lOrExp的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitLOrExp(SysYParser::LOrExpContext * ctx) override;

    /// @brief 非终结运算符constExp的遍历
    /// @param ctx CST上下文
    /// @return AST的节点
    std::any visitConstExp(SysYParser::ConstExpContext * ctx) override;

    // 以下是SysYBaseVisitor中没有的函数，是有多种生成式的非终结符的选择函数
    std::any visitBlockItem(SysYParser::BlockItemContext * ctx);

    std::any visitStmt(SysYParser::StmtContext * ctx);

    std::any visitConstInitVal(SysYParser::ConstInitValContext * ctx);

    std::any visitVarDef(SysYParser::VarDefContext * ctx);

    std::any visitInitVal(SysYParser::InitValContext * ctx);

    std::any visitPrimaryExp(SysYParser::PrimaryExpContext * ctx);

    std::any visitUnaryExp(SysYParser::UnaryExpContext * ctx);
};
