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
#include "CastInstruction.h"
#include "FuncCallInstruction.h"
#include "BinaryInstruction.h"
#include "MoveInstruction.h"
#include "LoadInstruction.h"
#include "StoreInstruction.h"
#include "GotoInstruction.h"
#include "BranchConditional.h"
#include "UnaryInstruction.h"
#include "ArgInstruction.h"
#include "BitCastInstruction.h"
#include "GetElementPtrInstruction.h"

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
    ast2ir_handlers[ast_operator_type::AST_OP_POS] = &IRGenerator::ir_pos;
    ast2ir_handlers[ast_operator_type::AST_OP_NEG] = &IRGenerator::ir_neg;
    ast2ir_handlers[ast_operator_type::AST_OP_NOT] = &IRGenerator::ir_not;

    // 关系表达式
    ast2ir_handlers[ast_operator_type::AST_OP_EQ] = &IRGenerator::ir_eq;
    ast2ir_handlers[ast_operator_type::AST_OP_NE] = &IRGenerator::ir_ne;
    ast2ir_handlers[ast_operator_type::AST_OP_LT] = &IRGenerator::ir_lt;
    ast2ir_handlers[ast_operator_type::AST_OP_LE] = &IRGenerator::ir_le;
    ast2ir_handlers[ast_operator_type::AST_OP_GT] = &IRGenerator::ir_gt;
    ast2ir_handlers[ast_operator_type::AST_OP_GE] = &IRGenerator::ir_ge;

    // 逻辑表达式，需要递归地传入label指引跳转，不走visit
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

    // ir_function_real_params不用，直接用lval节点处理函数就行
    //  ast2ir_handlers[ast_operator_type::AST_OP_FUNC_REAL_PARAMS] = &IRGenerator::ir_function_real_params;

    /* 函数定义 */
    ast2ir_handlers[ast_operator_type::AST_OP_FUNC_DEF] = &IRGenerator::ir_function_define;
    // ast2ir_handlers[ast_operator_type::AST_OP_FUNC_FORMAL_PARAMS] = &IRGenerator::ir_function_formal_params;

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
    ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_INDICES] = &IRGenerator::ir_array_indices;
    // ast2ir_handlers[ast_operator_type::AST_OP_ARRAY_INIT] = &IRGenerator::ir_array_init;

    /* 语句块 */
    ast2ir_handlers[ast_operator_type::AST_OP_BLOCK] = &IRGenerator::ir_block;

    /* 宏 */
    ast2ir_handlers[ast_operator_type::AST_OP_MACRO_DECL] = &IRGenerator::ir_macro_decl;

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
    // minic_log(LOG_INFO, "Visit节点类型: %d, 名称: %s", static_cast<int>(node->node_type), node->name.c_str());
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
    Value * retValue = nullptr;
    if (!type_node->type->isVoidType()) {

        // 保存函数返回值变量到函数信息中，在函数定义结尾，需要设置值到这个变量中(首先从%l0中load出返回值，存到一个临时变量中，再return这个临时变量)

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

    //在函数定义的结尾，首先从%l0中load出返回值，存到一个临时变量中，再在函数出口返回这个临时变量
    if (retValue) {
        // 如果函数有返回值，则需要设置返回值
        // 这里的retValue是函数内的局部变量，不能是临时变量
        LoadInstruction * loadInst = new LoadInstruction(newFunc, retValue);
        irCode.addInst(loadInst);
        retValue = loadInst;
    }

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
    if (entryIter == irCode.getInsts().end()) {
        return false;
    }
    ++entryIter;
    // 遍历形参列表，孩子是表达式
    for (auto son: node->sons) {
        Type * paramType = nullptr;
        std::string paramName = son->sons[1]->name;

        if (son->sons.size() > 2 && son->sons[2]->node_type == ast_operator_type::AST_OP_ARRAY_DIMS) {
            // 处理数组参数
            std::vector<int32_t> dimensions;
            ast_node * dims_node = son->sons[2];
            for (auto dim_node: dims_node->sons) {
                if (!ir_visit_ast_node(dim_node)) {
                    minic_log(LOG_ERROR, "数组形参维度节点翻译失败");
                    return false;
                }
                // -1 表示不定长（如 int a[][5]），跳过
                ConstInt * constDim = dynamic_cast<ConstInt *>(dim_node->val);
                if (!constDim) {
                    minic_log(LOG_ERROR, "数组形参维度解析失败");
                    return false;
                }
                int val = constDim->getVal();
                if (val > 0)
                    dimensions.push_back(val);
            }
            // 构造数组类型
            Type * baseType = son->sons[0]->type;
            if (!dimensions.empty()) {
                paramType = new ArrayType(baseType, dimensions);
                // 退化为指针类型
                const PointerType * ptrType = PointerType::get(paramType);
                paramType = static_cast<Type *>(const_cast<PointerType *>(ptrType));
            } else {
                // 只有 int b[] 这种，直接退化为指针
                const PointerType * ptrType = PointerType::get(baseType);
                paramType = static_cast<Type *>(const_cast<PointerType *>(ptrType));
            }
        } else {
            // 普通参数
            paramType = son->sons[0]->type;
        }

        // 创建 FormalParam
        FormalParam * formalParam = new FormalParam(paramType, paramName);
        currentFunc->addParam(formalParam);

        Value * realParam = module->newVarValue(paramType, paramName);

        // 产生赋值指令，将形参值存到局部变量
        bool isFormalRes = false;
        bool isFormalSrc = false;
        if (formalParam->getType()->isArrayType() || formalParam->getType()->isPointerType()) {
            isFormalSrc = true;
        }
        if (realParam->getType()->isArrayType() || realParam->getType()->isPointerType()) {
            isFormalRes = true;
        }
        if (!isFormalSrc && !isFormalRes) { //形参实参都为普通变量类型
            isFormalRes = true;
        }
        StoreInstruction * movInst =
            new StoreInstruction(currentFunc, realParam, formalParam, isFormalRes, isFormalSrc);
        irCode.getInsts().push_back(movInst); // currentFunc->getParams().back()
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
    // int64_t lineno = node->sons[0]->line_no;

    ast_node * paramsNode = nullptr;
    if (node->sons[1] != nullptr && node->sons[1]->node_type == ast_operator_type::AST_OP_FUNC_REAL_PARAMS) {
        paramsNode = node->sons[1];
    }

    // 根据函数名查找函数，看是否存在。若不存在则出错
    // 这里约定函数必须先定义后使用
    auto calledFunction = module->findFunction(funcName);
    if (nullptr == calledFunction) {
        minic_log(LOG_ERROR, "函数(%s)未定义或声明", funcName.c_str());
        return false;
    }
    // 当前函数存在函数调用
    currentFunc->setExistFuncCall(true);
    currentFunc->realArgCountReset(); // 重置计数
    printf("函数调用%s\n", funcName.c_str());
    // 如果没有孩子，也认为是没有参数
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
            printf("有参数\n");
            // 遍历Block的每个语句，进行显示或者运算
            ast_node * temp = ir_visit_ast_node(son);
            if (!temp || !temp->val) {
                minic_log(LOG_ERROR, "实参翻译失败");
                return false;
            }
            // 生成参数传递的IR指令
            // calledFunction->realArgCountInc();
            realParams.push_back(temp->val);
            node->blockInsts.addInst(temp->blockInsts);
        }
    }

    // TODO 这里请追加函数调用的语义错误检查，这里只进行了函数参数的个数检查等，其它请自行追加。
    // if (realParams.size() != calledFunction->getParams().size()) {
    //     // 函数参数的个数不一致，语义错误
    //     printf("realParams.size():%d, calledFunction->getParams().size:%d\n",
    //            int(realParams.size()),
    //            int(calledFunction->getParams().size()));
    //     minic_log(LOG_ERROR, "第%lld行的被调用函数(%s)未定义或声明", (long long) lineno, funcName.c_str());
    //     return false;
    // }
    std::vector<Value *> callArgs;
    auto & formalParams = calledFunction->getParams();
    for (size_t i = 0; i < realParams.size(); ++i) {
        Value * arg = realParams[i];
        Type * formalType = (i < formalParams.size()) ? formalParams[i]->getType() : arg->getType();

        // 形参是指针，实参是数组
        if (formalType->isPointerType() && arg->getType()->isArrayType()) {
            const ArrayType * arrTy = static_cast<const ArrayType *>(arg->getType());
            Type * formalElemType = const_cast<Type *>(static_cast<const PointerType *>(formalType)->getPointeeType());

            int arrDims = arrTy->getDimensions().size();
            int formalDims = 0;
            if (formalElemType->isArrayType()) {
                formalDims = static_cast<const ArrayType *>(formalElemType)->getDimensions().size();
            }

            // 多维数组（如 [3 x [5 x i32]]），GEP到首元素，再bitcast
            if (arrDims == formalDims + 1 && arrDims > 1) {
                // GEP到 a[0][0]...
                std::vector<Value *> gepIndices(arrDims + 1, module->newConstInt64(0));
                // auto gepInst = new GetElementPtrInstruction(currentFunc,
                //                                             arg,
                //                                             gepIndices,
                //                                             (Type *) PointerType::get(formalElemType));
                Type * baseType = formalElemType;
                while (baseType->isArrayType()) {
                    baseType = static_cast<const ArrayType *>(baseType)->getBaseType();
                }
                auto gepInst =
                    new GetElementPtrInstruction(currentFunc, arg, gepIndices, (Type *) PointerType::get(baseType));
                node->blockInsts.addInst(gepInst);

                // bitcast 到参数类型
                auto bitcastInst = new BitCastInstruction(currentFunc, gepInst, (Type *) formalType);
                node->blockInsts.addInst(bitcastInst);

                callArgs.push_back(bitcastInst);
                continue;
            }
            // 一维数组，GEP到首元素即可
            else if (arrDims == 1 && formalDims == 0) {
                std::vector<Value *> gepIndices = {module->newConstInt64(0), module->newConstInt64(0)};
                auto gepInst = new GetElementPtrInstruction(currentFunc, arg, gepIndices, (Type *) formalType);
                node->blockInsts.addInst(gepInst);

                callArgs.push_back(gepInst);
                continue;
            }
        }
        // 其它情况直接传递
        callArgs.push_back(arg);
    }
    // 返回调用有返回值，则需要分配临时变量，用于保存函数调用的返回值
    Type * type = calledFunction->getReturnType();
    // FuncCallInstruction * funcCallInst = new FuncCallInstruction(currentFunc, calledFunction, realParams, type);

    FuncCallInstruction * funcCallInst = new FuncCallInstruction(currentFunc, calledFunction, callArgs, type);

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
    CastInstruction * cast_inst = nullptr;

    if (left->val->getType()->isFloatType() && right->val->getType()->isFloatType()) {
        op = IRInstOperator::IRINST_OP_ADD_F; // 浮点加法指令
        resultType = FloatType::getTypeFloat();
        // 需要确保0.1这样的常量被识别为float
    } else if (left->val->getType()->isInt32Type() && right->val->getType()->isInt32Type()) {
        op = IRInstOperator::IRINST_OP_ADD_I; // 整数加法指令
        resultType = IntegerType::getTypeInt();
    } else {
        // 类型转换
        minic_log(LOG_INFO,
                  "add语句操作数需要类型转换: %s <-> %s",
                  right->val->getType()->toString().c_str(),
                  left->val->getType()->toString().c_str());
        if (left->val->getType()->isFloatType()) {
            // float + i32
            cast_inst = new CastInstruction(module->getCurrentFunction(), right->val, left->val->getType());
            right->val = cast_inst;
            op = IRInstOperator::IRINST_OP_ADD_F; // 浮点加法指令
            resultType = FloatType::getTypeFloat();
        } else if (right->val->getType()->isFloatType()) {
            // i32 + float
            cast_inst = new CastInstruction(module->getCurrentFunction(), left->val, right->val->getType());
            left->val = cast_inst;
            op = IRInstOperator::IRINST_OP_ADD_F; // 浮点加法指令
            resultType = FloatType::getTypeFloat();
        } else if (left->val->getType()->isIntegerType() && right->val->getType()->isInt1Byte()) {
            // i32 + i1
            cast_inst = new CastInstruction(module->getCurrentFunction(), right->val, left->val->getType());
            right->val = cast_inst;
            op = IRInstOperator::IRINST_OP_ADD_I; // 整数加法指令
            resultType = IntegerType::getTypeInt();
        } else if (left->val->getType()->isInt1Byte() && right->val->getType()->isIntegerType()) {
            // i1 + i32
            cast_inst = new CastInstruction(module->getCurrentFunction(), left->val, right->val->getType());
            left->val = cast_inst;
            op = IRInstOperator::IRINST_OP_ADD_I; // 整数加法指令
            resultType = IntegerType::getTypeInt();
        } else {
            // 其它类型不支持
            minic_log(LOG_ERROR, "加法操作数的类型转换不支持");
            if (left->val->getType()->isFloatType() || right->val->getType()->isFloatType()) {
                op = IRInstOperator::IRINST_OP_ADD_F; // 浮点加法指令
                resultType = FloatType::getTypeFloat();
                // 需要确保0.1这样的常量被识别为float
            } else {
                op = IRInstOperator::IRINST_OP_ADD_I; // 整数加法指令
                resultType = IntegerType::getTypeInt();
            }
        }
    }
    BinaryInstruction * addInst =
        new BinaryInstruction(module->getCurrentFunction(), op, left->val, right->val, resultType);

    // 加法ir，创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(addInst);

    if (cast_inst) {
        node->blockInsts.addInst(cast_inst);
    }

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
    CastInstruction * cast_inst = nullptr;

    if (left->val->getType()->isFloatType() && right->val->getType()->isFloatType()) {
        op = IRInstOperator::IRINST_OP_SUB_F; // 浮点加法指令
        resultType = FloatType::getTypeFloat();
        // 需要确保0.1这样的常量被识别为float
    } else if (left->val->getType()->isInt32Type() && right->val->getType()->isInt32Type()) {
        op = IRInstOperator::IRINST_OP_SUB_I; // 整数加法指令
        resultType = IntegerType::getTypeInt();
    } else {
        // 类型转换
        minic_log(LOG_INFO,
                  "sub语句操作数需要类型转换: %s <-> %s",
                  right->val->getType()->toString().c_str(),
                  left->val->getType()->toString().c_str());
        if (left->val->getType()->isFloatType()) {
            // float - i32
            cast_inst = new CastInstruction(module->getCurrentFunction(), right->val, left->val->getType());
            right->val = cast_inst;
            op = IRInstOperator::IRINST_OP_SUB_F; // 浮点加法指令
            resultType = FloatType::getTypeFloat();
        } else if (right->val->getType()->isFloatType()) {
            // i32 - float
            cast_inst = new CastInstruction(module->getCurrentFunction(), left->val, right->val->getType());
            left->val = cast_inst;
            op = IRInstOperator::IRINST_OP_SUB_F; // 浮点加法指令
            resultType = FloatType::getTypeFloat();
        } else if (left->val->getType()->isIntegerType() && right->val->getType()->isInt1Byte()) {
            // i32 - i1
            cast_inst = new CastInstruction(module->getCurrentFunction(), right->val, left->val->getType());
            right->val = cast_inst;
            op = IRInstOperator::IRINST_OP_SUB_I; // 整数加法指令
            resultType = IntegerType::getTypeInt();
        } else if (left->val->getType()->isInt1Byte() && right->val->getType()->isIntegerType()) {
            // i1 - i32
            cast_inst = new CastInstruction(module->getCurrentFunction(), left->val, right->val->getType());
            left->val = cast_inst;
            op = IRInstOperator::IRINST_OP_SUB_I; // 整数加法指令
            resultType = IntegerType::getTypeInt();
        } else {
            // 其它类型不支持
            minic_log(LOG_ERROR, "减法操作数的类型转换不支持");
            if (left->val->getType()->isFloatType() || right->val->getType()->isFloatType()) {
                op = IRInstOperator::IRINST_OP_ADD_F; // 浮点加法指令
                resultType = FloatType::getTypeFloat();
                // 需要确保0.1这样的常量被识别为float
            } else {
                op = IRInstOperator::IRINST_OP_ADD_I; // 整数加法指令
                resultType = IntegerType::getTypeInt();
            }
        }
    }
    BinaryInstruction * subInst =
        new BinaryInstruction(module->getCurrentFunction(), op, left->val, right->val, resultType);

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    if (cast_inst) {
        node->blockInsts.addInst(cast_inst);
    }
    node->blockInsts.addInst(subInst);

    node->val = subInst;

    return true;
}

/// @brief 整数乘法AST节点翻译成线性中间IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_mul(ast_node * node)
{
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
    CastInstruction * cast_inst = nullptr;

    if (left->val->getType()->isFloatType() || right->val->getType()->isFloatType()) {
        CastInstruction * cast_left =
            new CastInstruction(module->getCurrentFunction(), left->val, FloatType::getTypeFloat());
        CastInstruction * cast_right =
            new CastInstruction(module->getCurrentFunction(), right->val, FloatType::getTypeFloat());
        if (cast_left) {
            left->val = cast_left;
            cast_inst = cast_left;
        } else {
            left->val = cast_right;
            cast_inst = cast_right;
        }
        op = IRInstOperator::IRINST_OP_MUL_F; // 浮点乘法指令
        resultType = FloatType::getTypeFloat();
        // 需要确保0.1这样的常量被识别为float
    } else if (left->val->getType()->isInt32Type() && right->val->getType()->isInt32Type()) {
        op = IRInstOperator::IRINST_OP_MUL_I; // 整数乘法指令
        resultType = IntegerType::getTypeInt();
    } else {
        // 类型转换
        minic_log(LOG_INFO,
                  "mul语句操作数需要类型转换: %s <-> %s",
                  right->val->getType()->toString().c_str(),
                  left->val->getType()->toString().c_str());
        if (left->val->getType()->isFloatType()) {
            // float * i32
            cast_inst = new CastInstruction(module->getCurrentFunction(), right->val, left->val->getType());
            right->val = cast_inst;
            op = IRInstOperator::IRINST_OP_MUL_F; // 浮点乘法指令
            resultType = FloatType::getTypeFloat();
        } else if (right->val->getType()->isFloatType()) {
            // i32 * float
            cast_inst = new CastInstruction(module->getCurrentFunction(), left->val, right->val->getType());
            left->val = cast_inst;
            op = IRInstOperator::IRINST_OP_MUL_F; // 浮点乘法指令
            resultType = FloatType::getTypeFloat();
        } else if (left->val->getType()->isIntegerType() && right->val->getType()->isInt1Byte()) {
            // i32 * i1
            cast_inst = new CastInstruction(module->getCurrentFunction(), right->val, left->val->getType());
            right->val = cast_inst;
            op = IRInstOperator::IRINST_OP_MUL_I; // 整数乘法指令
            resultType = IntegerType::getTypeInt();
        } else if (left->val->getType()->isInt1Byte() && right->val->getType()->isIntegerType()) {
            // i1 * i32
            cast_inst = new CastInstruction(module->getCurrentFunction(), left->val, right->val->getType());
            left->val = cast_inst;
            op = IRInstOperator::IRINST_OP_MUL_I; // 整数乘法指令
            resultType = IntegerType::getTypeInt();
        } else {
            // 数组
            if ((left->val->getType()->isPointerType() &&
                 left->val->getType()->getBaseType() == IntegerType::getTypeInt()) ||
                (right->val->getType()->isPointerType() &&
                 right->val->getType()->getBaseType() == IntegerType::getTypeInt())) {
                op = IRInstOperator::IRINST_OP_MUL_I; // 整数乘法指令
                resultType = IntegerType::getTypeInt();
            } else {
                if (left->val->getType()->isFloatType() || right->val->getType()->isFloatType()) {
                    op = IRInstOperator::IRINST_OP_MUL_F; // 浮点乘法指令
                    resultType = FloatType::getTypeFloat();
                    // 需要确保0.1这样的常量被识别为float
                } else {
                    op = IRInstOperator::IRINST_OP_MUL_I; // 整数乘法指令
                    resultType = IntegerType::getTypeInt();
                }
            }
        }
    }

    BinaryInstruction * mulInst =
        new BinaryInstruction(module->getCurrentFunction(), op, left->val, right->val, resultType);

    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    if (cast_inst) {
        node->blockInsts.addInst(cast_inst);
    }
    node->blockInsts.addInst(mulInst);

    node->val = mulInst;
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

    // 检查是否需要进行类型转换
    CastInstruction * cast_inst = nullptr;
    if (left->val->getType() != right->val->getType()) {
        // minic_log(LOG_INFO,
        //    "赋值语句操作数需要类型转换: %s -> %s",
        //    right->val->getType()->toString().c_str(),
        //    left->val->getType()->toString().c_str());

        if (left->val->getType()->isInt32Type() && right->val->getType()->isInt1Byte()) {
            // i1 -> i32
            cast_inst = new CastInstruction(module->getCurrentFunction(),
                                            // CastInstruction::CastType::ZEXT,
                                            right->val,
                                            IntegerType::getTypeInt());
            right->val = cast_inst;
        } else if (left->val->getType()->isInt32Type() && right->val->getType()->isFloatType()) {
            // float -> i32
            cast_inst = new CastInstruction(module->getCurrentFunction(),
                                            // CastInstruction::CastType::FPTOSI,
                                            right->val,
                                            IntegerType::getTypeInt());
            right->val = cast_inst;
        } else if (left->val->getType()->isFloatType() && right->val->getType()->isInt32Type()) {
            // i32 -> float
            cast_inst = new CastInstruction(module->getCurrentFunction(),
                                            // CastInstruction::CastType::SITOFP,
                                            right->val,
                                            FloatType::getTypeFloat());
            right->val = cast_inst;
        } else {
            // minic_log(LOG_ERROR, "赋值语句操作数暂时不支持转换");
            //  return false;
        }
    }

    // 将右侧操作数的值赋给左侧操作数，采用load + store指令代替move指令
    bool isFormalRes = true;
    bool isFormalSrc = true;
    if (left->val->getType()->isArrayType() || left->val->getType()->isPointerType())
        isFormalRes = false;
    if (right->val->getType()->isArrayType() || right->val->getType()->isPointerType())
        isFormalSrc = false;
    StoreInstruction * storeInst =
        new StoreInstruction(module->getCurrentFunction(), left->val, right->val, isFormalRes, isFormalSrc);

    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    if (cast_inst) {
        node->blockInsts.addInst(cast_inst);
    }
    node->blockInsts.addInst(storeInst);

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
        // 将数组索引处理拆分到 ir_array_indices
        if (!ir_array_indices(node)) {
            minic_log(LOG_ERROR, "数组索引处理失败");
            return false;
        }
        resultVal = node->val;
    } else if (!node->store && !resultVal->getType()->isArrayType()) {
        Value * val = module->findVarValue(var_node->name);
        if (val->isConst()) {
            resultVal = val->getConstValue();
        } else {
            // 非数组变量，但需要加载值（如指针解引用）
            LoadInstruction * loadInst = new LoadInstruction(module->getCurrentFunction(), resultVal);
            node->blockInsts.addInst(loadInst);
            resultVal = loadInst; // 更新为加载后的值
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
        // Type * valueType = returnValue->getType();

        // 普通类型检查
        // if (valueType != returnType) {
        //     minic_log(LOG_ERROR,
        //               "返回值类型(%s)与函数返回类型(%s)不匹配",
        //               valueType->toString().c_str(),
        //               returnType->toString().c_str());
        //     return false;
        // }
        // 添加返回值的IR指令
        node->blockInsts.addInst(right->blockInsts);

        // 如果有返回值变量（非void函数），生成赋值指令
        if (currentFunc->getReturnValue()) {
            bool isFormalRes = true;
            bool isFormalSrc = true;
            if (currentFunc->getReturnValue()->getType()->isArrayType() ||
                currentFunc->getReturnValue()->getType()->isPointerType())
                isFormalRes = false;
            if (returnValue->getType()->isArrayType() || returnValue->getType()->isPointerType())
                isFormalSrc = false;
            StoreInstruction * store1 = new StoreInstruction(module->getCurrentFunction(),
                                                             currentFunc->getReturnValue(),
                                                             returnValue,
                                                             isFormalRes,
                                                             isFormalSrc);
            node->blockInsts.addInst(store1);
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
    if (right) {
        node->val = right->val;
        node->val = right->val;
    }
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
    //如果是常量且有初值，直接返回初值
    if (val->isConst()) {
        val = val->getConstValue();
        if (!val) {
            minic_log(LOG_ERROR, "常量(%s)未定义", node->name.c_str());
            return false;
        }
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
    if (module->findCurrentVarValue(varName)) {
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
        return true;
    }
    // 非数组变量处理
    // 检查是否有初始化
    if (node->sons.size() > 1) {
        // 处理初始化表达式
        ast_node * init_expr_node = node->sons[1];
        if (!ir_visit_ast_node(init_expr_node)) {
            minic_log(LOG_ERROR, "初始化表达式翻译失败");
            return false;
        }
        Value * varValue;
        if (!module->getCurrentFunction()) { //全局变量
            varValue = module->newVarValue(varType, varName, init_expr_node->val);
        } else { //局部变量
            varValue = module->newVarValue(varType, varName);
        }
        node->val = varValue;
        var_name_node->val = varValue;
        if (!varValue) {
            minic_log(LOG_ERROR, "变量(%s)创建失败", varName.c_str());
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
        bool isFormalRes = true;
        bool isFormalSrc = true;
        if (varValue->getType()->isArrayType() || varValue->getType()->isPointerType())
            isFormalRes = false;
        if (init_expr_node->val->getType()->isArrayType() || init_expr_node->val->getType()->isPointerType())
            isFormalSrc = false;
        StoreInstruction * movInst =
            new StoreInstruction(module->getCurrentFunction(), varValue, init_expr_node->val, isFormalRes, isFormalSrc);
        // 添加指令到当前块
        node->blockInsts.addInst(init_expr_node->blockInsts);
        node->blockInsts.addInst(var_name_node->blockInsts);
        node->blockInsts.addInst(movInst);
    } else { //不初始化直接创建变量就行
        Value * varValue;
        varValue = module->newVarValue(varType, varName);
        if (!varValue)
            minic_log(LOG_INFO, "变量(%s)创建失败", varName.c_str());
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

bool IRGenerator::ir_array_indices(ast_node * node)
{
    // node: AST_OP_LVAL, sons[0]: var_node, sons[1]: indices_node
    ast_node * var_node = node->sons[0];
    ast_node * indices_node = node->sons[1];

    Value * arrayValue = var_node->val;
    if (!arrayValue) {
        minic_log(LOG_ERROR, "数组变量未定义");
        return false;
    }
    // 解析所有索引
    std::vector<Value *> indices;
    for (auto index_node: indices_node->sons) {
        if (!ir_visit_ast_node(index_node)) {
            minic_log(LOG_ERROR, "数组索引解析失败");
            return false;
        }
        node->blockInsts.addInst(index_node->blockInsts);
        if (index_node->val->getType()->isInt32Type()) {
            // 扩展到i64
            CastInstruction * cast_inst =
                new CastInstruction(module->getCurrentFunction(), index_node->val, IntegerType::getTypeInt64());
            index_node->val = cast_inst;
            node->blockInsts.addInst(cast_inst);
        }
        indices.push_back(index_node->val);
    }

    // 1. 获取数组的类型和维度
    Type * curType = arrayValue->getType();
    Value * curPtr = arrayValue;

    const ArrayType * arrayType = static_cast<const ArrayType *>(curType);
    std::vector<int32_t> dims;
    Type * baseType;
    if (curType->isArrayType()) {
        dims = arrayType->getDimensions();
        baseType = arrayType->getBaseType();
    } else {
        // 指针类型或基本类型时，dims 为空
        dims.clear();
        dims.push_back(1); // 作为指针处理时，假设只有一维
        baseType = curType;
    }
    Function * currentFunc = module->getCurrentFunction();

    Value * resultVal = arrayValue;

    // 每个 getelementptr 指令只处理一层索引
    for (size_t i = 0; i < dims.size(); ++i) {
        std::vector<Value *> gepIndices;
        // 更新指针和类型
        std::vector<int32_t> nextdims;
        ArrayType * nextArrayType = nullptr;
        if (i < dims.size() - 1) {
            // 如果还有下一维，获取下一维的维度
            nextdims = dims;
            nextdims.erase(nextdims.begin()); // 移除当前维度
            nextArrayType = new ArrayType(baseType, nextdims);
        } else {
            nextdims.clear();                                       // 最后一维后没有更多维度
            nextArrayType = (ArrayType *) arrayType->getBaseType(); // 最后一维后没有更多维度
        }

        // 第一个索引始终是 0，因为你从数组的第一维开始
        gepIndices.push_back(module->newConstInt64(0));

        // 第二个索引是当前维度的索引值
        gepIndices.push_back(indices[i]);

        // 生成 getelementptr 指令
        auto gepInst = new GetElementPtrInstruction(currentFunc, curPtr, gepIndices, nextArrayType);
        node->blockInsts.addInst(gepInst);

        // 如果是指针，报错
        if (!nextArrayType->getDimensions().empty()) {
            curPtr = gepInst; // 如果还处在数组中，继续使用该指针
        } else {
            curPtr = gepInst;    // 如果不是数组，说明已经到了最后一维
            curType = baseType;  // 最后一维的数据类型
            resultVal = gepInst; // 更新结果值为当前 gep 指令
        }

        // // 如果是最后一维，获取结果
        // if (i == dims.size() - 1) {
        //     resultVal = gepInst;
        //     break;
        // }
    }

    // 如果是数组传参，那么dims会是空的，数组实际为指针类型
    if (dims.empty() && curType->isPointerType()) {
    }

    node->val = resultVal;
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

    // 获取当前函数
    Function * currentFunc = module->getCurrentFunction();
    if (!currentFunc) {
        return false;
    }

    LabelInstruction * thenLabelInst = new LabelInstruction(currentFunc);
    LabelInstruction * elseLabelInst = elseNode ? new LabelInstruction(currentFunc) : nullptr;
    LabelInstruction * endLabelInst = new LabelInstruction(currentFunc);

    // 处理条件表达式
    // if (!ir_condition(condNode, thenLabelInst, elseLabelInst ? elseLabelInst : endLabelInst)) {
    //     minic_log(LOG_ERROR, "if语句的条件表达式翻译失败");
    //     return false;
    // }
    // node->blockInsts.addInst(condNode->blockInsts);

    // 1. 左值节点 或 一元表达式(! + -)
    // 2. 关系表达式 (==, !=, <, >, <=, >=)
    // 3. 逻辑表达式 (and or)
    // 4. 函数调用的返回值
    // 5. 数学表达式(+ - * / %)

    if (condNode->node_type == ast_operator_type::AST_OP_LVAL) {
        // 如果cond是一个单独的lval节点，与0比较
        if (!ir_visit_ast_node(condNode)) {
            minic_log(LOG_ERROR, "if语句的条件表达式翻译失败");
            return false;
        }
        node->blockInsts.addInst(condNode->blockInsts);
        BinaryInstruction * lval_ne_0 = new BinaryInstruction(module->getCurrentFunction(),
                                                              IRInstOperator::IRINST_OP_ICMP_NE,
                                                              condNode->val,
                                                              module->newConstInt(0),
                                                              IntegerType::getTypeBool());
        node->blockInsts.addInst(lval_ne_0);
        // 根据条件表达式的值，跳转到thenLabel或elseLabel(如果没有elseLabel，则跳转到endLabel)
        condNode->val = lval_ne_0;
        BranchCondInstruction * condGotoInst = new BranchCondInstruction(module->getCurrentFunction(),
                                                                         lval_ne_0,
                                                                         thenLabelInst,
                                                                         elseLabelInst ? elseLabelInst : endLabelInst);
        node->blockInsts.addInst(condGotoInst);
    } else if (condNode->node_type == ast_operator_type::AST_OP_POS ||
               condNode->node_type == ast_operator_type::AST_OP_NEG ||
               condNode->node_type == ast_operator_type::AST_OP_NOT) {
        // 处理一元表达式
        if (!ir_visit_ast_node(condNode)) {
            minic_log(LOG_ERROR, "if语句的条件表达式翻译失败");
            return false;
        }
        node->blockInsts.addInst(condNode->blockInsts);
        // 与0比较
        BinaryInstruction * unary_expr_ne_0 = new BinaryInstruction(module->getCurrentFunction(),
                                                                    IRInstOperator::IRINST_OP_ICMP_NE,
                                                                    condNode->val,
                                                                    module->newConstInt(0),
                                                                    IntegerType::getTypeBool());
        node->blockInsts.addInst(unary_expr_ne_0);
        condNode->val = unary_expr_ne_0;
        // 根据条件表达式的值，跳转到thenLabel或elseLabel(如果没有elseLabel，则跳转到endLabel)
        BranchCondInstruction * condGotoInst = new BranchCondInstruction(module->getCurrentFunction(),
                                                                         condNode->val,
                                                                         thenLabelInst,
                                                                         elseLabelInst ? elseLabelInst : endLabelInst);
        node->blockInsts.addInst(condGotoInst);
    } else if (condNode->node_type == ast_operator_type::AST_OP_AND) {
        // 处理逻辑与表达式
        if (!ir_and(condNode, thenLabelInst, elseLabelInst ? elseLabelInst : endLabelInst)) {
            minic_log(LOG_ERROR, "if语句的条件表达式翻译失败");
            return false;
        }
        node->blockInsts.addInst(condNode->blockInsts);
    } else if (condNode->node_type == ast_operator_type::AST_OP_OR) {
        // 处理逻辑或表达式
        if (!ir_or(condNode, thenLabelInst, elseLabelInst ? elseLabelInst : endLabelInst)) {
            minic_log(LOG_ERROR, "if语句的条件表达式翻译失败");
            return false;
        }
        node->blockInsts.addInst(condNode->blockInsts);
    } else if (condNode->node_type == ast_operator_type::AST_OP_EQ ||
               condNode->node_type == ast_operator_type::AST_OP_NE ||
               condNode->node_type == ast_operator_type::AST_OP_LT ||
               condNode->node_type == ast_operator_type::AST_OP_GT ||
               condNode->node_type == ast_operator_type::AST_OP_LE ||
               condNode->node_type == ast_operator_type::AST_OP_GE) {
        // 处理关系表达式
        if (!ir_visit_ast_node(condNode)) {
            minic_log(LOG_ERROR, "if语句的条件表达式翻译失败");
            return false;
        }
        node->blockInsts.addInst(condNode->blockInsts);
        // 根据条件表达式的值，跳转到thenLabel或elseLabel(如果没有elseLabel，则跳转到endLabel)
        BranchCondInstruction * condGotoInst = new BranchCondInstruction(module->getCurrentFunction(),
                                                                         condNode->val,
                                                                         thenLabelInst,
                                                                         elseLabelInst ? elseLabelInst : endLabelInst);
        node->blockInsts.addInst(condGotoInst);
    } else if (condNode->node_type == ast_operator_type::AST_OP_FUNC_CALL) {
        // 处理函数调用的返回值
        if (!ir_visit_ast_node(condNode)) {
            minic_log(LOG_ERROR, "if语句的条件表达式翻译失败");
            return false;
        }
        node->blockInsts.addInst(condNode->blockInsts);
        // 与0比较
        BinaryInstruction * func_call_ne_0 = new BinaryInstruction(module->getCurrentFunction(),
                                                                   IRInstOperator::IRINST_OP_ICMP_NE,
                                                                   condNode->val,
                                                                   module->newConstInt(0),
                                                                   IntegerType::getTypeBool());
        node->blockInsts.addInst(func_call_ne_0);
        condNode->val = func_call_ne_0;
        // 根据条件表达式的值，跳转到thenLabel或elseLabel(如果没有elseLabel，则跳转到endLabel)
        BranchCondInstruction * condGotoInst = new BranchCondInstruction(module->getCurrentFunction(),
                                                                         condNode->val,
                                                                         thenLabelInst,
                                                                         elseLabelInst ? elseLabelInst : endLabelInst);
        node->blockInsts.addInst(condGotoInst);
    } else if (condNode->node_type == ast_operator_type::AST_OP_ADD ||
               condNode->node_type == ast_operator_type::AST_OP_SUB ||
               condNode->node_type == ast_operator_type::AST_OP_MUL ||
               condNode->node_type == ast_operator_type::AST_OP_DIV ||
               condNode->node_type == ast_operator_type::AST_OP_MOD) {
        // 处理数学表达式
        if (!ir_visit_ast_node(condNode)) {
            minic_log(LOG_ERROR, "if语句的条件表达式翻译失败");
            return false;
        }
        node->blockInsts.addInst(condNode->blockInsts);
        // 与0比较
        BinaryInstruction * math_expr_ne_0 = new BinaryInstruction(module->getCurrentFunction(),
                                                                   IRInstOperator::IRINST_OP_ICMP_NE,
                                                                   condNode->val,
                                                                   module->newConstInt(0),
                                                                   IntegerType::getTypeBool());
        node->blockInsts.addInst(math_expr_ne_0);
        condNode->val = math_expr_ne_0;
        // 根据条件表达式的值，跳转到thenLabel或elseLabel(如果没有elseLabel，则跳转到endLabel)
        BranchCondInstruction * condGotoInst = new BranchCondInstruction(module->getCurrentFunction(),
                                                                         condNode->val,
                                                                         thenLabelInst,
                                                                         elseLabelInst ? elseLabelInst : endLabelInst);
        node->blockInsts.addInst(condGotoInst);
    } else if (condNode->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
        // 处理无符号整数字面量
        if (!ir_visit_ast_node(condNode)) {
            minic_log(LOG_ERROR, "if语句的条件表达式翻译失败");
            return false;
        }
        node->blockInsts.addInst(condNode->blockInsts);
        // 与0比较
        BinaryInstruction * literal_ne_0 = new BinaryInstruction(module->getCurrentFunction(),
                                                                 IRInstOperator::IRINST_OP_ICMP_NE,
                                                                 condNode->val,
                                                                 module->newConstInt(0),
                                                                 IntegerType::getTypeBool());
        node->blockInsts.addInst(literal_ne_0);
        condNode->val = literal_ne_0;
        // 根据条件表达式的值，跳转到thenLabel或elseLabel(如果没有elseLabel，则跳转到endLabel)
        BranchCondInstruction * condGotoInst = new BranchCondInstruction(module->getCurrentFunction(),
                                                                         condNode->val,
                                                                         thenLabelInst,
                                                                         elseLabelInst ? elseLabelInst : endLabelInst);
        node->blockInsts.addInst(condGotoInst);
    } else {
        minic_log(LOG_ERROR, "不支持的条件表达式类型: %d", static_cast<int>(condNode->node_type));
        return false;
    }

    // 处理then分支
    node->blockInsts.addInst(thenLabelInst);
    if (!ir_visit_ast_node(thenNode)) {
        minic_log(LOG_ERROR, "if语句的then分支翻译失败");
        return false;
    }
    node->blockInsts.addInst(thenNode->blockInsts);
    // then 执行完毕后需要跳过else和最终cond成立与否的设置，跳转到end
    node->blockInsts.addInst(new GotoInstruction(currentFunc, endLabelInst));

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
    node->blockInsts.addInst(new GotoInstruction(currentFunc, endLabelInst));

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

    // 标签指令，用于跳转
    LabelInstruction * condLabelInst = new LabelInstruction(currentFunc);
    LabelInstruction * bodyLabelInst = new LabelInstruction(currentFunc);
    LabelInstruction * endLabelInst = new LabelInstruction(currentFunc);

    // 添加条件判断的Label指令
    node->blockInsts.addInst(new GotoInstruction(currentFunc, condLabelInst));
    node->blockInsts.addInst(condLabelInst);

    // 处理条件判断
    // 检查cond是否是左值节点，如果是，跟0比较
    if (condNode->node_type == ast_operator_type::AST_OP_LVAL) {
        // 如果cond是一个单独的lval节点
        // 这里需要处理lval的值
        if (!ir_visit_ast_node(condNode)) {
            minic_log(LOG_ERROR, "while语句的条件表达式翻译失败");
            return false;
        }
        node->blockInsts.addInst(condNode->blockInsts);
        BinaryInstruction * lval_ne_0 = new BinaryInstruction(module->getCurrentFunction(),
                                                              IRInstOperator::IRINST_OP_ICMP_NE,
                                                              condNode->val,
                                                              module->newConstInt(0),
                                                              IntegerType::getTypeBool());
        node->blockInsts.addInst(lval_ne_0);
        // 根据条件表达式的值，跳转到bodyLabel或endLabel
        BranchCondInstruction * condGotoInst =
            new BranchCondInstruction(currentFunc, lval_ne_0, bodyLabelInst, endLabelInst);
        node->blockInsts.addInst(condGotoInst);
    } else if (condNode->node_type == ast_operator_type::AST_OP_POS ||
               condNode->node_type == ast_operator_type::AST_OP_NEG ||
               condNode->node_type == ast_operator_type::AST_OP_NOT) {
        // 如果cond是一个一元表达式
        if (!ir_visit_ast_node(condNode)) {
            minic_log(LOG_ERROR, "while语句的条件表达式翻译失败");
            return false;
        }
        node->blockInsts.addInst(condNode->blockInsts);
        // 根据条件表达式的值，跳转到bodyLabel或endLabel
        BranchCondInstruction * condGotoInst =
            new BranchCondInstruction(currentFunc, condNode->val, bodyLabelInst, endLabelInst);
        node->blockInsts.addInst(condGotoInst);
    } else if (condNode->node_type == ast_operator_type::AST_OP_AND) {
        if (!ir_and(condNode, bodyLabelInst, endLabelInst)) {
            minic_log(LOG_ERROR, "while语句的条件表达式翻译失败");
            return false;
        }
        node->blockInsts.addInst(condNode->blockInsts);
    } else if (condNode->node_type == ast_operator_type::AST_OP_OR) {
        if (!ir_or(condNode, bodyLabelInst, endLabelInst)) {
            minic_log(LOG_ERROR, "while语句的条件表达式翻译失败");
            return false;
        }
        node->blockInsts.addInst(condNode->blockInsts);
    } else if (condNode->node_type == ast_operator_type::AST_OP_FUNC_CALL) {
        // 如果cond是一个函数调用的返回值
        if (!ir_visit_ast_node(condNode)) {
            minic_log(LOG_ERROR, "while语句的条件表达式翻译失败");
            return false;
        }
        node->blockInsts.addInst(condNode->blockInsts);
        // 与0比较
        BinaryInstruction * func_call_ne_0 = new BinaryInstruction(currentFunc,
                                                                   IRInstOperator::IRINST_OP_ICMP_NE,
                                                                   condNode->val,
                                                                   module->newConstInt(0),
                                                                   IntegerType::getTypeBool());
        node->blockInsts.addInst(func_call_ne_0);
        condNode->val = func_call_ne_0;
        // 根据条件表达式的值，跳转到bodyLabel或endLabel
        BranchCondInstruction * condGotoInst =
            new BranchCondInstruction(currentFunc, condNode->val, bodyLabelInst, endLabelInst);
        node->blockInsts.addInst(condGotoInst);
    } else if (condNode->node_type == ast_operator_type::AST_OP_EQ ||
               condNode->node_type == ast_operator_type::AST_OP_NE ||
               condNode->node_type == ast_operator_type::AST_OP_LT ||
               condNode->node_type == ast_operator_type::AST_OP_GT ||
               condNode->node_type == ast_operator_type::AST_OP_LE ||
               condNode->node_type == ast_operator_type::AST_OP_GE) {
        // 如果cond是一个关系表达式
        if (!ir_visit_ast_node(condNode)) {
            minic_log(LOG_ERROR, "while语句的条件表达式翻译失败");
            return false;
        }
        node->blockInsts.addInst(condNode->blockInsts);
        // 根据条件表达式的值，跳转到bodyLabel或endLabel
        BranchCondInstruction * condGotoInst =
            new BranchCondInstruction(currentFunc, condNode->val, bodyLabelInst, endLabelInst);
        node->blockInsts.addInst(condGotoInst);
    } else if (condNode->node_type == ast_operator_type::AST_OP_ADD ||
               condNode->node_type == ast_operator_type::AST_OP_SUB ||
               condNode->node_type == ast_operator_type::AST_OP_MUL ||
               condNode->node_type == ast_operator_type::AST_OP_DIV ||
               condNode->node_type == ast_operator_type::AST_OP_MOD) {
        // 如果cond是一个数学表达式
        if (!ir_visit_ast_node(condNode)) {
            minic_log(LOG_ERROR, "while语句的条件表达式翻译失败");
            return false;
        }
        // 检查条件表达式的值是否有效
        if (!condNode->val) {
            minic_log(LOG_ERROR, "while语句的条件表达式值无效");
            return false;
        }
        // 检查条件表达式的类型是否正确
        if (!condNode->val->getType()->isInt1Byte()) {
            minic_log(LOG_ERROR, "while语句的条件表达式类型错误");
            return false;
        }
        node->blockInsts.addInst(condNode->blockInsts);
        // 根据条件表达式的值，跳转到bodyLabel或endLabel
        BranchCondInstruction * condGotoInst =
            new BranchCondInstruction(currentFunc, condNode->val, bodyLabelInst, endLabelInst);
        node->blockInsts.addInst(condGotoInst);
    } else if (condNode->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
        // 如果cond是一个无符号整数字面量
        if (!ir_visit_ast_node(condNode)) {
            minic_log(LOG_ERROR, "while语句的条件表达式翻译失败");
            return false;
        }
        node->blockInsts.addInst(condNode->blockInsts);
        // 与0比较
        BinaryInstruction * literal_ne_0 = new BinaryInstruction(currentFunc,
                                                                 IRInstOperator::IRINST_OP_ICMP_NE,
                                                                 condNode->val,
                                                                 module->newConstInt(0),
                                                                 IntegerType::getTypeBool());
        node->blockInsts.addInst(literal_ne_0);
        condNode->val = literal_ne_0;
        // 根据条件表达式的值，跳转到bodyLabel或endLabel
        BranchCondInstruction * condGotoInst =
            new BranchCondInstruction(currentFunc, condNode->val, bodyLabelInst, endLabelInst);
        node->blockInsts.addInst(condGotoInst);
    } else {
        // 不支持的条件表达式类型
        minic_log(LOG_ERROR, "不支持的条件表达式类型: %d", static_cast<int>(condNode->node_type));
        return false;
    }

    // ======= 记录loop label目标 =======
    LoopContext loopContext;
    loopContext.continueTarget = condLabelInst;
    loopContext.breakTarget = endLabelInst;
    loopLabelStack.push(loopContext);

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

    BinaryInstruction * ltInst = nullptr;

    if (left->val->getType()->isFloatType() || right->val->getType()->isFloatType()) {
        // 这里可以进行类型转换
        // left->val = new CastInstruction(module->getCurrentFunction(), left->val, FloatType::getTypeFloat());
        // right->val = new CastInstruction(module->getCurrentFunction(), right->val, FloatType::getTypeFloat());
        ltInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_FCMP_LT,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    } else if (left->val->getType()->isInt1Byte() && right->val->getType()->isInt1Byte()) {
        // 这里需要处理int1byte类型的比较
        // 这里可以进行类型转换
        // left->val = new CastInstruction(module->getCurrentFunction(), left->val, IntegerType::getTypeInt1Byte());
        // right->val = new CastInstruction(module->getCurrentFunction(), right->val,
        // IntegerType::getTypeInt1Byte());
        ltInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_ICMP_LT,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    } else if (left->val->getType()->isIntegerType() && right->val->getType()->isIntegerType()) {
        ltInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_ICMP_LT,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    } else {
        // 其他类型的比较
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

    BinaryInstruction * gtInst = nullptr;

    if (left->val->getType()->isFloatType() || right->val->getType()->isFloatType()) {
        // 这里可以进行类型转换
        // left->val = new CastInstruction(module->getCurrentFunction(), left->val, FloatType::getTypeFloat());
        // right->val = new CastInstruction(module->getCurrentFunction(), right->val, FloatType::getTypeFloat());
        gtInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_FCMP_GT,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    } else if (left->val->getType()->isIntegerType() && right->val->getType()->isIntegerType()) {
        gtInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_ICMP_GT,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    } else {
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

    BinaryInstruction * leInst = nullptr;

    if (left->val->getType()->isFloatType() || right->val->getType()->isFloatType()) {
        // 这里可以进行类型转换
        // left->val = new CastInstruction(module->getCurrentFunction(), left->val, FloatType::getTypeFloat());
        // right->val = new CastInstruction(module->getCurrentFunction(), right->val, FloatType::getTypeFloat());
        leInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_FCMP_LE,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    } else if (left->val->getType()->isIntegerType() && right->val->getType()->isIntegerType()) {
        leInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_ICMP_LE,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    } else {
        // 其他类型的比较
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

    BinaryInstruction * geInst = nullptr;

    if (left->val->getType()->isFloatType() || right->val->getType()->isFloatType()) {
        // 这里可以进行类型转换
        // left->val = new CastInstruction(module->getCurrentFunction(), left->val, FloatType::getTypeFloat());
        // right->val = new CastInstruction(module->getCurrentFunction(), right->val, FloatType::getTypeFloat());
        geInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_FCMP_GE,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    } else if (left->val->getType()->isIntegerType() && right->val->getType()->isIntegerType()) {
        geInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_ICMP_GE,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    } else {
        // 其他类型的比较
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

    BinaryInstruction * eqInst = nullptr;
    CastInstruction * castInst = nullptr;

    if (left->val->getType()->isFloatType() && right->val->getType()->isFloatType()) {
        // float == float
        eqInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_FCMP_EQ,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    } else if (left->val->getType()->isInt32Type() && right->val->getType()->isInt32Type()) {
        // i32 == i32
        eqInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_ICMP_EQ,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    } else {
        // 类型转换
        if (left->val->getType()->isInt32Type() && right->val->getType()->isFloatType()) {
            // i32 == float
            castInst = new CastInstruction(module->getCurrentFunction(), left->val, FloatType::getTypeFloat());
            eqInst = new BinaryInstruction(module->getCurrentFunction(),
                                           IRInstOperator::IRINST_OP_FCMP_EQ,
                                           castInst,
                                           right->val,
                                           IntegerType::getTypeBool());
        } else if (left->val->getType()->isFloatType() && right->val->getType()->isInt32Type()) {
            // float == i32
            castInst = new CastInstruction(module->getCurrentFunction(), right->val, FloatType::getTypeFloat());
            eqInst = new BinaryInstruction(module->getCurrentFunction(),
                                           IRInstOperator::IRINST_OP_FCMP_EQ,
                                           left->val,
                                           castInst,
                                           IntegerType::getTypeBool());
        } else if (left->val->getType()->isInt1Byte() && right->val->getType()->isInt1Byte()) {
            // i1 == i1
            eqInst = new BinaryInstruction(module->getCurrentFunction(),
                                           IRInstOperator::IRINST_OP_ICMP_EQ,
                                           left->val,
                                           right->val,
                                           IntegerType::getTypeBool());
        } else if (left->val->getType()->isInt1Byte() && right->val->getType()->isInt32Type()) {
            // i1 == i32
            castInst = new CastInstruction(module->getCurrentFunction(), left->val, IntegerType::getTypeInt());
            eqInst = new BinaryInstruction(module->getCurrentFunction(),
                                           IRInstOperator::IRINST_OP_ICMP_EQ,
                                           castInst,
                                           right->val,
                                           IntegerType::getTypeBool());
        } else if (left->val->getType()->isInt32Type() && right->val->getType()->isInt1Byte()) {
            // i32 == i1
            castInst = new CastInstruction(module->getCurrentFunction(), right->val, IntegerType::getTypeInt());
            eqInst = new BinaryInstruction(module->getCurrentFunction(),
                                           IRInstOperator::IRINST_OP_ICMP_EQ,
                                           left->val,
                                           castInst,
                                           IntegerType::getTypeBool());
        } else {
            eqInst = new BinaryInstruction(module->getCurrentFunction(),
                                           IRInstOperator::IRINST_OP_ICMP_EQ,
                                           left->val,
                                           right->val,
                                           IntegerType::getTypeBool());
        }
    }

    // 创建临时变量保存IR的值，以及线性IR指令
    node->blockInsts.addInst(left->blockInsts);
    node->blockInsts.addInst(right->blockInsts);
    if (castInst) {
        node->blockInsts.addInst(castInst);
    }
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

    BinaryInstruction * neInst = nullptr;

    if (left->val->getType()->isFloatType() || right->val->getType()->isFloatType()) {
        // 这里可以进行类型转换
        // left->val = new CastInstruction(module->getCurrentFunction(), left->val, FloatType::getTypeFloat());
        // right->val = new CastInstruction(module->getCurrentFunction(), right->val, FloatType::getTypeFloat());
        neInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_FCMP_NE,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    } else if (left->val->getType()->isIntegerType() && right->val->getType()->isIntegerType()) {
        neInst = new BinaryInstruction(module->getCurrentFunction(),
                                       IRInstOperator::IRINST_OP_ICMP_NE,
                                       left->val,
                                       right->val,
                                       IntegerType::getTypeBool());
    } else {
        // 其他类型的比较
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

/// @brief and节点，生成对应的IR。
/// @param node AST节点，真/假 出口标签指令
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_and(ast_node * node, LabelInstruction * trueLabel, LabelInstruction * falseLabel)
{
    // and节点，生成对应的IR。
    // 处理逻辑与操作符
    // leftJudgeLabel: 左操作数判断
    // 1. 处理左操作数
    // 2. 如果左操作数为假，跳转到假标签
    // rightJudgeLabel: 右操作数判断
    // 3. 处理右操作数
    // 4. 如果右操作数为假，跳转到假标签
    // 5. 否则，跳转到真标签

    if (node->sons.size() != 2) {
        minic_log(LOG_ERROR, "and操作的子节点数量不正确");
        return false;
    }
    // LabelInstruction * leftJudgeInst = new LabelInstruction(module->getCurrentFunction());
    LabelInstruction * rightJudgeInst = new LabelInstruction(module->getCurrentFunction());

    // 获取左操作数和右操作数
    ast_node * left = node->sons[0];
    ast_node * right = node->sons[1];
    // 处理左操作数
    // node->blockInsts.addInst(leftJudgeInst);
    if (left->node_type == ast_operator_type::AST_OP_LVAL || left->node_type == ast_operator_type::AST_OP_FUNC_CALL ||
        left->node_type == ast_operator_type::AST_OP_ADD || left->node_type == ast_operator_type::AST_OP_SUB ||
        left->node_type == ast_operator_type::AST_OP_MUL || left->node_type == ast_operator_type::AST_OP_DIV ||
        left->node_type == ast_operator_type::AST_OP_MOD || left->node_type == ast_operator_type::AST_OP_POS ||
        left->node_type == ast_operator_type::AST_OP_NEG || left->node_type == ast_operator_type::AST_OP_NOT ||
        left->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
        // 需要求值并与0比较的
        if (!ir_visit_ast_node(left)) {
            minic_log(LOG_ERROR, "and操作数解析失败");
            return false;
        }
        // 检查左操作数的值是否有效
        if (!left->val) {
            minic_log(LOG_ERROR, "and操作数值无效");
            return false;
        }
        node->blockInsts.addInst(left->blockInsts);
        BinaryInstruction * left_ne_0 = new BinaryInstruction(module->getCurrentFunction(),
                                                              IRInstOperator::IRINST_OP_ICMP_NE,
                                                              left->val,
                                                              module->newConstInt(0),
                                                              IntegerType::getTypeBool());
        node->blockInsts.addInst(left_ne_0);
        // 左节点短路跳转
        BranchCondInstruction * leftGotoInst =
            new BranchCondInstruction(module->getCurrentFunction(), left_ne_0, rightJudgeInst, falseLabel);
        node->blockInsts.addInst(leftGotoInst);
    } else if (left->node_type == ast_operator_type::AST_OP_AND) {
        if (!ir_and(left, rightJudgeInst, falseLabel)) {
            minic_log(LOG_ERROR, "and操作数解析失败");
            return false;
        }
        node->blockInsts.addInst(left->blockInsts);
    } else if (left->node_type == ast_operator_type::AST_OP_OR) {
        if (!ir_or(left, rightJudgeInst, falseLabel)) {
            minic_log(LOG_ERROR, "or操作数解析失败");
            return false;
        }
        node->blockInsts.addInst(left->blockInsts);
    } else if (left->node_type == ast_operator_type::AST_OP_EQ || left->node_type == ast_operator_type::AST_OP_NE ||
               left->node_type == ast_operator_type::AST_OP_LT || left->node_type == ast_operator_type::AST_OP_GT ||
               left->node_type == ast_operator_type::AST_OP_LE || left->node_type == ast_operator_type::AST_OP_GE) {
        // 如果左操作数是一个关系表达式
        if (!ir_visit_ast_node(left)) {
            minic_log(LOG_ERROR, "and操作数解析失败");
            return false;
        }
        node->blockInsts.addInst(left->blockInsts);
        // 检查左操作数的值是否有效
        if (!left->val) {
            minic_log(LOG_ERROR, "and操作数值无效");
            return false;
        }
        // 左节点短路跳转
        BranchCondInstruction * leftGotoInst =
            new BranchCondInstruction(module->getCurrentFunction(), left->val, rightJudgeInst, falseLabel);
        node->blockInsts.addInst(leftGotoInst);
    } else {
        // 其他类型的操作，不支持
        minic_log(LOG_ERROR, "不支持的操作数类型");
        return false;
    }

    // 处理右操作数
    node->blockInsts.addInst(rightJudgeInst);
    if (right->node_type == ast_operator_type::AST_OP_LVAL || right->node_type == ast_operator_type::AST_OP_FUNC_CALL ||
        right->node_type == ast_operator_type::AST_OP_ADD || right->node_type == ast_operator_type::AST_OP_SUB ||
        right->node_type == ast_operator_type::AST_OP_MUL || right->node_type == ast_operator_type::AST_OP_DIV ||
        right->node_type == ast_operator_type::AST_OP_MOD || right->node_type == ast_operator_type::AST_OP_POS ||
        right->node_type == ast_operator_type::AST_OP_NEG || right->node_type == ast_operator_type::AST_OP_NOT ||
        right->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
        // 需要求值并与0比较的
        if (!ir_visit_ast_node(right)) {
            minic_log(LOG_ERROR, "and操作数解析失败");
            return false;
        }
        // 检查右操作数的值是否有效
        if (!right->val) {
            minic_log(LOG_ERROR, "and操作数值无效");
            return false;
        }
        node->blockInsts.addInst(right->blockInsts);
        BinaryInstruction * right_ne_0 = new BinaryInstruction(module->getCurrentFunction(),
                                                               IRInstOperator::IRINST_OP_ICMP_NE,
                                                               right->val,
                                                               module->newConstInt(0),
                                                               IntegerType::getTypeBool());
        node->blockInsts.addInst(right_ne_0);
        // 右节点短路跳转
        BranchCondInstruction * rightGotoInst =
            new BranchCondInstruction(module->getCurrentFunction(), right_ne_0, trueLabel, falseLabel);
        node->blockInsts.addInst(rightGotoInst);
    } else if (right->node_type == ast_operator_type::AST_OP_AND) {
        if (!ir_and(right, trueLabel, falseLabel)) {
            minic_log(LOG_ERROR, "and操作数解析失败");
            return false;
        }
        node->blockInsts.addInst(right->blockInsts);
    } else if (right->node_type == ast_operator_type::AST_OP_OR) {
        if (!ir_or(right, trueLabel, falseLabel)) {
            minic_log(LOG_ERROR, "or操作数解析失败");
            return false;
        }
        node->blockInsts.addInst(right->blockInsts);
    } else if (right->node_type == ast_operator_type::AST_OP_EQ || right->node_type == ast_operator_type::AST_OP_NE ||
               right->node_type == ast_operator_type::AST_OP_LT || right->node_type == ast_operator_type::AST_OP_GT ||
               right->node_type == ast_operator_type::AST_OP_LE || right->node_type == ast_operator_type::AST_OP_GE) {
        // 如果右操作数是一个关系表达式
        if (!ir_visit_ast_node(right)) {
            minic_log(LOG_ERROR, "and操作数解析失败");
            return false;
        }
        node->blockInsts.addInst(right->blockInsts);
        // 检查右操作数的值是否有效
        if (!right->val) {
            minic_log(LOG_ERROR, "and操作数值无效");
            return false;
        }
        // 右节点短路跳转
        BranchCondInstruction * rightGotoInst =
            new BranchCondInstruction(module->getCurrentFunction(), right->val, trueLabel, falseLabel);
        node->blockInsts.addInst(rightGotoInst);
    } else {
        // 其他类型的操作，不支持
        minic_log(LOG_ERROR, "不支持的操作数类型");
        return false;
    }

    return true;
}

/// @brief or节点，生成对应的IR。
/// @param node AST节点，真/假 出口标签指令
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_or(ast_node * node, LabelInstruction * trueLabel, LabelInstruction * falseLabel)
{
    // or节点，生成对应的IR。
    // 处理逻辑或操作符
    // leftJudgeLabel: 左操作数判断
    // 1. 处理左操作数
    // 2. 如果左操作数为真，跳转到真标签
    // rightJudgeLabel: 右操作数判断
    // 3. 处理右操作数
    // 4. 如果右操作数为真，跳转到真标签
    // 5. 否则，跳转到假标签

    if (node->sons.size() != 2) {
        minic_log(LOG_ERROR, "or操作的子节点数量不正确");
        return false;
    }
    // LabelInstruction * leftJudgeInst = new LabelInstruction(module->getCurrentFunction());
    LabelInstruction * rightJudgeInst = new LabelInstruction(module->getCurrentFunction());

    // 获取左操作数和右操作数
    ast_node * left = node->sons[0];
    ast_node * right = node->sons[1];

    // 处理左操作数
    // 1. lval
    // 2. 逻辑表达式 (&&, ||)
    // 3. 关系表达式 (==, !=, <, >, <=, >=)
    // 4. 函数调用返回值
    // node->blockInsts.addInst(leftJudgeInst);
    if (left->node_type == ast_operator_type::AST_OP_LVAL || left->node_type == ast_operator_type::AST_OP_ADD ||
        left->node_type == ast_operator_type::AST_OP_SUB || left->node_type == ast_operator_type::AST_OP_MUL ||
        left->node_type == ast_operator_type::AST_OP_DIV || left->node_type == ast_operator_type::AST_OP_MOD ||
        left->node_type == ast_operator_type::AST_OP_POS || left->node_type == ast_operator_type::AST_OP_NEG ||
        left->node_type == ast_operator_type::AST_OP_NOT || left->node_type == ast_operator_type::AST_OP_FUNC_CALL ||
        left->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
        // 需要求值并与0比较的
        if (!ir_visit_ast_node(left)) {
            minic_log(LOG_ERROR, "or操作数解析失败");
            return false;
        }
        // 检查左操作数的值是否有效
        if (!left->val) {
            minic_log(LOG_ERROR, "or操作数值无效");
            return false;
        }
        node->blockInsts.addInst(left->blockInsts);
        BinaryInstruction * left_ne_0 = new BinaryInstruction(module->getCurrentFunction(),
                                                              IRInstOperator::IRINST_OP_ICMP_NE,
                                                              left->val,
                                                              module->newConstInt(0),
                                                              IntegerType::getTypeBool());
        node->blockInsts.addInst(left_ne_0);
        // 左节点短路跳转
        BranchCondInstruction * leftGotoInst =
            new BranchCondInstruction(module->getCurrentFunction(), left_ne_0, trueLabel, rightJudgeInst);
        node->blockInsts.addInst(leftGotoInst);
    } else if (left->node_type == ast_operator_type::AST_OP_EQ || left->node_type == ast_operator_type::AST_OP_NE ||
               left->node_type == ast_operator_type::AST_OP_LE || left->node_type == ast_operator_type::AST_OP_GE ||
               left->node_type == ast_operator_type::AST_OP_LT || left->node_type == ast_operator_type::AST_OP_GT) {
        // 如果左操作数是一个关系表达式
        if (!ir_visit_ast_node(left)) {
            minic_log(LOG_ERROR, "or操作数解析失败");
            return false;
        }
        // 检查左操作数的值是否有效
        if (!left->val) {
            minic_log(LOG_ERROR, "or操作数值无效");
            return false;
        }
        node->blockInsts.addInst(left->blockInsts);
        // 左节点短路跳转
        BranchCondInstruction * leftGotoInst =
            new BranchCondInstruction(module->getCurrentFunction(), left->val, trueLabel, rightJudgeInst);
        node->blockInsts.addInst(leftGotoInst);
    } else if (left->node_type == ast_operator_type::AST_OP_AND) {
        if (!ir_and(left, trueLabel, rightJudgeInst)) {
            minic_log(LOG_ERROR, "or操作数解析失败");
            return false;
        }
        node->blockInsts.addInst(left->blockInsts);
    } else if (left->node_type == ast_operator_type::AST_OP_OR) {
        if (!ir_or(left, trueLabel, rightJudgeInst)) {
            minic_log(LOG_ERROR, "or操作数解析失败");
            return false;
        }
        node->blockInsts.addInst(left->blockInsts);
    } else {
        minic_log(LOG_ERROR, "or操作数类型错误");
        return false;
    }

    // 处理右操作数
    node->blockInsts.addInst(rightJudgeInst);
    if (right->node_type == ast_operator_type::AST_OP_LVAL || right->node_type == ast_operator_type::AST_OP_ADD ||
        right->node_type == ast_operator_type::AST_OP_SUB || right->node_type == ast_operator_type::AST_OP_MUL ||
        right->node_type == ast_operator_type::AST_OP_DIV || right->node_type == ast_operator_type::AST_OP_MOD ||
        right->node_type == ast_operator_type::AST_OP_POS || right->node_type == ast_operator_type::AST_OP_NEG ||
        right->node_type == ast_operator_type::AST_OP_NOT || right->node_type == ast_operator_type::AST_OP_FUNC_CALL ||
        right->node_type == ast_operator_type::AST_OP_LEAF_LITERAL_UINT) {
        // 需要求值并与0比较的
        if (!ir_visit_ast_node(right)) {
            minic_log(LOG_ERROR, "or操作数解析失败");
            return false;
        }
        // 检查右操作数的值是否有效
        if (!right->val) {
            minic_log(LOG_ERROR, "or操作数值无效");
            return false;
        }
        node->blockInsts.addInst(right->blockInsts);
        BinaryInstruction * left_ne_0 = new BinaryInstruction(module->getCurrentFunction(),
                                                              IRInstOperator::IRINST_OP_ICMP_NE,
                                                              right->val,
                                                              module->newConstInt(0),
                                                              IntegerType::getTypeBool());
        node->blockInsts.addInst(left_ne_0);
        // 右节点跳转
        BranchCondInstruction * rightGotoInst =
            new BranchCondInstruction(module->getCurrentFunction(), left_ne_0, trueLabel, falseLabel);
        node->blockInsts.addInst(rightGotoInst);
    } else if (right->node_type == ast_operator_type::AST_OP_EQ || right->node_type == ast_operator_type::AST_OP_NE ||
               right->node_type == ast_operator_type::AST_OP_LE || right->node_type == ast_operator_type::AST_OP_GE ||
               right->node_type == ast_operator_type::AST_OP_LT || right->node_type == ast_operator_type::AST_OP_GT) {
        // 如果右操作数是一个关系表达式
        if (!ir_visit_ast_node(right)) {
            minic_log(LOG_ERROR, "or操作数解析失败");
            return false;
        }
        // 检查右操作数的值是否有效
        if (!right->val) {
            minic_log(LOG_ERROR, "or操作数值无效");
            return false;
        }
        node->blockInsts.addInst(right->blockInsts);
        // 右节点跳转
        BranchCondInstruction * rightGotoInst =
            new BranchCondInstruction(module->getCurrentFunction(), right->val, trueLabel, falseLabel);
        node->blockInsts.addInst(rightGotoInst);
    } else if (right->node_type == ast_operator_type::AST_OP_AND) {
        if (!ir_and(right, trueLabel, falseLabel)) {
            minic_log(LOG_ERROR, "or操作数解析失败");
            return false;
        }
        node->blockInsts.addInst(right->blockInsts);
    } else if (right->node_type == ast_operator_type::AST_OP_OR) {
        if (!ir_or(right, trueLabel, falseLabel)) {
            minic_log(LOG_ERROR, "or操作数解析失败");
            return false;
        }
        node->blockInsts.addInst(right->blockInsts);
    } else {
        minic_log(LOG_ERROR, "or操作数类型错误");
        return false;
    }

    return true;
}

/// @brief pos正号节点，生成对应的IR。
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_pos(ast_node * node)
{
    ast_node * src1_node = node->sons[0];

    // 处理操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left || !left->val) {
        minic_log(LOG_ERROR, "pos操作数解析失败");
        return false;
    }

    // 添加IR指令
    node->blockInsts.addInst(left->blockInsts);

    // 保存结果
    node->val = left->val;

    return true;
}

/// @brief neg负号节点，生成对应的IR。
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_neg(ast_node * node)
{
    ast_node * src1_node = node->sons[0];

    // 获取当前函数
    Function * currentFunc = module->getCurrentFunction();

    // 处理操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left || !left->val) {
        minic_log(LOG_ERROR, "neg操作数解析失败");
        return false;
    }
    // i1 -> i32
    CastInstruction * castInst = nullptr;
    if (left->val->getType()->isInt1Byte()) {
        castInst = new CastInstruction(currentFunc, left->val, IntegerType::getTypeInt());
        left->val = castInst;
    }

    // 创建IR指令
    UnaryInstruction * negInst = new UnaryInstruction(currentFunc, IRInstOperator::IRINST_OP_NEG, left->val);

    // 添加IR指令
    node->blockInsts.addInst(left->blockInsts);
    if (castInst) {
        node->blockInsts.addInst(castInst);
    }
    node->blockInsts.addInst(negInst);

    // 保存结果
    node->val = negInst;

    return true;
}

/// @brief not节点，生成对应的IR。
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_not(ast_node * node)
{
    ast_node * src1_node = node->sons[0];

    // 获取当前函数
    Function * currentFunc = module->getCurrentFunction();

    // 处理操作数
    ast_node * left = ir_visit_ast_node(src1_node);
    if (!left || !left->val) {
        minic_log(LOG_ERROR, "not操作数解析失败");
        return false;
    }

    if (left->val->getType() != IntegerType::getTypeBool()) {
        // 用icmp ne 0 + xor 代替not指令
        BinaryInstruction * notInst = new BinaryInstruction(currentFunc,
                                                            IRInstOperator::IRINST_OP_ICMP_NE,
                                                            left->val,
                                                            module->newConstInt(0),
                                                            IntegerType::getTypeBool());
        UnaryInstruction * xorInst = new UnaryInstruction(currentFunc, IRInstOperator::IRINST_OP_NOT, notInst);
        // 添加IR指令
        node->blockInsts.addInst(left->blockInsts);
        node->blockInsts.addInst(notInst);
        node->blockInsts.addInst(xorInst);
        // 保存结果
        node->val = xorInst;
    } else if (left->val->getType() == IntegerType::getTypeBool()) {
        // 直接使用not指令
        UnaryInstruction * notInst = new UnaryInstruction(currentFunc, IRInstOperator::IRINST_OP_NOT, left->val);
        // 添加IR指令
        node->blockInsts.addInst(left->blockInsts);
        node->blockInsts.addInst(notInst);
        // 保存结果
        node->val = notInst;
    } else {
        minic_log(LOG_ERROR, "not操作数类型错误");
        return false;
    }
    return true;
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
    if (module->findCurrentVarValue(constName)) {
        minic_log(LOG_ERROR, "常量(%s)重复声明", constName.c_str());
        return false;
    }

    // 创建常量
    if (node->sons[1]->node_type != ast_operator_type::AST_OP_ARRAY_DIMS) {
        Value * constValue;
        ast_node * init_expr_node = node->sons[1];
        if (!module->getCurrentFunction()) { // 全局常量
            // 处理初始化表达式
            if (node->sons.size() > 1) {
                if (!ir_visit_ast_node(init_expr_node)) {
                    minic_log(LOG_ERROR, "常量初始化表达式翻译失败");
                    return false;
                }
                constValue = module->newVarValue(constType, constName, init_expr_node->val);
            } else {
                minic_log(LOG_ERROR, "全局常量(%s)必须初始化", constName.c_str());
                return false;
            }
        } else { // 局部常量
            constValue = module->newVarValue(constType, constName);
            if (!constValue) {
                minic_log(LOG_ERROR, "常量(%s)创建失败", constName.c_str());
                return false;
            }
            // 处理初始化表达式
            if (node->sons.size() > 1) {
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
                StoreInstruction * movInst =
                    new StoreInstruction(module->getCurrentFunction(), constValue, init_expr_node->val, true);
                node->blockInsts.addInst(init_expr_node->blockInsts);
                node->blockInsts.addInst(movInst);
            } else {
                minic_log(LOG_ERROR, "局部常量(%s)必须初始化", constName.c_str());
                return false;
            }
        }
        constValue->setConst(true);
        constValue->setConstValue(init_expr_node->val);
        node->val = constValue;
        const_name_node->val = constValue;

        return true;
    } else {
        return false;

        // 数组常量定义
        ast_node * array_dims_node = node->sons[1];
        if (array_dims_node->sons.empty()) {
            minic_log(LOG_ERROR, "数组常量定义缺少维度信息");
            return false;
        }

        // 处理数组维度
        std::vector<int> dims;
        if (!ir_array_dims(array_dims_node, dims)) {
            minic_log(LOG_ERROR, "数组维度解析失败");
            return false;
        }

        // 创建数组常量
        ArrayType * arrayType = new ArrayType(constType, dims);
        Value * constValue = module->newVarValue(arrayType, constName);
        if (!constValue) {
            minic_log(LOG_ERROR, "数组常量(%s)创建失败", constName.c_str());
            return false;
        }

        // 创建初始化数组
    }
}

/// @brief 处理条件节点，生成对应的IR。
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_condition(ast_node * node, LabelInstruction * trueExitLabel, LabelInstruction * falseExitLabel)
{
    // 处理条件表达式
    // 1. 左值节点 或 一元表达式(! + -)
    // 2. 关系表达式 (==, !=, <, >, <=, >=)
    // 3. 逻辑表达式 (and or)
    // 4. 函数调用的返回值
    // 5. 数学表达式(+ - * / %)
    // 6. 常量
    return true;
}

/// @brief 处理宏定义点，生成对应的IR
/// @param node AST节点
/// @return 翻译是否成功，true：成功，false：失败
bool IRGenerator::ir_macro_decl(ast_node * node)
{
    // 宏定义在ast树已经优化，无需处理
    if (node->sons.size() < 2) {
        minic_log(LOG_ERROR, "宏定义节点的子节点数量不足");
        return false;
    }
    return true;
}