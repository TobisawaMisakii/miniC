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
#include "BranchConditional.h"

/// @brief 构造函数
/// @param _root AST的根
/// @param _module 符号表
IRGenerator::IRGenerator(ast_node * _root, Module * _module) : root(_root), module(_module)
{
    /* 叶子节点 */
    ast2ir_handlers[ast_operator_type::AST_OP_LEAF_LITERAL_UINT] = &IRGenerator::ir_leaf_node_uint;
    ast2ir_handlers[ast_operator_type::AST_OP_LEAF_VAR_ID] = &IRGenerator::ir_leaf_node_var_id;
    ast2ir_handlers[ast_operator_type::AST_OP_LEAF_TYPE] = &IRGenerator::ir_leaf_node_type;
    ast2ir_handlers[ast_operator_type::AST_OP_LEAF_LITERAL_FLOAT] = &IRGenerator::ir_leaf_node_float;

    /* 表达式运算， 加减 */
    ast2ir_handlers[ast_operator_type::AST_OP_SUB] = &IRGenerator::ir_sub;
    ast2ir_handlers[ast_operator_type::AST_OP_ADD] = &IRGenerator::ir_add;
    ast2ir_handlers[ast_operator_type::AST_OP_MUL] = &IRGenerator::ir_mul;
    ast2ir_handlers[ast_operator_type::AST_OP_DIV] = &IRGenerator::ir_div;
    ast2ir_handlers[ast_operator_type::AST_OP_MOD] = &IRGenerator::ir_mod;

    //单目运算符
    // ast2ir_handlers[ast_operator_type::AST_OP_POS] = &IRGenerator::ir_pos;
    // ast2ir_handlers[ast_operator_type::AST_OP_NEG] = &IRGenerator::ir_neg;
    // ast2ir_handlers[ast_operator_type::AST_OP_NOT] = &IRGenerator::ir_not;

    // 关系表达式
    ast2ir_handlers[ast_operator_type::AST_OP_EQ] = &IRGenerator::ir_eq;
    ast2ir_handlers[ast_operator_type::AST_OP_NE] = &IRGenerator::ir_ne;
    ast2ir_handlers[ast_operator_type::AST_OP_LT] = &IRGenerator::ir_lt;
    ast2ir_handlers[ast_operator_type::AST_OP_LE] = &IRGenerator::ir_le;
    ast2ir_handlers[ast_operator_type::AST_OP_GT] = &IRGenerator::ir_gt;
    ast2ir_handlers[ast_operator_type::AST_OP_GE] = &IRGenerator::ir_ge;

    // 逻辑表达式
    // ast2ir_handlers[ast_operator_type::AST_OP_AND] = &IRGenerator::ir_and;
    // ast2ir_handlers[ast_operator_type::AST_OP_OR] = &IRGenerator::ir_or;

    /* 语句 */
    ast2ir_handlers[ast_operator_type::AST_OP_ASSIGN] = &IRGenerator::ir_assign;
    ast2ir_handlers[ast_operator_type::AST_OP_RETURN] = &IRGenerator::ir_return;
    ast2ir_handlers[ast_operator_type::AST_OP_BREAK] = &IRGenerator::ir_break;
    ast2ir_handlers[ast_operator_type::AST_OP_CONTINUE] = &IRGenerator::ir_continue;
    ast2ir_handlers[ast_operator_type::AST_OP_IF] = &IRGenerator::ir_if;
    ast2ir_handlers[ast_operator_type::AST_OP_WHILE] = &IRGenerator::ir_while;
    ast2ir_handlers[ast_operator_type::AST_OP_EMPTY] = &IRGenerator::ir_empty;

    /* 函数调用 */
    ast2ir_handlers[ast_operator_type::AST_OP_FUNC_CALL] = &IRGenerator::ir_function_call;
    // ast2ir_handlers[ast_operator_type::AST_OP_FUNC_REAL_PARAMS] = &IRGenerator::ir_function_real_params;

    /* 函数定义 */
    ast2ir_handlers[ast_operator_type::AST_OP_FUNC_DEF] = &IRGenerator::ir_function_define;
    ast2ir_handlers[ast_operator_type::AST_OP_FUNC_FORMAL_PARAMS] = &IRGenerator::ir_function_formal_params;

    /* 变量定义语句 */
    ast2ir_handlers[ast_operator_type::AST_OP_DECL_STMT] = &IRGenerator::ir_declare_statment;
    ast2ir_handlers[ast_operator_type::AST_OP_VAR_DECL] = &IRGenerator::ir_variable_declare;
    ast2ir_handlers[ast_operator_type::AST_OP_CONST_DECL] = &IRGenerator::ir_const_declare;
    ast2ir_handlers[ast_operator_type::AST_OP_VAR_DEF] = &IRGenerator::ir_variable_define;
    ast2ir_handlers[ast_operator_type::AST_OP_CONST_DEF] = &IRGenerator::ir_const_define;

    // 左值
    ast2ir_handlers[ast_operator_type::AST_OP_LVAL] = &IRGenerator::ir_lval;

    // 数组, 不支持定义时初始化数组，维度处理处理节点还需要维度参数，索引直接在lval处理了，所以都不走visit
    // ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_DIMS] = &IRGenerator::ir_array_dims;
    // ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_INDICES] = &IRGenerator::ir_array_indices;
    // ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_INIT] = &IRGenerator::ir_array_init;

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
    if (!node) {
        minic_log(LOG_ERROR, "AST 根节点翻译失败");
        return false;
    }
    return true;
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
    minic_log(LOG_INFO, "Visit节点类型: %d, 名称: %s", static_cast<int>(node->node_type), node->name.c_str());
    bool result;

    std::unordered_map<ast_operator_type, ast2ir_handler_t>::const_iterator pIter;
    pIter = ast2ir_handlers.find(
        node->node_type); //在 ast2ir_handlers 映射表中查找键为 node->node_type 的元素,如果未找到，find()
                          //方法返回一个迭代器，指向找到的元素,则返回 end() 迭代器
                          // 打印调试信息

    if (pIter == ast2ir_handlers.end()) {
        // 没有找到，则说明当前不支持
        result = (this->ir_default)(node);
    } else {
        result = (this->*(pIter->second))(node);
    }

    if (!result) {
        // 语义解析错误，则出错返回
        minic_log(LOG_ERROR, "节点处理失败，类型: %d, 名称: %s", static_cast<int>(node->node_type), node->name.c_str());
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

    for (auto son: node->sons) {

        // 遍历编译单元，要么是函数定义，要么是语句
        ast_node * son_node = ir_visit_ast_node(son);
        if (!son_node) {
            // TODO 自行追加语义错误处理
            std::cout << "ir_compile_unit error" << '\n';
            return false;
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
        std::cout << "函数中嵌套定义函数 in IRGenerator" << std::endl;
        return false;
    }

    // 函数定义的AST包含四个孩子
    // 第一个孩子：函数返回类型
    // 第二个孩子：函数名字
    // 第三个孩子：形参列表
    // 第四个孩子：函数体即block
    ast_node * type_node = node->sons[0];
    ast_node * name_node = node->sons[1];
    ast_node * param_node = node->sons[2];
    ast_node * block_node = node->sons[3];

    // 创建一个新的函数定义，函数的返回类型设置为VOID，待定，必须等return时才能确定，目前可以是VOID或者INT类型
    // 请注意这个与C语言的函数定义不同。在实现MiniC编译器时必须调整
    Function * newFunc = module->newFunction(name_node->name, type_node->type);
    if (!newFunc) {
        // 新定义的函数已经存在，则失败返回。
        // TODO 自行追加语义错误处理
        std::cout << "新定义的函数已经存在 in IRGenerator" << std::endl;
        return false;
    }

    // 当前函数设置有效，变更为当前的函数
    module->setCurrentFunction(newFunc);

    // 进入函数的作用域
    module->enterScope();

    // 获取函数的IR代码列表，用于后面追加指令用，注意这里用的是引用传值
    InterCode & irCode = newFunc->getInterCode();

    // // 这里也可增加一个函数入口Label指令，便于后续基本块划分
    // LabelInstruction * entryLabelInst = new LabelInstruction(newFunc);
    // // 添加函数入口Label指令
    // irCode.addInst(entryLabelInst);

    // 创建并加入Entry入口指令
    irCode.addInst(new EntryInstruction(newFunc));

    // 创建出口指令并不加入出口指令，等函数内的指令处理完毕后加入出口指令
    LabelInstruction * exitLabelInst = new LabelInstruction(newFunc);

    // 函数出口指令保存到函数信息中，因为在语义分析函数体时return语句需要跳转到函数尾部，需要这个label指令
    newFunc->setExitLabel(exitLabelInst);

    // 遍历形参，没有IR指令，不需要追加
    result = ir_function_formal_params(param_node);
    if (!result) {
        // 形参解析失败
        // TODO 自行追加语义错误处理
        std::cout << "形参解析失败 in IRGenerator" << std::endl;
        return false;
    }
    node->blockInsts.addInst(param_node->blockInsts);

    // 新建一个Value，用于保存函数的返回值，如果没有返回值可不用申请
    LocalVariable * retValue = nullptr;
    if (!type_node->type->isVoidType()) {

        // 保存函数返回值变量到函数信息中，在return语句翻译时需要设置值到这个变量中
        retValue = static_cast<LocalVariable *>(module->newVarValue(type_node->type));
    }
    newFunc->setReturnValue(retValue);

    // 函数内已经进入作用域，内部不再需要做变量的作用域管理
    block_node->needScope = false;

    // 遍历block
    result = ir_block(block_node);
    if (!result) {
        // block解析失败
        // TODO 自行追加语义错误处理
        std::cout << "block解析失败 in IRGenerator" << std::endl;
        return false;
    }

    // IR指令追加到当前的节点中
    node->blockInsts.addInst(block_node->blockInsts);

    // 此时，所有指令都加入到当前函数中，也就是node->blockInsts

    // node节点的指令移动到函数的IR指令列表中
    irCode.addInst(node->blockInsts);

    // 添加函数出口Label指令，主要用于return语句跳转到这里进行函数的退出
    irCode.addInst(exitLabelInst);

    // 函数出口指令
    irCode.addInst(new ExitInstruction(newFunc, retValue));

    // 恢复成外部函数
    module->setCurrentFunction(nullptr);

    // 退出函数的作用域
    module->leaveScope();

    return true;
}

/// @brief 形式参数AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_function_formal_params(ast_node * node)
{
    // TODO 目前形参还不支持，直接返回true

    // 每个形参变量都创建对应的临时变量，用于表达实参转递的值
    // 而真实的形参则创建函数内的局部变量。
    // 然后产生赋值指令，用于把表达实参值的临时变量拷贝到形参局部变量上。
    // 请注意这些指令要放在Entry指令后面，因此处理的先后上要注意。

    // 获取当前正在处理的函数
    Function * currentFunc = module->getCurrentFunction();
    if (!currentFunc) {
        return false;
    }

    // 获取函数的IR代码列表
    InterCode & irCode = currentFunc->getInterCode();

    // 找到Entry指令的位置，新的指令要添加在Entry指令之后
    auto entryIter = irCode.getInsts().begin();
    if (entryIter == irCode.getInsts().end() || (*entryIter)->getOp() != IRInstOperator::IRINST_OP_ENTRY) {
        return false;
    }
    ++entryIter;

    // 遍历形参列表
    for (auto son: node->sons) {

        // 形参的类型和名称
        Type * paramType = son->sons[0]->type;
        std::string paramName = son->sons[1]->name;

        // 创建真实的形参局部变量
        LocalVariable * realParam = currentFunc->newLocalVarValue(paramType, paramName);

        // 创建临时变量用于表达实参传递的值
        LocalVariable * tempParam = currentFunc->newLocalVarValue(paramType);

        // 产生赋值指令，将临时变量的值拷贝到形参局部变量上
        MoveInstruction * movInst = new MoveInstruction(currentFunc, realParam, tempParam);

        // 将赋值指令插入到Entry指令之后
        irCode.getInsts().insert(entryIter, movInst);
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

    std::string funcName = node->sons[0]->name;
    int64_t lineno = node->sons[0]->line_no;

    ast_node * paramsNode = node->sons[1];

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
    // if (!paramsNode->sons.empty()) {
    if (nullptr != paramsNode) {

        int32_t argsCount = (int32_t) paramsNode->sons.size();

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

            realParams.push_back(temp->val);
            node->blockInsts.addInst(temp->blockInsts);
        }
    }

    // TODO 这里请追加函数调用的语义错误检查，这里只进行了函数参数的个数检查等，其它请自行追加。
    if (realParams.size() != calledFunction->getParams().size()) {
        // 函数参数的个数不一致，语义错误
        minic_log(LOG_ERROR, "第%lld行的被调用函数(%s)未定义或声明", (long long) lineno, funcName.c_str());
        return false;
    }

    // 返回调用有返回值，则需要分配临时变量，用于保存函数调用的返回值
    Type * type = calledFunction->getReturnType();

    FuncCallInstruction * funcCallInst = new FuncCallInstruction(currentFunc, calledFunction, realParams, type);

    // 创建函数调用指令
    node->blockInsts.addInst(funcCallInst);

    // 函数调用结果Value保存到node中，可能为空，上层节点可利用这个值
    node->val = funcCallInst;

    return true;
}

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
    ast_node * left = ir_visit_ast_node(src1_node);
    ast_node * right = ir_visit_ast_node(src2_node);
    // 检查操作数的值是否有效
    if (!left->val || !right->val) {
        minic_log(LOG_ERROR, "加法操作数的值未正确设置");
        return false;
    }
    // 左右值的处理ir,对于数组，要先计算地址，创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    //分别处理整数和浮点
    IRInstOperator op;
    Type * resultType;
    if (left->val->getType()->isFloatType() || right->val->getType()->isFloatType()) {
        op = IRInstOperator::IRINST_OP_ADD_F; // 浮点加法指令
        resultType = FloatType::getTypeFloat();
        // 需要确保0.1这样的常量被识别为float
    } else {
        op = IRInstOperator::IRINST_OP_ADD_I; // 整数加法指令
        resultType = IntegerType::getTypeInt();
    }
    BinaryInstruction * addInst =
        new BinaryInstruction(module->getCurrentFunction(), op, left->val, right->val, resultType);

    // 加法ir，创建临时变量保存IR的值，以及线性IR指令
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
    //分别处理整数和浮点
    IRInstOperator op;
    Type * resultType;
    if (left->val->getType()->isFloatType() || right->val->getType()->isFloatType()) {
        op = IRInstOperator::IRINST_OP_SUB_F; // 浮点加法指令
        resultType = FloatType::getTypeFloat();
        // 需要确保0.1这样的常量被识别为float
    } else {
        op = IRInstOperator::IRINST_OP_SUB_I; // 整数加法指令
        resultType = IntegerType::getTypeInt();
    }
    BinaryInstruction * subInst =
        new BinaryInstruction(module->getCurrentFunction(), op, left->val, right->val, resultType);

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
    printf("ir_mul is called\n");
    // 确保有两个操作数
    if (node->sons.size() != 2) {
        minic_log(LOG_ERROR, "乘法运算需要两个操作数");
        return false;
    }

    ast_node * left = ir_visit_ast_node(node->sons[0]);
    ast_node * right = ir_visit_ast_node(node->sons[1]);

    if (!left || !right) {
        minic_log(LOG_ERROR, "乘法操作数解析失败");
        return false;
    }

    //分别处理整数和浮点
    IRInstOperator op;
    Type * resultType;
    if (left->val->getType()->isFloatType() || right->val->getType()->isFloatType()) {
        op = IRInstOperator::IRINST_OP_MUL_F; // 浮点加法指令
        resultType = FloatType::getTypeFloat();
        // 需要确保0.1这样的常量被识别为float
    } else {
        op = IRInstOperator::IRINST_OP_MUL_I; // 整数加法指令
        resultType = IntegerType::getTypeInt();
    }

    BinaryInstruction * mulInst =
        new BinaryInstruction(module->getCurrentFunction(), op, left->val, right->val, resultType);

    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(mulInst);

    node->val = mulInst;
    printf("ir_mul is fianl\n");
    return true;
}

/// @brief 除法AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_div(ast_node * node)
{
    // 确保有两个操作数
    if (node->sons.size() != 2) {
        minic_log(LOG_ERROR, "除法运算需要两个操作数");
        return false;
    }

    ast_node * left = ir_visit_ast_node(node->sons[0]);
    ast_node * right = ir_visit_ast_node(node->sons[1]);

    if (!left || !right) {
        minic_log(LOG_ERROR, "除法操作数解析失败");
        return false;
    }

    // 分别处理整数和浮点
    IRInstOperator op;
    Type * resultType;
    if (left->val->getType()->isFloatType() || right->val->getType()->isFloatType()) {
        op = IRInstOperator::IRINST_OP_DIV_F; // 浮点除法指令
        resultType = FloatType::getTypeFloat();
    } else {
        op = IRInstOperator::IRINST_OP_DIV_I; // 整数除法指令
        resultType = IntegerType::getTypeInt();
    }

    BinaryInstruction * divInst =
        new BinaryInstruction(module->getCurrentFunction(), op, left->val, right->val, resultType);

    // 添加指令到当前块
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(divInst);

    // 设置节点的值
    node->val = divInst;

    return true;
}

/// @brief 取模AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_mod(ast_node * node)
{
    // 确保有两个操作数
    if (node->sons.size() != 2) {
        minic_log(LOG_ERROR, "取模运算需要两个操作数");
        return false;
    }

    ast_node * left = ir_visit_ast_node(node->sons[0]);
    ast_node * right = ir_visit_ast_node(node->sons[1]);

    if (!left || !right) {
        minic_log(LOG_ERROR, "取模操作数解析失败");
        return false;
    }

    // 取模只支持整数
    if (!left->val->getType()->isIntegerType() || !right->val->getType()->isIntegerType()) {
        minic_log(LOG_ERROR, "取模运算只支持整数类型");
        return false;
    }

    IRInstOperator op = IRInstOperator::IRINST_OP_MOD_I; // 整数取模指令
    Type * resultType = IntegerType::getTypeInt();

    BinaryInstruction * modInst =
        new BinaryInstruction(module->getCurrentFunction(), op, left->val, right->val, resultType);

    // 添加指令到当前块
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(modInst);

    // 设置节点的值
    node->val = modInst;

    return true;
}

/// @brief 赋值AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_assign(ast_node * node)
{
    if (node->sons.size() != 2) {
        minic_log(LOG_ERROR, "赋值语句需要两个操作数");
        return false;
    }
    ast_node * son1_node = node->sons[0];
    ast_node * son2_node = node->sons[1];

    // 赋值节点，自右往左运算

    // 赋值运算符的左侧操作数
    son1_node->store = true; //若为数组，则需要store
    ast_node * left = ir_visit_ast_node(son1_node);
    if (!left) {
        // 某个变量没有定值
        // 这里缺省设置变量不存在则创建，因此这里不会错误
        minic_log(LOG_ERROR, "赋值语句左操作数无效");
        return false;
    }

    // 赋值运算符的右侧操作数
    ast_node * right = ir_visit_ast_node(son2_node);
    if (!right) {
        // 某个变量没有定值
        minic_log(LOG_ERROR, "赋值语句右操作数无效");
        return false;
    }

    // TODO real number add
    MoveInstruction * movInst;
    if (left->val->getType()->isPointerType()) {
        movInst = new MoveInstruction(module->getCurrentFunction(), left->val, right->val, true); // store
    } else {
        movInst = new MoveInstruction(module->getCurrentFunction(), left->sons[0]->val, right->val);
    }
    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(movInst);

    // 这里假定赋值的类型是一致的
    node->val = movInst;

    return true;
}

bool IRGenerator::ir_lval(ast_node * node)
{
    if (node->sons.empty()) {
        minic_log(LOG_ERROR, "LVAL节点没有子节点");
        return false;
    }

    // 左值节点的第一个子节点通常是变量名
    ast_node * var_node = node->sons[0];
    if (!ir_visit_ast_node(var_node)) {
        minic_log(LOG_ERROR, "LVAL节点的子节点不是变量标识符");
        return false;
    }

    Value * resultVal = var_node->val;
    node->blockInsts.addInst(var_node->blockInsts);

    // 检查是否是数组访问
    if (node->sons.size() == 2 && node->sons[1]->node_type == ast_operator_type::AST_OP_ARRAY_INDICES) {
        // 获取数组的值
        Value * arrayValue = var_node->val;
        if (!arrayValue) {
            minic_log(LOG_ERROR, "数组变量未定义");
            return false;
        }

        // 获取数组类型
        Type * arrayVarType = arrayValue->getType();
        const ArrayType * arrayType = nullptr;

        // 处理数组变量可能是数组类型或指针类型的情况
        if (arrayVarType->isArrayType()) {
            arrayType = dynamic_cast<const ArrayType *>(arrayVarType);
        } else if (arrayVarType->isPointerType()) {
            const PointerType * ptrType = dynamic_cast<const PointerType *>(arrayVarType);
            if (ptrType && ptrType->getPointeeType()->isArrayType()) {
                arrayType = dynamic_cast<const ArrayType *>(ptrType->getPointeeType());
            }
        }

        if (!arrayType) {
            minic_log(LOG_ERROR, "无效的数组类型");
            return false;
        }

        // 解析索引表达式
        ast_node * indices_node = node->sons[1];
        std::vector<Value *> indices;
        for (auto index_node: indices_node->sons) {
            if (!ir_visit_ast_node(index_node)) {
                minic_log(LOG_ERROR, "数组索引解析失败");
                return false;
            }
            indices.push_back(index_node->val);
            node->blockInsts.addInst(index_node->blockInsts);
        }

        // 计算偏移量
        const auto & dims = arrayType->getDimensions();
        Value * totalOffset = module->newConstInt(0);
        Function * currentFunc = module->getCurrentFunction();
        Type * intType = IntegerType::getTypeInt();
        bool isFirstDim = true; // 添加标志位跟踪第一个维度
        const int elementSize = arrayType->getBaseType()->getSize();

        // 多维数组计算
        if (dims.size() > 1) {
            // 计算前n-1维的偏移
            for (size_t i = 0; i < indices.size() - 1; i++) {
                // 计算后续维度的乘积
                int32_t stride = 1;
                for (size_t j = i + 1; j < dims.size(); j++) {
                    stride *= dims[j];
                }

                BinaryInstruction * dimOffset = new BinaryInstruction(currentFunc,
                                                                      IRInstOperator::IRINST_OP_MUL_I,
                                                                      indices[i],
                                                                      module->newConstInt(stride),
                                                                      intType);
                node->blockInsts.addInst(dimOffset);

                // 累加到总偏移
                if (isFirstDim) {
                    totalOffset = dimOffset;
                    isFirstDim = false;
                } else {
                    BinaryInstruction * newOffset = new BinaryInstruction(currentFunc,
                                                                          IRInstOperator::IRINST_OP_ADD_I,
                                                                          totalOffset,
                                                                          dimOffset,
                                                                          intType);
                    node->blockInsts.addInst(newOffset);
                    totalOffset = newOffset;
                }
            }

            // 加上最后一维的索引
            BinaryInstruction * finalOffset = new BinaryInstruction(currentFunc,
                                                                    IRInstOperator::IRINST_OP_ADD_I,
                                                                    totalOffset,
                                                                    indices.back(),
                                                                    intType);
            node->blockInsts.addInst(finalOffset);

            // 乘以元素大小4字节
            BinaryInstruction * byteOffset = new BinaryInstruction(currentFunc,
                                                                   IRInstOperator::IRINST_OP_MUL_I,
                                                                   finalOffset,
                                                                   module->newConstInt(elementSize),
                                                                   intType);
            node->blockInsts.addInst(byteOffset);
            totalOffset = byteOffset;
        } else {
            // 一维数组直接计算
            BinaryInstruction * byteOffset = new BinaryInstruction(currentFunc,
                                                                   IRInstOperator::IRINST_OP_MUL_I,
                                                                   indices[0],
                                                                   module->newConstInt(elementSize),
                                                                   intType);
            node->blockInsts.addInst(byteOffset);
            totalOffset = byteOffset;
        }

        // 计算最终地址
        const PointerType * elemPtrType = PointerType::get(arrayType->getBaseType());
        BinaryInstruction * addrCalc =
            new BinaryInstruction(currentFunc,
                                  IRInstOperator::IRINST_OP_ADD_I,
                                  arrayValue,
                                  totalOffset,
                                  const_cast<Type *>(static_cast<const Type *>(elemPtrType)));
        node->blockInsts.addInst(addrCalc);

        resultVal = addrCalc;

        // 如果 store=false，则直接加载数组元素的值
        if (!node->store) {
            Value * temp = module->newVarValue(arrayType->getBaseType());
            MoveInstruction * loadInst = new MoveInstruction(currentFunc,
                                                             temp,
                                                             resultVal,
                                                             true,  // dereference
                                                             true); // load
            node->blockInsts.addInst(loadInst);
            resultVal = temp; // 更新为加载后的值
        }
    } else if (!node->store) {
        // 非数组变量，但需要加载值（如指针解引用）
        if (resultVal->getType()->isPointerType()) {
            Value * temp = module->newVarValue(resultVal->getType()->getBaseType());
            MoveInstruction * loadInst = new MoveInstruction(module->getCurrentFunction(),
                                                             temp,
                                                             resultVal,
                                                             true,  // dereference
                                                             true); // load
            node->blockInsts.addInst(loadInst);
            resultVal = temp; // 更新为加载后的值
        }
    }

    node->val = resultVal;
    return true;
}
/// @brief return节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_return(ast_node * node)
{
    ast_node * right = nullptr;

    // 获取当前函数
    Function * currentFunc = module->getCurrentFunction();
    if (!currentFunc) {
        minic_log(LOG_ERROR, "return语句不在函数内");
        return false;
    }

    // 获取函数的返回类型
    Type * returnType = currentFunc->getReturnType();

    // return语句可能没有表达式，也可能有，因此这里必须进行区分判断
    if (!node->sons.empty()) {
        ast_node * son_node = node->sons[0];

        // 翻译返回值表达式
        right = ir_visit_ast_node(son_node);
        if (!right || !right->val) {
            minic_log(LOG_ERROR, "return语句的返回值表达式无效");
            return false;
        }

        Value * returnValue = right->val;
        Type * valueType = returnValue->getType();

        // 普通类型检查
        if (valueType != returnType) {
            minic_log(LOG_ERROR,
                      "返回值类型(%s)与函数返回类型(%s)不匹配",
                      valueType->toString().c_str(),
                      returnType->toString().c_str());
            return false;
        }
        // 添加返回值的IR指令
        node->blockInsts.addInst(right->blockInsts);

        // 如果有返回值变量（非void函数），生成赋值指令
        if (currentFunc->getReturnValue()) {
            node->blockInsts.addInst(new MoveInstruction(currentFunc, currentFunc->getReturnValue(), returnValue));
        }
    }
    // 无返回值的处理
    else {
        if (!returnType->isVoidType()) {
            minic_log(LOG_ERROR, "非void函数必须提供返回值");
            return false;
        }
    }

    // 跳转到函数出口
    node->blockInsts.addInst(new GotoInstruction(currentFunc, currentFunc->getExitLabel()));

    // 设置节点的值
    node->val = right->val;
    node->val = right->val;
    return true;
}

/// @brief 类型叶子节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_leaf_node_type(ast_node * node)
{
    // 不需要做什么，直接从节点中获取即可。
    if (!node->type) {
        minic_log(LOG_ERROR, "类型节点未初始化");
        return false;
    }
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
    if (!val) {
        minic_log(LOG_ERROR, "变量(%s)未定义", node->name.c_str());
        return false;
    }
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
    if (!val) {
        minic_log(LOG_ERROR, "创建整数常量失败，值: %d", node->integer_val);
        return false;
    }
    node->val = val;
    return true;
}

/// @brief 浮点数字面量叶子节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_leaf_node_float(ast_node * node)
{
    ConstFloat * val;

    // 新建一个浮点常量Value
    val = module->newConstFloat(node->float_val);
    if (!val) {
        minic_log(LOG_ERROR, "创建浮点常量失败，值: %f", node->float_val);
        return false;
    }
    node->val = val;
    return true;
}

/// @brief 变量声明语句节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_declare_statment(ast_node * node)
{
    if (node->sons.empty()) {
        minic_log(LOG_ERROR, "声明节点没有子节点");
        return false;
    }
    bool result = true;
    // 获取唯一的子节点
    ast_node * variable_declare_node = node->sons[0];
    // 判断子节点类型并处理
    if (!ir_visit_ast_node(variable_declare_node)) {
        minic_log(LOG_ERROR, "不支持的声明类型: %d", static_cast<int>(variable_declare_node->node_type));
        return false;
    }
    node->blockInsts.addInst(variable_declare_node->blockInsts);
    return result;
}
/// @brief 处理单个常量声明节点，生成对应的IR。
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_const_declare(ast_node * node)
{
    if (node->sons.size() < 2) {
        minic_log(LOG_ERROR, "常量声明节点的子节点数量不足");
        return false;
    }

    // 第一个子节点是类型节点
    ast_node * type_node = node->sons[0];
    if (!ir_visit_ast_node(type_node)) {
        minic_log(LOG_ERROR, "常量声明的类型节点无效");
        return false;
    }

    // 遍历所有 const_def 节点
    for (size_t i = 1; i < node->sons.size(); ++i) {
        ast_node * const_def_node = node->sons[i];
        if (!ir_visit_ast_node(const_def_node)) {
            minic_log(LOG_ERROR, "常量定义失败");
            return false;
        }
        node->blockInsts.addInst(const_def_node->blockInsts);
    }

    return true;
}
/// @brief 处理单个常量定义节点，生成对应的IR。
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_const_define(ast_node * node)
{
    if (node->sons.empty()) {
        minic_log(LOG_ERROR, "常量定义节点没有子节点");
        return false;
    }

    if (!node->parent->sons[0]->type) {
        minic_log(LOG_ERROR, "未指定常量类型");
        return false;
    }

    // 第一个子节点是常量名
    ast_node * const_name_node = node->sons[0];
    std::string constName = const_name_node->name;
    Type * constType = node->parent->sons[0]->type;

    if (const_name_node->node_type != ast_operator_type::AST_OP_LEAF_VAR_ID) {
        minic_log(LOG_ERROR, "常量定义的常量名节点无效");
        return false;
    }

    // 检查常量是否已在当前作用域中声明
    if (module->findVarValue(constName)) {
        minic_log(LOG_ERROR, "常量(%s)重复声明", constName.c_str());
        return false;
    }

    // 创建常量
    Value * constValue = module->newVarValue(constType, constName);
    if (!constValue) {
        minic_log(LOG_ERROR, "常量(%s)创建失败", constName.c_str());
        return false;
    }

    node->val = constValue;
    const_name_node->val = constValue;

    // 检查是否有初始化
    if (node->sons.size() > 1) {
        // 处理初始化表达式
        ast_node * init_expr_node = node->sons[1];
        if (!ir_visit_ast_node(init_expr_node)) {
            minic_log(LOG_ERROR, "常量初始化表达式翻译失败");
            return false;
        }

        // 类型转换检查
        if (!Type::canConvert(init_expr_node->val->getType(), constType)) {
            minic_log(LOG_ERROR,
                      "无法将类型%d赋给类型%d",
                      init_expr_node->val->getType()->getTypeID(),
                      constType->getTypeID());
            return false;
        }

        // 生成赋值指令
        MoveInstruction * movInst = new MoveInstruction(module->getCurrentFunction(), constValue, init_expr_node->val);
        // 添加指令到当前块
        node->blockInsts.addInst(init_expr_node->blockInsts);
        node->blockInsts.addInst(movInst);
    } else {
        minic_log(LOG_ERROR, "常量(%s)必须初始化", constName.c_str());
        return false;
    }

    return true;
}

/// @brief 处理单个变量声明节点，生成对应的IR。
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_variable_declare(ast_node * node)
{
    if (node->sons.size() < 2) {
        minic_log(LOG_ERROR, "变量声明节点的子节点数量不足");
        return false;
    }
    // 第一个子节点是类型节点
    ast_node * type_node = node->sons[0];
    if (!ir_visit_ast_node(type_node)) {
        minic_log(LOG_ERROR, "变量声明的类型节点无效");
        return false;
    }
    // 遍历所有 var_def 节点
    for (size_t i = 1; i < node->sons.size(); ++i) {
        ast_node * var_def_node = node->sons[i];
        if (!ir_visit_ast_node(var_def_node)) {
            minic_log(LOG_ERROR, "变量定义失败");
            return false;
        }
        node->blockInsts.addInst(var_def_node->blockInsts);
    }

    return true;
}

/// @brief 处理单个变量定义节点，生成对应的IR。
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_variable_define(ast_node * node)
{
    if (node->sons.empty()) {
        minic_log(LOG_ERROR, "变量定义节点没有子节点");
        return false;
    }
    if (!node->parent->sons[0]->type) {
        minic_log(LOG_ERROR, "未指定变量类型");
        return false;
    }

    // 第一个子节点是变量名
    ast_node * var_name_node = node->sons[0];
    std::string varName = var_name_node->name;
    Type * varType = node->parent->sons[0]->type;
    if (var_name_node->node_type != ast_operator_type::AST_OP_LEAF_VAR_ID) {
        minic_log(LOG_ERROR, "变量定义的变量名节点无效");
        return false;
    }
    // 检查变量是否已在当前作用域中声明
    if (module->findVarValue(varName)) {
        minic_log(LOG_ERROR, "变量(%s)重复声明", varName.c_str());
        return false;
    }

    // 检查是否为数组声明
    if (node->sons.size() > 1 && node->sons[1]->node_type == ast_operator_type::AST_OP_ARRAY_DIMS) {
        // 解析数组维度
        std::vector<int32_t> dimensions;
        if (!ir_array_dims(node->sons[1], dimensions)) {
            minic_log(LOG_ERROR, "数组(%s)的维度处理失败", varName.c_str());
            return false;
        }
        // 创建数组变量
        Value * arrayValue = module->newArrayValue(varType, varName, dimensions);
        if (!arrayValue) {
            minic_log(LOG_ERROR, "数组(%s)创建失败", varName.c_str());
            return false;
        }
        node->val = arrayValue;
        var_name_node->val = arrayValue;
        //是否初始化
        if (node->sons.size() == 3) {
            if (!ir_visit_ast_node(node->sons[2])) {
                minic_log(LOG_ERROR, "数组(%s)的初始化处理失败", varName.c_str());
                return false;
            }
            return true;
        }
        return true;
    }
    // 非数组变量处理

    Value * varValue;
    varValue = module->newVarValue(varType, varName);
    node->val = varValue;
    var_name_node->val = varValue;
    if (!varValue) {
        minic_log(LOG_ERROR, "变量(%s)创建失败", varName.c_str());
        return false;
    }
    // 检查是否有初始化
    if (node->sons.size() > 1) {
        // 处理初始化表达式
        ast_node * init_expr_node = node->sons[1];
        if (!ir_visit_ast_node(init_expr_node)) {
            minic_log(LOG_ERROR, "初始化表达式翻译失败");
            return false;
        }
        // 类型转换检查
        if (!Type::canConvert(var_name_node->val->getType(), varType)) {
            minic_log(LOG_ERROR,
                      "无法将类型%d赋给类型%d",
                      var_name_node->val->getType()->getTypeID(),
                      varType->getTypeID());
            return false;
        }
        // 生成赋值指令
        MoveInstruction * movInst = new MoveInstruction(module->getCurrentFunction(), varValue, init_expr_node->val);
        // 添加指令到当前块
        node->blockInsts.addInst(init_expr_node->blockInsts);
        node->blockInsts.addInst(var_name_node->blockInsts);
        node->blockInsts.addInst(movInst);
    }
    return true;
}

bool IRGenerator::ir_array_dims(ast_node * node, std::vector<int32_t> & dimensions)
{
    for (auto dim_node: node->sons) {
        if (!ir_visit_ast_node(dim_node)) {
            minic_log(LOG_ERROR, "数组维度节点翻译失败");
            return false;
        }

        // 确保维度是一个常量整数
        if (!dim_node->val || !dim_node->val->getType()->isIntegerType()) {
            minic_log(LOG_ERROR, "数组维度必须是整数常量");
            return false;
        }

        // 获取维度值
        ConstInt * constDim = dynamic_cast<ConstInt *>(dim_node->val);
        if (!constDim) {
            minic_log(LOG_ERROR, "数组维度解析失败");
            return false;
        }

        dimensions.push_back(constDim->getVal());
    }

    return true;
}
bool IRGenerator::ir_array_init(ast_node * node)
{
    Value * arrayValue = node->parent->val;
    if (!arrayValue->getType()->isArrayType()) {
        minic_log(LOG_ERROR, "初始化的目标不是数组类型");
        return false;
    }

    ArrayType * arrayType = dynamic_cast<ArrayType *>(arrayValue->getType());
    if (!arrayType) {
        minic_log(LOG_ERROR, "数组类型解析失败");
        return false;
    }

    // const std::vector<int32_t> & dimensions = arrayType->getDimensions();
    size_t totalSize = arrayType->getTotalSize();

    // 检查初始化值的数量是否匹配
    if (node->sons.size() > totalSize) {
        minic_log(LOG_ERROR, "数组初始化值的数量超过数组大小");
        return false;
    }

    // 遍历初始化值
    size_t index = 0;
    for (auto init_node: node->sons) {
        if (!ir_visit_ast_node(init_node)) {
            minic_log(LOG_ERROR, "数组初始化值翻译失败");
            return false;
        }

        // 类型检查
        if (!Type::canConvert(init_node->val->getType(), arrayType->getBaseType())) {
            minic_log(LOG_ERROR, "数组初始化值的类型与数组基础类型不匹配");
            return false;
        }
        // 获取指针类型
        PointerType * pointerType = new PointerType(arrayType->getBaseType());
        // 生成存储指令
        Value * elementAddr = new BinaryInstruction(module->getCurrentFunction(),
                                                    IRInstOperator::IRINST_OP_ADD_I,
                                                    arrayValue,
                                                    module->newConstInt(index * arrayType->getBaseType()->getSize()),
                                                    pointerType);

        MoveInstruction * movInst = new MoveInstruction(module->getCurrentFunction(), elementAddr, init_node->val);
        node->blockInsts.addInst(init_node->blockInsts);
        node->blockInsts.addInst(movInst);

        ++index;
    }

    return true;
}

/// @brief empty stmtAST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_empty(ast_node * node)
{
    // 空语句不需要做任何处理
    return true;
}

/// @brief if语句AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_if(ast_node * node)
{
    // if语句包含2个或3个子节点
    // 第一个子节点是条件表达式
    // 第二个子节点是if语句的语句块
    // 第三个可选子节点是else语句的语句块

    if (node->sons.size() < 2 || node->sons.size() > 3) {
        minic_log(LOG_ERROR, "if语句的子节点数量不正确");
        return false;
    }

    ast_node * condNode = node->sons[0];                                      // 条件表达式
    ast_node * thenNode = node->sons[1];                                      // then分支
    ast_node * elseNode = (node->sons.size() == 3) ? node->sons[2] : nullptr; // 可选的else分支

    // 处理条件表达式
    ast_node * cond = ir_visit_ast_node(condNode);
    if (!cond) {
        minic_log(LOG_ERROR, "if语句的条件表达式翻译失败");
        return false;
    }
    // 检查条件表达式的值是否有效
    if (!cond->val) {
        minic_log(LOG_ERROR, "if语句的条件表达式值无效");
        return false;
    }
    // 检查条件表达式的类型是否为布尔类型
    if (!cond->val->getType()->isInt1Byte()) {
        minic_log(LOG_ERROR, "if语句的条件表达式类型错误,不是bool类型");
        return false;
    }

    // 获取当前函数
    Function * currentFunc = module->getCurrentFunction();
    if (!currentFunc) {
        return false;
    }

    // 标签指令，用于跳转
    LabelInstruction * elseLabelInst = elseNode ? new LabelInstruction(currentFunc) : nullptr;
    LabelInstruction * thenLabelInst = new LabelInstruction(currentFunc);
    LabelInstruction * endLabelInst = new LabelInstruction(currentFunc);

    // 创建条件跳转指令，如果cond->val为0，则跳转到elseLabel(如果没有就是endLable)，否则跳转到thenLabel
    BranchCondInstruction * condGotoInst =
        new BranchCondInstruction(currentFunc, cond->val, thenLabelInst, elseLabelInst ? elseLabelInst : endLabelInst);

    node->blockInsts.addInst(cond->blockInsts);
    node->blockInsts.addInst(condGotoInst);

    // 处理then分支
    node->blockInsts.addInst(thenLabelInst);
    if (!ir_visit_ast_node(thenNode)) {
        minic_log(LOG_ERROR, "if语句的then分支翻译失败");
        return false;
    }
    node->blockInsts.addInst(thenNode->blockInsts);
    // then 执行完毕后需要跳过else，跳转到end（如果有else）
    if (elseNode) {
        node->blockInsts.addInst(new GotoInstruction(currentFunc, endLabelInst));
    }

    // 添加else分支的Label指令
    if (elseNode) {
        node->blockInsts.addInst(elseLabelInst);
        // 处理else分支
        if (!ir_visit_ast_node(elseNode)) {
            minic_log(LOG_ERROR, "if语句的else分支翻译失败");
            return false;
        }
        node->blockInsts.addInst(elseNode->blockInsts);
    }

    // 添加end分支的Label指令
    node->blockInsts.addInst(endLabelInst);

    return true;
}

/// @brief while语句AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_while(ast_node * node)
{
    // while语句包含2个子节点
    // 第一个子节点是条件表达式
    // 第二个子节点是while语句的语句块

    if (node->sons.size() != 2) {
        minic_log(LOG_ERROR, "while语句的子节点数量不正确");
        return false;
    }
    ast_node * condNode = node->sons[0];  // 条件表达式
    ast_node * blockNode = node->sons[1]; // 语句块

    // 获取当前函数及其IR代码
    Function * currentFunc = module->getCurrentFunction();
    if (!currentFunc) {
        return false;
    }
    // InterCode & irCode = currentFunc->getInterCode();

    // 标签指令，用于跳转
    LabelInstruction * condLabelInst = new LabelInstruction(currentFunc);
    LabelInstruction * bodyLabelInst = new LabelInstruction(currentFunc);
    LabelInstruction * endLabelInst = new LabelInstruction(currentFunc);

    // 添加条件判断的Label指令
    node->blockInsts.addInst(condLabelInst);

    // 处理条件判断
    ast_node * cond = ir_visit_ast_node(condNode);
    if (!cond) {
        minic_log(LOG_ERROR, "while语句的条件表达式翻译失败");
        return false;
    }
    // 检查条件表达式的值是否有效
    if (!cond->val) {
        minic_log(LOG_ERROR, "while语句的条件表达式值无效");
        return false;
    }

    node->blockInsts.addInst(cond->blockInsts);

    // ======= 记录loop label目标 =======
    LoopContext loopContext;
    loopContext.continueTarget = condLabelInst;
    loopContext.breakTarget = endLabelInst;
    loopLabelStack.push(loopContext);

    // 创建条件跳转指令，如果cond->val为0，则跳转到endLabel，否则按顺序进入bodyLabel
    BranchCondInstruction * condGotoInst =
        new BranchCondInstruction(currentFunc, cond->val, bodyLabelInst, endLabelInst);
    node->blockInsts.addInst(condGotoInst);

    // 添加body分支的Label指令，进入循环体
    node->blockInsts.addInst(bodyLabelInst);
    // 处理while语句块
    if (!ir_visit_ast_node(blockNode)) {
        minic_log(LOG_ERROR, "while语句的语句块翻译失败");
        loopLabelStack.pop(); // 弹出以防出错造成污染
        return false;
    }
    node->blockInsts.addInst(blockNode->blockInsts);
    // 回跳条件判断
    node->blockInsts.addInst(new GotoInstruction(currentFunc, condLabelInst));
    // 循环结束标签
    node->blockInsts.addInst(endLabelInst);

    // ======= 循环结束，弹出本循环loop label目标 =======
    loopLabelStack.pop();

    return true;
}

/// @brief break语句AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_break(ast_node * node)
{
    // 获取当前函数
    Function * currentFunc = module->getCurrentFunction();
    if (!currentFunc) {
        minic_log(LOG_ERROR, "break语句不在函数内");
        return false;
    }

    // 找到当前循环对应的end label
    if (loopLabelStack.empty()) {
        minic_log(LOG_ERROR, "break语句不在循环内");
        return false;
    }
    LabelInstruction * endLabel = loopLabelStack.top().breakTarget;

    // 添加跳转到循环结束的指令
    node->blockInsts.addInst(new GotoInstruction(currentFunc, endLabel));

    return true;
}

/// @brief continue语句AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_continue(ast_node * node)
{
    // 获取当前函数
    Function * currentFunc = module->getCurrentFunction();
    if (!currentFunc) {
        minic_log(LOG_ERROR, "continue语句不在函数内");
        return false;
    }

    // 获取当前loop的continue entry laebl
    if (loopLabelStack.empty()) {
        minic_log(LOG_ERROR, "continue语句不在循环内");
        return false;
    }
    LabelInstruction * continueLabel = loopLabelStack.top().continueTarget;

    // 添加跳转到循环条件判断的指令
    node->blockInsts.addInst(new GotoInstruction(currentFunc, continueLabel));

    return true;
}

/// @brief less than节点处理
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_lt(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    ast_node * left = ir_visit_ast_node(src1_node);
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!left || !right || !left->val || !right->val) {
        minic_log(LOG_ERROR, "less than操作数解析失败");
        return false;
    }
    if (left->val->getType() != right->val->getType()) {
        minic_log(LOG_ERROR, "less than操作数类型不一致");
        return false;
    }

    BinaryInstruction * ltInst = nullptr;

    if (!left->val->getType()->isIntegerType() || !right->val->getType()->isIntegerType()) {
        // 类型转换
        if (!Type::canConvert(left->val->getType(), right->val->getType())) {
            minic_log(LOG_ERROR, "less than操作数类型不一致");
            return false;
        }
        // 这里可以进行类型转换
        // left->val = new CastInstruction(module->getCurrentFunction(), left->val, FloatType::getTypeFloat());
        // right->val = new CastInstruction(module->getCurrentFunction(), right->val, FloatType::getTypeFloat());
        ltInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_FCMP_LT,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    } else if (left->val->getType()->isIntegerType() || right->val->getType()->isIntegerType()) {
        ltInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_ICMP_LT,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    }

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(ltInst);

    node->val = ltInst;

    return true;
}

/// @brief greater than节点处理
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_gt(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    ast_node * left = ir_visit_ast_node(src1_node);
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!left || !right || !left->val || !right->val) {
        minic_log(LOG_ERROR, "greater than操作数解析失败");
        return false;
    }
    if (left->val->getType() != right->val->getType()) {
        minic_log(LOG_ERROR, "greater than操作数类型不一致");
        return false;
    }

    BinaryInstruction * gtInst = nullptr;

    if (!left->val->getType()->isIntegerType() || !right->val->getType()->isIntegerType()) {
        // 类型转换
        if (!Type::canConvert(left->val->getType(), right->val->getType())) {
            minic_log(LOG_ERROR, "greater than操作数类型不一致");
            return false;
        }
        // 这里可以进行类型转换
        // left->val = new CastInstruction(module->getCurrentFunction(), left->val, FloatType::getTypeFloat());
        // right->val = new CastInstruction(module->getCurrentFunction(), right->val, FloatType::getTypeFloat());
        gtInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_FCMP_GT,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    } else if (left->val->getType()->isIntegerType() || right->val->getType()->isIntegerType()) {
        gtInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_ICMP_GT,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    }

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(gtInst);

    node->val = gtInst;

    return true;
}

/// @brief less than equal节点处理
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_le(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    ast_node * left = ir_visit_ast_node(src1_node);
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!left || !right || !left->val || !right->val) {
        minic_log(LOG_ERROR, "less than equal操作数解析失败");
        return false;
    }
    if (left->val->getType() != right->val->getType()) {
        minic_log(LOG_ERROR, "less than equal操作数类型不一致");
        return false;
    }

    BinaryInstruction * leInst = nullptr;

    if (!left->val->getType()->isIntegerType() || !right->val->getType()->isIntegerType()) {
        // 类型转换
        if (!Type::canConvert(left->val->getType(), right->val->getType())) {
            minic_log(LOG_ERROR, "less than equal操作数类型不一致");
            return false;
        }
        // 这里可以进行类型转换
        // left->val = new CastInstruction(module->getCurrentFunction(), left->val, FloatType::getTypeFloat());
        // right->val = new CastInstruction(module->getCurrentFunction(), right->val, FloatType::getTypeFloat());
        leInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_FCMP_LE,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    } else if (left->val->getType()->isIntegerType() || right->val->getType()->isIntegerType()) {
        leInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_ICMP_LE,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    }

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(leInst);

    node->val = leInst;

    return true;
}

/// @brief greater than equal节点处理
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_ge(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    ast_node * left = ir_visit_ast_node(src1_node);
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!left || !right || !left->val || !right->val) {
        minic_log(LOG_ERROR, "greater than equal操作数解析失败");
        return false;
    }
    if (left->val->getType() != right->val->getType()) {
        minic_log(LOG_ERROR, "greater than equal操作数类型不一致");
        return false;
    }

    BinaryInstruction * geInst = nullptr;

    if (!left->val->getType()->isIntegerType() || !right->val->getType()->isIntegerType()) {
        // 类型转换
        if (!Type::canConvert(left->val->getType(), right->val->getType())) {
            minic_log(LOG_ERROR, "greater than equal操作数类型不一致");
            return false;
        }
        // 这里可以进行类型转换
        // left->val = new CastInstruction(module->getCurrentFunction(), left->val, FloatType::getTypeFloat());
        // right->val = new CastInstruction(module->getCurrentFunction(), right->val, FloatType::getTypeFloat());
        geInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_FCMP_GE,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    } else if (left->val->getType()->isIntegerType() || right->val->getType()->isIntegerType()) {
        geInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_ICMP_GE,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    }

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(geInst);

    node->val = geInst;

    return true;
}

/// @brief equal节点处理
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_eq(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    // ==节点，（如果允许多个==连接）可能需要考虑结合性
    ast_node * left = ir_visit_ast_node(src1_node);
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!left || !right || !left->val || !right->val) {
        minic_log(LOG_ERROR, "equal操作数解析失败");
        return false;
    }
    if (left->val->getType() != right->val->getType()) {
        minic_log(LOG_ERROR, "equal操作数类型不一致");
        return false;
    }

    BinaryInstruction * eqInst = nullptr;

    if (!left->val->getType()->isIntegerType() || !right->val->getType()->isIntegerType()) {
        // 类型转换
        if (!Type::canConvert(left->val->getType(), right->val->getType())) {
            minic_log(LOG_ERROR, "equal操作数类型不一致");
            return false;
        }
        // 这里可以进行类型转换
        // left->val = new CastInstruction(module->getCurrentFunction(), left->val, FloatType::getTypeFloat());
        // right->val = new CastInstruction(module->getCurrentFunction(), right->val, FloatType::getTypeFloat());
        eqInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_FCMP_EQ,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    } else if (left->val->getType()->isIntegerType() || right->val->getType()->isIntegerType()) {
        eqInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_ICMP_EQ,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    }

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(eqInst);

    node->val = eqInst;

    return true;
}

/// @brief not equal节点处理
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_ne(ast_node * node)
{
    ast_node * src1_node = node->sons[0];
    ast_node * src2_node = node->sons[1];

    ast_node * left = ir_visit_ast_node(src1_node);
    ast_node * right = ir_visit_ast_node(src2_node);
    if (!left || !right || !left->val || !right->val) {
        minic_log(LOG_ERROR, "not equal操作数解析失败");
        return false;
    }
    if (left->val->getType() != right->val->getType()) {
        minic_log(LOG_ERROR, "not equal操作数类型不一致");
        return false;
    }

    BinaryInstruction * neInst = nullptr;

    if (!left->val->getType()->isIntegerType() || !right->val->getType()->isIntegerType()) {
        // 类型转换
        if (!Type::canConvert(left->val->getType(), right->val->getType())) {
            minic_log(LOG_ERROR, "not equal操作数类型不一致");
            return false;
        }
        // 这里可以进行类型转换
        // left->val = new CastInstruction(module->getCurrentFunction(), left->val, FloatType::getTypeFloat());
        // right->val = new CastInstruction(module->getCurrentFunction(), right->val, FloatType::getTypeFloat());
        neInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_FCMP_NE,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    } else if (left->val->getType()->isIntegerType() || right->val->getType()->isIntegerType()) {
        neInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_ICMP_NE,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    }

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    node->blockInsts.addInst(neInst);

    node->val = neInst;

    return true;
}
