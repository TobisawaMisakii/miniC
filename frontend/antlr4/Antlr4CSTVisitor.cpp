///
/// @file Antlr4CSTVisitor.cpp
/// @brief Antlr4的具体语法树的遍历产生AST
/// @author zenglj (zenglj@live.com)
/// @version 1.1
/// @date 2024-11-23
///

#include <string>

#include "Antlr4CSTVisitor.h"
#include "AST.h"
#include "AttrType.h"

#define Instanceof(res, type, var) auto res = dynamic_cast<type>(var)

/// @brief 构造函数
SysYCSTVisitor::SysYCSTVisitor()
{}

/// @brief 析构函数
SysYCSTVisitor::~SysYCSTVisitor()
{}

/// @brief 遍历CST产生AST
/// @param root CST语法树的根结点
/// @return AST的根节点
ast_node * SysYCSTVisitor::run(SysYParser::CompileUnitContext * root)
{
    return std::any_cast<ast_node *>(visitCompileUnit(root));
}

/// @brief 非终结运算符compileUnit的遍历
/// @param ctx CST上下文
std::any SysYCSTVisitor::visitCompileUnit(SysYParser::CompileUnitContext * ctx)
{
    ast_node * compileUnitNode = create_contain_node(ast_operator_type::AST_OP_COMPILE_UNIT);

    // 处理所有声明和函数定义
    for (auto item: ctx->decl()) {
        auto node = std::any_cast<ast_node *>(visitDecl(item));
        compileUnitNode->insert_son_node(node);
    }

    for (auto func: ctx->funcDef()) {
        auto node = std::any_cast<ast_node *>(visitFuncDef(func));
        compileUnitNode->insert_son_node(node);
    }

    // 检查是否有main函数
    bool hasMain = false;
    for (auto func: ctx->funcDef()) {
        if (func->Ident()->getText() == "main" && func->funcType()->getText() == "int" && !func->funcFParams()) {
            hasMain = true;
            break;
        }
    }

    if (!hasMain) {
        // 抛出错误：缺少main函数
        throw std::runtime_error("Error: Missing main function");
    }

    return compileUnitNode;
}

/// @brief 非终结运算符decl的遍历
std::any SysYCSTVisitor::visitDecl(SysYParser::DeclContext * ctx)
{
    if (ctx->constDecl()) {
        return visitConstDecl(ctx->constDecl());
    } else {
        return visitVarDecl(ctx->varDecl());
    }
}

/// @brief 非终结运算符constDecl的遍历
std::any SysYCSTVisitor::visitConstDecl(SysYParser::ConstDeclContext * ctx)
{
    ast_node * stmt_node = create_contain_node(ast_operator_type::AST_OP_DECL_STMT);
    type_attr typeAttr = std::any_cast<type_attr>(visitBasicType(ctx->basicType()));

    for (auto constDef: ctx->constDef()) {
        auto defNode = std::any_cast<ast_node *>(visitConstDef(constDef));
        ast_node * type_node = create_type_node(typeAttr);
        ast_node * decl_node = ast_node::New(ast_operator_type::AST_OP_CONST_DECL, type_node, defNode, nullptr);
        stmt_node->insert_son_node(decl_node);
    }

    return stmt_node;
}

/// @brief 非终结运算符constDef的遍历
std::any SysYCSTVisitor::visitConstDef(SysYParser::ConstDefContext * ctx)
{
    // 处理标识符
    std::string varName = ctx->Ident()->getText();
    ast_node * id_node = ast_node::New(varName, ctx->Ident()->getSymbol()->getLine());

    // 处理数组维度
    ast_node * dims_node = nullptr;
    if (!ctx->constExp().empty()) {
        dims_node = create_contain_node(ast_operator_type::AST_OP_ARRAY_DIMS);
        for (auto dim: ctx->constExp()) {
            auto dim_node = std::any_cast<ast_node *>(visitConstExp(dim));
            dims_node->insert_son_node(dim_node);
        }
    }

    // 处理初始化值
    auto init_node = std::any_cast<ast_node *>(visitConstInitVal(ctx->constInitVal()));

    // 创建constDef节点
    if (dims_node) {
        return ast_node::New(ast_operator_type::AST_OP_CONST_DEF, id_node, dims_node, init_node);
    } else {
        return ast_node::New(ast_operator_type::AST_OP_CONST_DEF, id_node, init_node, nullptr);
    }
}

/// @brief 非终结运算符constInitVal的遍历
std::any SysYCSTVisitor::visitConstInitVal(SysYParser::ConstInitValContext * ctx)
{
    if (Instanceof(singleConstCtx, SysYParser::SingleConstantInitContext *, ctx)) {
        return visitSingleConstantInit(singleConstCtx);
    } else if (Instanceof(arrayConstCtx, SysYParser::ArrayConstantInitContext *, ctx)) {
        return visitArrayConstantInit(arrayConstCtx);
    } else {
        // 处理其他情况
        throw std::runtime_error("Error: Unknown ConstInitVal type");
    }
}

/// @brief 非终结运算符singleConstantInit的遍历
std::any SysYCSTVisitor::visitSingleConstantInit(SysYParser::SingleConstantInitContext * ctx)
{
    return visitConstExp(ctx->constExp());
}

/// @brief 非终结运算符arrayConstantInit的遍历
std::any SysYCSTVisitor::visitArrayConstantInit(SysYParser::ArrayConstantInitContext * ctx)
{
    ast_node * init_node = create_contain_node(ast_operator_type::AST_OP_ARRAY_INIT);

    for (auto initVal: ctx->constInitVal()) {
        auto val_node = std::any_cast<ast_node *>(visitConstInitVal(initVal));
        init_node->insert_son_node(val_node);
    }

    return init_node;
}

/// @brief 非终结运算符varDecl的遍历
std::any SysYCSTVisitor::visitVarDecl(SysYParser::VarDeclContext * ctx)
{
    ast_node * stmt_node = create_contain_node(ast_operator_type::AST_OP_DECL_STMT);
    type_attr typeAttr = std::any_cast<type_attr>(visitBasicType(ctx->basicType()));

    for (auto varDef: ctx->varDef()) {
        auto defNode = std::any_cast<ast_node *>(visitVarDef(varDef));
        ast_node * type_node = create_type_node(typeAttr);
        ast_node * decl_node = ast_node::New(ast_operator_type::AST_OP_VAR_DECL, type_node, defNode, nullptr);
        stmt_node->insert_son_node(decl_node);
    }

    return stmt_node;
}

/// @brief 非终结运算符varDef的遍历
std::any SysYCSTVisitor::visitVarDef(SysYParser::VarDefContext * ctx)
{
    if (Instanceof(simpleVarCtx, SysYParser::SimpleVarDefContext *, ctx)) {
        // 处理简单变量定义 Ident ('[' constExp ']')*
        return visitSimpleVarDef(simpleVarCtx);
    } else if (Instanceof(initializedVarCtx, SysYParser::InitializedVarDefContext *, ctx)) {
        // 处理初始化变量定义 Ident ('[' constExp ']')* '=' initVal
        return visitInitializedVarDef(initializedVarCtx);
    }
    return nullptr;
}

/// @brief 非终结运算符simpleVarDef的遍历
std::any SysYCSTVisitor::visitSimpleVarDef(SysYParser::SimpleVarDefContext * ctx)
{
    std::string varName = ctx->Ident()->getText();
    ast_node * id_node = ast_node::New(varName, ctx->Ident()->getSymbol()->getLine());

    if (!ctx->constExp().empty()) {
        ast_node * dims_node = create_contain_node(ast_operator_type::AST_OP_ARRAY_DIMS);
        for (auto dim: ctx->constExp()) {
            auto dim_node = std::any_cast<ast_node *>(visitConstExp(dim));
            dims_node->insert_son_node(dim_node);
        }
        return ast_node::New(ast_operator_type::AST_OP_VAR_DEF, id_node, dims_node, nullptr);
    } else {
        return ast_node::New(ast_operator_type::AST_OP_VAR_DEF, id_node, nullptr, nullptr);
    }
}

/// @brief 非终结运算符initializedVarDef的遍历
std::any SysYCSTVisitor::visitInitializedVarDef(SysYParser::InitializedVarDefContext * ctx)
{
    std::string varName = ctx->Ident()->getText();
    ast_node * id_node = ast_node::New(varName, ctx->Ident()->getSymbol()->getLine());

    ast_node * dims_node = nullptr;
    if (!ctx->constExp().empty()) {
        dims_node = create_contain_node(ast_operator_type::AST_OP_ARRAY_DIMS);
        for (auto dim: ctx->constExp()) {
            auto dim_node = std::any_cast<ast_node *>(visitConstExp(dim));
            dims_node->insert_son_node(dim_node);
        }
    }

    auto init_node = std::any_cast<ast_node *>(visitInitVal(ctx->initVal()));

    if (dims_node) {
        return ast_node::New(ast_operator_type::AST_OP_VAR_DEF, id_node, dims_node, init_node);
    } else {
        return ast_node::New(ast_operator_type::AST_OP_VAR_DEF, id_node, init_node, nullptr);
    }
}

/// @brief 非终结运算符initVal的遍历
std::any SysYCSTVisitor::visitInitVal(SysYParser::InitValContext * ctx)
{
    if (Instanceof(singleVarInitCtx, SysYParser::SingleVarInitContext *, ctx)) {
        return visitSingleVarInit(singleVarInitCtx);
    } else if (Instanceof(arrayVarInitCtx, SysYParser::ArrayVarInitContext *, ctx)) {
        return visitArrayVarInit(arrayVarInitCtx);
    }
    return nullptr;
}

/// @brief 非终结运算符singleVarInit的遍历
std::any SysYCSTVisitor::visitSingleVarInit(SysYParser::SingleVarInitContext * ctx)
{
    return visitExp(ctx->exp());
}

/// @brief 非终结运算符arrayVarInit的遍历
std::any SysYCSTVisitor::visitArrayVarInit(SysYParser::ArrayVarInitContext * ctx)
{
    ast_node * init_node = create_contain_node(ast_operator_type::AST_OP_ARRAY_INIT);

    for (auto initVal: ctx->initVal()) {
        auto val_node = std::any_cast<ast_node *>(visitInitVal(initVal));
        init_node->insert_son_node(val_node);
    }

    return init_node;
}

/// @brief 非终结运算符funcDef的遍历
std::any SysYCSTVisitor::visitFuncDef(SysYParser::FuncDefContext * ctx)
{
    type_attr funcReturnType;
    funcReturnType.lineno = ctx->funcType()->getStart()->getLine();
    if (ctx->funcType()->getText() == "int") {
        funcReturnType.type = BasicType::TYPE_INT;
    } else if (ctx->funcType()->getText() == "float") {
        funcReturnType.type = BasicType::TYPE_FLOAT;
    } else if (ctx->funcType()->getText() == "void") {
        funcReturnType.type = BasicType::TYPE_VOID;
    } else {
        // 处理其他类型
        throw std::runtime_error("Error: Unknown function return type");
    }

    char * id = strdup(ctx->Ident()->getText().c_str());
    var_id_attr funcId{id, (int64_t) ctx->Ident()->getSymbol()->getLine()};

    ast_node * formalParamsNode = nullptr;
    if (ctx->funcFParams()) {
        formalParamsNode = std::any_cast<ast_node *>(visitFuncFParams(ctx->funcFParams()));
    }

    auto blockNode = std::any_cast<ast_node *>(visitBlock(ctx->block()));

    return create_func_def(funcReturnType, funcId, blockNode, formalParamsNode);
}

/// @brief 非终结运算符funcFParams的遍历
std::any SysYCSTVisitor::visitFuncFParams(SysYParser::FuncFParamsContext * ctx)
{
    ast_node * paramsNode = create_contain_node(ast_operator_type::AST_OP_FUNC_FORMAL_PARAMS);

    for (auto param: ctx->funcFParam()) {
        auto paramNode = std::any_cast<ast_node *>(visitFuncFParam(param));
        paramsNode->insert_son_node(paramNode);
    }

    return paramsNode;
}

/// @brief 非终结运算符funcFParam的遍历
std::any SysYCSTVisitor::visitFuncFParam(SysYParser::FuncFParamContext * ctx)
{
    type_attr typeAttr = std::any_cast<type_attr>(visitBasicType(ctx->basicType()));
    ast_node * typeNode = create_type_node(typeAttr);

    std::string paramName = ctx->Ident()->getText();
    ast_node * idNode = ast_node::New(paramName, ctx->Ident()->getSymbol()->getLine());

    if (ctx->getText().find('[') != std::string::npos) {
        // 数组参数
        ast_node * dimsNode = create_contain_node(ast_operator_type::AST_OP_ARRAY_DIMS);
        return ast_node::New(ast_operator_type::AST_OP_FUNC_FORMAL_PARAM, typeNode, idNode, dimsNode);
    } else {
        // 普通参数
        return ast_node::New(ast_operator_type::AST_OP_FUNC_FORMAL_PARAM, typeNode, idNode, nullptr);
    }
}

/// @brief 非终结运算符block的遍历
std::any SysYCSTVisitor::visitBlock(SysYParser::BlockContext * ctx)
{
    ast_node * blockNode = create_contain_node(ast_operator_type::AST_OP_BLOCK);

    for (auto item: ctx->blockItem()) {
        auto itemNode = std::any_cast<ast_node *>(visitBlockItem(item));
        if (itemNode) {
            blockNode->insert_son_node(itemNode);
        }
    }

    return blockNode;
}

/// @brief 非终结运算符blockItem的遍历
std::any SysYCSTVisitor::visitBlockItem(SysYParser::BlockItemContext * ctx)
{
    if (Instanceof(declCtx, SysYParser::DeclarationBlockItemContext *, ctx)) {
        return visitDeclarationBlockItem(declCtx);
    } else if (Instanceof(stmtCtx, SysYParser::StatementBlockItemContext *, ctx)) {
        return visitStatementBlockItem(stmtCtx);
    } else {
        // 处理其他情况
        throw std::runtime_error("Error: Unknown block item type");
    }
}

/// @brief 非终结运算符declarationBlockItem的遍历
std::any SysYCSTVisitor::visitDeclarationBlockItem(SysYParser::DeclarationBlockItemContext * ctx)
{
    return visitDecl(ctx->decl());
}

/// @brief 非终结运算符statementBlockItem的遍历
std::any SysYCSTVisitor::visitStatementBlockItem(SysYParser::StatementBlockItemContext * ctx)
{
    return visitStmt(ctx->stmt());
}

/// @brief 非终结运算符stmt的遍历
std::any SysYCSTVisitor::visitStmt(SysYParser::StmtContext * ctx)
{
    if (Instanceof(assignmentCtx, SysYParser::AssignmentStatementContext *, ctx)) {
        return visitAssignmentStatement(assignmentCtx);
    } else if (Instanceof(expressionCtx, SysYParser::ExpressionStatementContext *, ctx)) {
        return visitExpressionStatement(expressionCtx);
    } else if (Instanceof(nestedBlockCtx, SysYParser::NestedBlockStatementContext *, ctx)) {
        return visitNestedBlockStatement(nestedBlockCtx);
    } else if (Instanceof(ifCtx, SysYParser::IfStatementContext *, ctx)) {
        return visitIfStatement(ifCtx);
    } else if (Instanceof(whileCtx, SysYParser::WhileStatementContext *, ctx)) {
        return visitWhileStatement(whileCtx);
    } else if (Instanceof(breakCtx, SysYParser::BreakStatementContext *, ctx)) {
        return visitBreakStatement(breakCtx);
    } else if (Instanceof(continueCtx, SysYParser::ContinueStatementContext *, ctx)) {
        return visitContinueStatement(continueCtx);
    } else if (Instanceof(returnCtx, SysYParser::ReturnStatementContext *, ctx)) {
        return visitReturnStatement(returnCtx);
    } else {
        // 处理其他情况
        throw std::runtime_error("Error: Unknown statement type");
    }
}

/// @brief 非终结运算符assignmentStatement的遍历
std::any SysYCSTVisitor::visitAssignmentStatement(SysYParser::AssignmentStatementContext * ctx)
{
    auto lval = std::any_cast<ast_node *>(visitLVal(ctx->lVal()));
    auto expr = std::any_cast<ast_node *>(visitExp(ctx->exp()));
    return ast_node::New(ast_operator_type::AST_OP_ASSIGN, lval, expr, nullptr);
}

/// @brief 非终结运算符expressionStatement的遍历
std::any SysYCSTVisitor::visitExpressionStatement(SysYParser::ExpressionStatementContext * ctx)
{
    if (ctx->exp()) {
        return visitExp(ctx->exp());
    }
    return nullptr;
}

/// @brief 非终结运算符nestedBlockStatement的遍历
std::any SysYCSTVisitor::visitNestedBlockStatement(SysYParser::NestedBlockStatementContext * ctx)
{
    return visitBlock(ctx->block());
}

/// @brief 非终结运算符ifStatement的遍历
std::any SysYCSTVisitor::visitIfStatement(SysYParser::IfStatementContext * ctx)
{
    auto cond = std::any_cast<ast_node *>(visitCond(ctx->cond()));
    auto thenStmt = std::any_cast<ast_node *>(visitStmt(ctx->stmt(0)));

    if (ctx->stmt().size() > 1) {
        // 处理else语句
        auto elseStmt = std::any_cast<ast_node *>(visitStmt(ctx->stmt(1)));
        return ast_node::New(ast_operator_type::AST_OP_IF, cond, thenStmt, elseStmt);
    } else {
        return ast_node::New(ast_operator_type::AST_OP_IF, cond, thenStmt, nullptr);
    }
}

/// @brief 非终结运算符whileStatement的遍历
std::any SysYCSTVisitor::visitWhileStatement(SysYParser::WhileStatementContext * ctx)
{
    auto cond = std::any_cast<ast_node *>(visitCond(ctx->cond()));
    auto stmt = std::any_cast<ast_node *>(visitStmt(ctx->stmt()));
    return ast_node::New(ast_operator_type::AST_OP_WHILE, cond, stmt, nullptr);
}

/// @brief 非终结运算符breakStatement的遍历
std::any SysYCSTVisitor::visitBreakStatement(SysYParser::BreakStatementContext * ctx)
{
    return create_contain_node(ast_operator_type::AST_OP_BREAK);
}

/// @brief 非终结运算符continueStatement的遍历
std::any SysYCSTVisitor::visitContinueStatement(SysYParser::ContinueStatementContext * ctx)
{
    return create_contain_node(ast_operator_type::AST_OP_CONTINUE);
}

/// @brief 非终结运算符returnStatement的遍历
std::any SysYCSTVisitor::visitReturnStatement(SysYParser::ReturnStatementContext * ctx)
{
    if (ctx->exp()) {
        auto expr = std::any_cast<ast_node *>(visitExp(ctx->exp()));
        return ast_node::New(ast_operator_type::AST_OP_RETURN, expr, nullptr, nullptr);
    } else {
        return create_contain_node(ast_operator_type::AST_OP_RETURN);
    }
}

/// @brief 非终结运算符exp的遍历
std::any SysYCSTVisitor::visitExp(SysYParser::ExpContext * ctx)
{
    return visitAddExp(ctx->addExp());
}

/// @brief 非终结运算符cond的遍历
std::any SysYCSTVisitor::visitCond(SysYParser::CondContext * ctx)
{
    // 识别产生式 cond: lOrExp;
    return visitLOrExp(ctx->lOrExp());
}

/// @brief 非终结运算符lVal的遍历
std::any SysYCSTVisitor::visitLVal(SysYParser::LValContext * ctx)
{
    std::string varName = ctx->Ident()->getText();
    ast_node * idNode = ast_node::New(varName, ctx->Ident()->getSymbol()->getLine());

    if (!ctx->exp().empty()) {
        ast_node * indicesNode = create_contain_node(ast_operator_type::AST_OP_ARRAY_INDICES);
        for (auto exp: ctx->exp()) {
            auto indexNode = std::any_cast<ast_node *>(visitExp(exp));
            indicesNode->insert_son_node(indexNode);
        }
        return ast_node::New(ast_operator_type::AST_OP_LVAL, idNode, indicesNode, nullptr);
    } else {
        return ast_node::New(ast_operator_type::AST_OP_LVAL, idNode, nullptr, nullptr);
    }
}

/// @brief 非终结运算符primaryExp的遍历
std::any SysYCSTVisitor::visitPrimaryExp(SysYParser::PrimaryExpContext * ctx)
{
    if (Instanceof(groupedExpCtx, SysYParser::GroupedExpressionContext *, ctx)) {
        return visitGroupedExpression(groupedExpCtx);
    } else if (Instanceof(leftValueExpCtx, SysYParser::LeftValueExpressionContext *, ctx)) {
        return visitLeftValueExpression(leftValueExpCtx);
    } else if (Instanceof(numberExpCtx, SysYParser::NumberExpressionContext *, ctx)) {
        return visitNumberExpression(numberExpCtx);
    } else {
        // 处理其他情况
        throw std::runtime_error("Error: Unknown primary expression type");
    }
}

/// @brief 非终结运算符groupedExpression的遍历
std::any SysYCSTVisitor::visitGroupedExpression(SysYParser::GroupedExpressionContext * ctx)
{
    return visitExp(ctx->exp());
}

/// @brief 非终结运算符leftValueExpression的遍历
std::any SysYCSTVisitor::visitLeftValueExpression(SysYParser::LeftValueExpressionContext * ctx)
{
    return visitLVal(ctx->lVal());
}

/// @brief 非终结运算符numberExpression的遍历
std::any SysYCSTVisitor::visitNumberExpression(SysYParser::NumberExpressionContext * ctx)
{
    return visitNumber(ctx->number());
}

/// @brief 非终结运算符number的遍历
std::any SysYCSTVisitor::visitNumber(SysYParser::NumberContext * ctx)
{
    if (ctx->IntConst()) {
        // 处理整型常量
        std::string intStr = ctx->IntConst()->getText();
        int64_t value;

        if (intStr.find("0x") == 0 || intStr.find("0X") == 0) {
            // 十六进制
            value = std::stoll(intStr.substr(2), nullptr, 16);
        } else if (intStr[0] == '0') {
            // 八进制
            value = std::stoll(intStr, nullptr, 8);
        } else {
            // 十进制
            value = std::stoll(intStr);
        }

        return ast_node::New(digit_int_attr{(uint32_t) value, (int64_t) ctx->IntConst()->getSymbol()->getLine()});
    } else {
        // 处理浮点型常量
        double value = std::stod(ctx->FloatConst()->getText());
        return ast_node::New(digit_real_attr{value, (int64_t) ctx->FloatConst()->getSymbol()->getLine()});
    }
}

/// @brief 非终结运算符unaryExp的遍历
std::any SysYCSTVisitor::visitUnaryExp(SysYParser::UnaryExpContext * ctx)
{
    if (Instanceof(primaryUnaryExpCtx, SysYParser::PrimaryUnaryExpressionContext *, ctx)) {
        return visitPrimaryUnaryExpression(primaryUnaryExpCtx);
    } else if (Instanceof(functionCallCtx, SysYParser::FunctionCallContext *, ctx)) {
        return visitFunctionCall(functionCallCtx);
    } else if (Instanceof(unaryOperatorExpCtx, SysYParser::UnaryOperatorExpressionContext *, ctx)) {
        return visitUnaryOperatorExpression(unaryOperatorExpCtx);
    } else {
        // 处理其他情况
        throw std::runtime_error("Error: Unknown unary expression type");
    }
}

/// @brief 非终结运算符primaryUnaryExpression的遍历
std::any SysYCSTVisitor::visitPrimaryUnaryExpression(SysYParser::PrimaryUnaryExpressionContext * ctx)
{
    return visitPrimaryExp(ctx->primaryExp());
}

/// @brief 非终结运算符functionCall的遍历
std::any SysYCSTVisitor::visitFunctionCall(SysYParser::FunctionCallContext * ctx)
{
    std::string funcName = ctx->Ident()->getText();
    ast_node * funcIdNode = ast_node::New(funcName, ctx->Ident()->getSymbol()->getLine());

    ast_node * argsNode = nullptr;
    if (ctx->funcRParams()) {
        argsNode = std::any_cast<ast_node *>(visitFuncRParams(ctx->funcRParams()));
    }

    return ast_node::New(ast_operator_type::AST_OP_FUNC_CALL, funcIdNode, argsNode, nullptr);
}

/// @brief 非终结运算符unaryOperatorExpression的遍历
std::any SysYCSTVisitor::visitUnaryOperatorExpression(SysYParser::UnaryOperatorExpressionContext * ctx)
{
    ast_operator_type op;
    std::string opStr = ctx->unaryOp()->getText();
    if (opStr == "+") {
        op = ast_operator_type::AST_OP_POS;
    } else if (opStr == "-") {
        op = ast_operator_type::AST_OP_NEG;
    } else {
        op = ast_operator_type::AST_OP_NOT;
    }

    auto expr = std::any_cast<ast_node *>(visitUnaryExp(ctx->unaryExp()));
    return ast_node::New(op, expr, nullptr, nullptr);
}

/// @brief 非终结运算符unaryOp的遍历
std::any SysYCSTVisitor::visitUnaryOp(SysYParser::UnaryOpContext * ctx)
{
    std::string opStr = ctx->getText();
    ast_operator_type op;
    if (opStr == "+") {
        op = ast_operator_type::AST_OP_POS;
    } else if (opStr == "-") {
        op = ast_operator_type::AST_OP_NEG;
    } else if (opStr == "!") {
        op = ast_operator_type::AST_OP_NOT;
    } else if (opStr == "&") {
        op = ast_operator_type::AST_OP_AND;
    } else if (opStr == "*") {
        op = ast_operator_type::AST_OP_MUL;
    } else {
        // 处理其他情况
        throw std::runtime_error("Error: Unknown unary operator");
    }

    return op;
}

/// @brief 非终结运算符funcRParams的遍历
std::any SysYCSTVisitor::visitFuncRParams(SysYParser::FuncRParamsContext * ctx)
{
    ast_node * paramsNode = create_contain_node(ast_operator_type::AST_OP_FUNC_REAL_PARAMS);

    for (auto exp: ctx->exp()) {
        auto paramNode = std::any_cast<ast_node *>(visitExp(exp));
        paramsNode->insert_son_node(paramNode);
    }

    return paramsNode;
}

/// @brief 非终结运算符mulExp的遍历
std::any SysYCSTVisitor::visitMulExp(SysYParser::MulExpContext * ctx)
{
    // 识别产生式 mulExp: unaryExp | mulExp ('*' | '/' | '%') unaryExp;
    if (!ctx->mulExp()) {
        // 没有mulExp，处理 unaryExp
        return visitUnaryExp(ctx->unaryExp());
    } else {
        // 处理 mulExp ('*' | '/' | '%') unaryExp
        auto left = std::any_cast<ast_node *>(visitMulExp(ctx->mulExp()));
        auto right = std::any_cast<ast_node *>(visitUnaryExp(ctx->unaryExp()));
        if (ctx->children[1]->getText() == "*") {
            return ast_node::New(ast_operator_type::AST_OP_MUL, left, right, nullptr);
        } else if (ctx->children[1]->getText() == "/") {
            return ast_node::New(ast_operator_type::AST_OP_DIV, left, right, nullptr);
        } else if (ctx->children[1]->getText() == "%") {
            return ast_node::New(ast_operator_type::AST_OP_MOD, left, right, nullptr);
        } else {
            throw std::runtime_error("Unknown multiplication operator: " + ctx->children[1]->getText());
        }
    }
}

/// @brief 非终结运算符addExp的遍历
std::any SysYCSTVisitor::visitAddExp(SysYParser::AddExpContext * ctx)
{
    // 识别产生式 addExp: mulExp | addExp ('+' | '-') mulExp;
    if (!ctx->addExp()) {
        // 没有addExp，处理 mulExp
        return visitMulExp(ctx->mulExp());
    } else {
        // 处理 addExp ('+' | '-') mulExp
        auto left = std::any_cast<ast_node *>(visitAddExp(ctx->addExp()));
        auto right = std::any_cast<ast_node *>(visitMulExp(ctx->mulExp()));
        if (ctx->children[1]->getText() == "+") {
            return ast_node::New(ast_operator_type::AST_OP_ADD, left, right, nullptr);
        } else if (ctx->children[1]->getText() == "-") {
            return ast_node::New(ast_operator_type::AST_OP_SUB, left, right, nullptr);
        } else {
            throw std::runtime_error("Unknown addition operator: " + ctx->children[1]->getText());
        }
    }
}

/// @brief 非终结运算符relExp的遍历
std::any SysYCSTVisitor::visitRelExp(SysYParser::RelExpContext * ctx)
{
    // 识别产生式 relExp: addExp | relExp ('<' | '>' | '<=' | '>=') addExp;
    if (!ctx->relExp()) {
        // 没有relExp，处理 addExp
        return visitAddExp(ctx->addExp());
    } else {
        // 处理 relExp ('<' | '>' | '<=' | '>=') addExp
        auto left = std::any_cast<ast_node *>(visitRelExp(ctx->relExp()));
        auto right = std::any_cast<ast_node *>(visitAddExp(ctx->addExp()));
        if (ctx->children[1]->getText() == "<") {
            return ast_node::New(ast_operator_type::AST_OP_LT, left, right, nullptr);
        } else if (ctx->children[1]->getText() == ">") {
            return ast_node::New(ast_operator_type::AST_OP_GT, left, right, nullptr);
        } else if (ctx->children[1]->getText() == "<=") {
            return ast_node::New(ast_operator_type::AST_OP_LE, left, right, nullptr);
        } else if (ctx->children[1]->getText() == ">=") {
            return ast_node::New(ast_operator_type::AST_OP_GE, left, right, nullptr);
        } else {
            throw std::runtime_error("Unknown relational operator: " + ctx->children[1]->getText());
        }
    }
}

/// @brief 非终结运算符eqExp的遍历
std::any SysYCSTVisitor::visitEqExp(SysYParser::EqExpContext * ctx)
{
    // 识别产生式 eqExp: relExp | eqExp ('==' | '!=') relExp;
    if (!ctx->eqExp()) {
        // 没有eqExp，处理 relExp
        return visitRelExp(ctx->relExp());
    } else {
        // 处理 eqExp ('==' | '!=') relExp
        auto left = std::any_cast<ast_node *>(visitEqExp(ctx->eqExp()));
        auto right = std::any_cast<ast_node *>(visitRelExp(ctx->relExp()));
        if (ctx->children[1]->getText() == "==") {
            return ast_node::New(ast_operator_type::AST_OP_EQ, left, right, nullptr);
        } else if (ctx->children[1]->getText() == "!=") {
            return ast_node::New(ast_operator_type::AST_OP_NE, left, right, nullptr);
        } else {
            throw std::runtime_error("Unknown equality operator: " + ctx->children[1]->getText());
        }
    }
}

/// @brief 非终结运算符lAndExp的遍历
std::any SysYCSTVisitor::visitLAndExp(SysYParser::LAndExpContext * ctx)
{
    // 识别产生式 lAndExp: eqExp | lAndExp '&&' eqExp;
    if (!ctx->lAndExp()) {
        // 没有lAndExp，处理 eqExp
        return visitEqExp(ctx->eqExp());
    } else {
        // 处理 lAndExp '&&' eqExp
        auto left = std::any_cast<ast_node *>(visitLAndExp(ctx->lAndExp()));
        auto right = std::any_cast<ast_node *>(visitEqExp(ctx->eqExp()));
        return ast_node::New(ast_operator_type::AST_OP_AND, left, right, nullptr);
    }
}

/// @brief 非终结运算符lOrExp的遍历
std::any SysYCSTVisitor::visitLOrExp(SysYParser::LOrExpContext * ctx)
{
    // 识别产生式 lOrExp: lAndExp | lOrExp '||' lAndExp;

    if (!ctx->lOrExp()) {
        // 没有lOrExp，处理 lAndExp
        return visitLAndExp(ctx->lAndExp());
    } else {
        // 处理 lOrExp '||' lAndExp
        auto left = std::any_cast<ast_node *>(visitLOrExp(ctx->lOrExp()));
        auto right = std::any_cast<ast_node *>(visitLAndExp(ctx->lAndExp()));
        return ast_node::New(ast_operator_type::AST_OP_OR, left, right, nullptr);
    }
}

/// @brief 非终结运算符constExp的遍历
std::any SysYCSTVisitor::visitConstExp(SysYParser::ConstExpContext * ctx)
{
    return visitAddExp(ctx->addExp());
}

/// @brief 非终结运算符basicType的遍历
std::any SysYCSTVisitor::visitBasicType(SysYParser::BasicTypeContext * ctx)
{
    type_attr attr;
    attr.lineno = ctx->getStart()->getLine();

    std::string typeText = ctx->getText();
    if (typeText == "int") {
        attr.type = BasicType::TYPE_INT;
    } else if (typeText == "float") {
        attr.type = BasicType::TYPE_FLOAT;
    } else if (typeText == "void") {
        attr.type = BasicType::TYPE_VOID;
    } else {
        throw std::runtime_error("Unknown basic type: " + typeText);
    }

    return attr;
}

/// @brief 非终结运算符funcType的遍历
std::any SysYCSTVisitor::visitFuncType(SysYParser::FuncTypeContext * ctx)
{
    type_attr attr;
    attr.lineno = ctx->getStart()->getLine();

    std::string typeText = ctx->getText();
    if (typeText == "int") {
        attr.type = BasicType::TYPE_INT;
    } else if (typeText == "float") {
        attr.type = BasicType::TYPE_FLOAT;
    } else if (typeText == "void") {
        attr.type = BasicType::TYPE_VOID;
    } else {
        throw std::runtime_error("Unknown function type: " + typeText);
    }

    return attr;
}