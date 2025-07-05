///
/// @file AST.h
/// @brief 抽象语法树AST管理的头文件
/// @author zenglj (zenglj@live.com)
/// @version 1.2
/// @date 2025-04-22
///
/// @copyright Copyright (c) 2025
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-11-21 <td>1.0     <td>zenglj  <td>初始版本
/// <tr><td>2024-11-23 <td>1.1     <td>zenglj  <td>表达式增强
/// <tr><td>2025-04-22 <td>1.2     <td>TobisawaMisakii <td>完整支持SysY语言规范
/// </table>
///
#pragma once

#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

#include "AttrType.h"
#include "IRCode.h"
#include "Value.h"
#include "VoidType.h"

///
/// @brief AST节点的类型
///
enum class ast_operator_type : int {
    /* 叶子节点类型 */
    AST_OP_LEAF_LITERAL_UINT,  // 无符号整数字面量0
    AST_OP_LEAF_LITERAL_FLOAT, // 浮点数字面量
    AST_OP_LEAF_VAR_ID,        // 变量ID
    AST_OP_LEAF_TYPE,          // 类型节点3

    /* 声明和定义节点 */
    AST_OP_COMPILE_UNIT,       // 编译单元4
    AST_OP_MACRO_DECL,         // 宏定义
    AST_OP_MACRO_VALUE,        // 宏值
    AST_OP_MACRO_CALL,         // 宏调用
    AST_OP_FUNC_DEF,           // 函数定义
    AST_OP_FUNC_FORMAL_PARAMS, // 形参列表
    AST_OP_FUNC_FORMAL_PARAM,  // 形参
    AST_OP_FUNC_CALL,          // 函数调用
    AST_OP_FUNC_REAL_PARAMS,   // 实参列表
    AST_OP_DECL_STMT,          // 声明语句
    AST_OP_VAR_DECL,           // 变量声明
    AST_OP_CONST_DECL,         // 常量声明
    AST_OP_VAR_DEF,            // 变量定义
    AST_OP_CONST_DEF,          // 常量定义14

    /* 控制流节点 */
    AST_OP_BLOCK,    // 语句块15
    AST_OP_IF,       // if语句
    AST_OP_WHILE,    // while语句
    AST_OP_BREAK,    // break语句
    AST_OP_CONTINUE, // continue语句
    AST_OP_RETURN,   // return语句20

    /* 表达式节点 */
    AST_OP_ASSIGN,        // 赋值21
    AST_OP_LVAL,          // 左值
    AST_OP_ARRAY_DIMS,    // 数组维度
    AST_OP_ARRAY_INDICES, // 数组索引
    AST_OP_ARRAY_INIT,    // 数组初始化25

    /* 运算符节点 */
    AST_OP_POS, // 正号26
    AST_OP_NEG, // 负号
    AST_OP_NOT, // 逻辑非
    AST_OP_ADD, // 加法
    AST_OP_SUB, // 减法30
    AST_OP_MUL, // 乘法
    AST_OP_DIV, // 除法
    AST_OP_MOD, // 取模
    AST_OP_LT,  // 小于
    AST_OP_GT,  // 大于35
    AST_OP_LE,  // 小于等于
    AST_OP_GE,  // 大于等于
    AST_OP_EQ,  // 等于
    AST_OP_NE,  // 不等于
    AST_OP_AND, // 逻辑与40
    AST_OP_OR,  // 逻辑或

    AST_OP_EMPTY, // 空语句
    AST_OP_MAX    // 最大标识符
};

///
/// @brief 抽象语法树AST的节点描述类
///
class ast_node {
public:
    ast_operator_type node_type; // 节点类型
    int64_t line_no;             // 行号信息
    Type * type;                 // 节点值的类型
    bool store; //该节点是否可以store, 即是否为赋值语句的左值，至于是否为数组或指针，在左值节点判断
    union {
        uint32_t integer_val; // 整数值
        float float_val;      // 浮点值
    };
    std::string float_str;
    std::string name;             // 变量名或函数名
    ast_node * parent;            // 父节点
    std::vector<ast_node *> sons; // 子节点
    InterCode blockInsts;         // 线性IR指令块，可包含多条IR指令，用于线性IR指令产生用
    Value * val = nullptr;        // 线性IR指令或者运行产生的Value，用于线性IR指令产生用
    bool needScope = true;        // 是否需要作用域管理， 默认需要

    /// @brief 构造函数
    ast_node(ast_operator_type _node_type,
             Type * _type = VoidType::getType(),
             int64_t _line_no = -1,
             bool store = false);

    /// @brief 类型节点构造函数
    ast_node(Type * _type);

    /// @brief 整数字面量构造函数
    ast_node(digit_int_attr attr);

    /// @brief 浮点数字面量构造函数
    ast_node(digit_real_attr attr);

    /// @brief 标识符构造函数
    ast_node(var_id_attr attr);

    /// @brief 标识符构造函数
    ast_node(std::string id, int64_t _line_no);

    /// @brief 判断是否是叶子节点
    bool isLeafNode();

    /// @brief 添加子节点
    ast_node * insert_son_node(ast_node * node);

    /// @brief 创建新节点(可变参数)
    static ast_node * New(ast_operator_type type, ...);

    /// @brief 创建整数字面量节点
    static ast_node * New(digit_int_attr attr);

    /// @brief 创建浮点数字面量节点
    static ast_node * New(digit_real_attr attr);

    /// @brief 创建标识符节点
    static ast_node * New(var_id_attr attr);

    /// @brief 创建标识符节点
    static ast_node * New(std::string id, int64_t lineno);

    /// @brief 创建具备指定类型的节点
    static ast_node * New(Type * type);

    /// @brief 删除节点
    static void Delete(ast_node * node);
};

// AST相关函数声明
void free_ast(ast_node * root); // AST资源清理

extern ast_node * ast_root; //抽象语法树的根节点指针

/// @brief 创建AST的内部节点，请注意可追加孩子节点，请按次序依次加入，最多3个
/// @param node_type 节点类型
/// @param first_child 第一个孩子节点
/// @param second_child 第一个孩子节点
/// @param third_child 第一个孩子节点
/// @return 创建的节点
ast_node * create_contain_node(ast_operator_type node_type,
                               ast_node * first_child = nullptr,
                               ast_node * second_child = nullptr,
                               ast_node * third_child = nullptr);

/// @brief 创建函数定义类型的内部AST节点
/// @param type_node 函数返回值类型
/// @param name_node 函数名节点
/// @param block 函数体语句块
/// @param params 函数形参，可以没有参数
/// @return 创建的节点
ast_node *
create_func_def(ast_node * type_node, ast_node * name_node, ast_node * block = nullptr, ast_node * params = nullptr);

/// @brief 创建函数定义类型的内部AST节点
/// @param type 返回值类型
/// @param id 函数名字
/// @param block_node 函数体语句块节点
/// @param params_node 函数形参，可以没有参数
/// @return 创建的节点
ast_node * create_func_def(type_attr & type, var_id_attr & id, ast_node * block_node, ast_node * params_node);

/// @brief 创建函数形式参数的节点
/// @param line_no 行号
/// @param param_name 形式参数名
/// @return 创建的节点
ast_node * create_func_formal_param(uint32_t line_no, const char * param_name);

/// @brief 创建函数调用的节点
/// @param funcname_node 函数名节点
/// @param params_node 实参节点
/// @return 创建的节点
ast_node * create_func_call(ast_node * funcname_node, ast_node * params_node = nullptr);

/// @brief 创建类型节点
/// @param type 类型信息
/// @return 创建的节点
ast_node * create_type_node(type_attr & type);

/// @brief 类型属性转换成Type
/// @param attr 词法属性
/// @return Type* 类型
Type * typeAttr2Type(type_attr & attr);

/// @brief 根据第一个变量定义创建变量声明语句节点
/// @param first_child 第一个变量定义节点
/// @return ast_node* 变量声明语句节点
ast_node * create_var_decl_stmt_node(ast_node * first_child);

/// @brief 根据变量的类型和属性创建变量声明语句节点
/// @param type 变量的类型
/// @param id 变量的名字
/// @return ast_node* 变量声明语句节点
ast_node * create_var_decl_stmt_node(type_attr & type, var_id_attr & id);

/// @brief 向变量声明语句中追加变量声明
/// @param stmt_node 变量声明语句
/// @param id 变量的名字
/// @return ast_node* 变量声明语句节点
ast_node * add_var_decl_node(ast_node * stmt_node, var_id_attr & id);