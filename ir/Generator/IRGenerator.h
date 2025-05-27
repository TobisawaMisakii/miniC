///
/// @file IRGenerator.h
/// @brief AST遍历产生线性IR的头文件
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

#include <unordered_map>
#include <stack>

#include "AST.h"
#include "Module.h"
#include "../ir/Instructions/LabelInstruction.h"

/// @brief AST遍历产生线性IR类
class IRGenerator {

public:
    /// @brief 构造函数
    /// @param root
    /// @param _module
    IRGenerator(ast_node * root, Module * _module);

    /// @brief 析构函数
    ~IRGenerator() = default;

    /// @brief 运行产生IR
    bool run();

    /// @brief while语句的label记录
    struct LoopContext {
        LabelInstruction * continueTarget; // 通常是循环条件的起始
        LabelInstruction * breakTarget;    // 通常是循环结束处
    };

protected:
    /// @brief 编译单元AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_compile_unit(ast_node * node);

    /// @brief 宏定义AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_macro_decl(ast_node * node);

    /// @brief 函数定义AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_function_define(ast_node * node);

    /// @brief 形式参数AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_function_formal_params(ast_node * node);

    /// @brief 函数调用AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_function_call(ast_node * node);

    /// @brief 实参列表AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    // bool ir_function_real_params(ast_node * node);

    /// @brief 语句块（含函数体）AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_block(ast_node * node);

    /// @brief 加法AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_add(ast_node * node);

    /// @brief 减法AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_sub(ast_node * node);

    /// @brief 乘法AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_mul(ast_node * node);

    /// @brief 除法AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_div(ast_node * node);

    /// @brief 取模AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_mod(ast_node * node);

    /// @brief 赋值AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_assign(ast_node * node);

    /// @brief 左值AST节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_lval(ast_node * node);

    /// @brief return节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_return(ast_node * node);

    /// @brief empty stmt节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_empty(ast_node * node);

    /// @brief 类型叶子节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_leaf_node_type(ast_node * node);

    /// @brief 标识符叶子节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_leaf_node_var_id(ast_node * node);

    /// @brief 无符号整数字面量叶子节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_leaf_node_uint(ast_node * node);

    /// @brief float数字面量叶子节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_leaf_node_float(ast_node * node);

    /// @brief 变量声明语句节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_declare_statment(ast_node * node);

    /// @brief 变量的声明节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_variable_declare(ast_node * node);

    /// @brief 变量的定义节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_variable_define(ast_node * node);

    /// @brief 数组的维度节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_array_dims(ast_node * node, std::vector<int32_t> & dimensions);

    bool ir_array_indices(ast_node * node);

    /// @brief 数组的初始化节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_array_init(ast_node * node);

    /// @brief 常量的声明节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_const_declare(ast_node * node);

    /// @brief 常量的定义节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_const_define(ast_node * node);

    /// @brief if节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_if(ast_node * node);

    /// @brief while节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_while(ast_node * node);

    /// @brief break节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_break(ast_node * node);

    /// @brief continue节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_continue(ast_node * node);

    /// @brief less than节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_lt(ast_node * node);

    /// @brief less than equal节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_le(ast_node * node);

    /// @brief greater than节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_gt(ast_node * node);

    /// @brief greater than equal节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_ge(ast_node * node);

    /// @brief equal节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_eq(ast_node * node);

    /// @brief not equal节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_ne(ast_node * node);

    /// @brief condition节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_condition(ast_node * node, LabelInstruction * trueLabel, LabelInstruction * falseLabel);

    /// @brief and节点翻译成线性中间IR
    /// @param node AST节点，真/假 出口标签指令
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_and(ast_node * node, LabelInstruction * trueExitLabel, LabelInstruction * falseEixtLabel);

    /// @brief or节点翻译成线性中间IR
    /// @param node AST节点，真/假 出口标签指令
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_or(ast_node * node, LabelInstruction * trueExitLabel, LabelInstruction * falseEixtLabel);

    /// @brief pos（正号）节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_pos(ast_node * node);

    /// @brief neg（负号）节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_neg(ast_node * node);

    /// @brief not节点翻译成线性中间IR
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_not(ast_node * node);

    /// @brief 未知节点类型的节点处理
    /// @param node AST节点
    /// @return 翻译是否成功，true：成功，false：失败
    bool ir_default(ast_node * node);

    /// @brief 根据AST的节点运算符查找对应的翻译函数并执行翻译动作
    /// @param node AST节点
    /// @return 成功返回node节点，否则返回nullptr
    ast_node * ir_visit_ast_node(ast_node * node);

    /// @brief AST的节点操作函数
    typedef bool (IRGenerator::*ast2ir_handler_t)(ast_node *);

    /// @brief AST节点运算符与动作函数关联的映射表
    std::unordered_map<ast_operator_type, ast2ir_handler_t> ast2ir_handlers;

private:
    /// @brief 抽象语法树的根
    ast_node * root;

    /// @brief 符号表:模块
    Module * module;

    /// @brief while loop 的标签栈，为break和continue服务
    std::stack<LoopContext> loopLabelStack;
};