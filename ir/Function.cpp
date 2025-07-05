///
/// @file Function.cpp
/// @brief 函数实现
/// @author zenglj (zenglj@live.com)
/// @version 1.0
/// @date 2024-11-21
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-11-21 <td>1.0     <td>zenglj  <td>新做
/// </table>
///

#include <cstdlib>
#include <string>

#include "IRConstant.h"
#include "Function.h"

/// @brief 指定函数名字、函数类型的构造函数
/// @param _name 函数名称
/// @param _type 函数类型
/// @param _builtin 是否是内置函数
Function::Function(std::string _name, FunctionType * _type, bool _builtin)
    : GlobalValue(_type, _name), builtIn(_builtin)
{
    returnType = _type->getReturnType();

    // 设置对齐大小
    setAlignment(1);
}

///
/// @brief 析构函数
/// @brief 释放函数占用的内存和IR指令代码
/// @brief 注意：IR指令代码并未释放，需要手动释放
Function::~Function()
{
    Delete();
}

/// @brief 获取函数返回类型
/// @return 返回类型
Type * Function::getReturnType()
{
    return returnType;
}

/// @brief 获取函数的形参列表
/// @return 形参列表
std::vector<FormalParam *> & Function::getParams()
{
    return params;
}

/// @brief 加入函数的形参列表
void Function::addParam(FormalParam * param)
{
    params.push_back(param);
}

/// @brief 获取函数内的IR指令代码
/// @return IR指令代码
InterCode & Function::getInterCode()
{
    return code;
}

/// @brief 判断该函数是否是内置函数
/// @return true: 内置函数，false：用户自定义
bool Function::isBuiltin()
{
    return builtIn;
}

/// @brief 函数指令信息输出
/// @param str 函数指令
void Function::toString(std::string & str)
{
    if (builtIn) {
        std::string name = getIRName();
        if (name == "@getarray") {
            // 内置函数的声明
            str = "declare dso_local i32 @getarray(...)\n";
            return;
        } else if (name == "@getfarray") {
            // 内置函数的声明
            str = "declare dso_local float @getfarray(...)\n";
            return;
        }
        str += "declare ";
        str += getReturnType()->toString() + " " + getIRName() + "(";
        bool firstParam = false;
        for (auto & param: params) {
            if (!firstParam) {
                firstParam = true;
            } else {
                str += ", ";
            }
            str += param->getType()->toString();
        }
        if (!firstParam) {
            str += "...";
        }
        str += ");\n";
        return;
    }
    // 输出函数头
    str = "define " + getReturnType()->toString() + " " + getIRName() + "(";

    bool firstParam = false;
    for (auto & param: params) {
        if (!firstParam) {
            firstParam = true;
        } else {
            str += ", ";
        }
        str += param->toString();
    }
    str += ")\n";
    str += "{\n";

    // 输出局部变量的名字与IR名字
    for (auto & var: this->varsVector) {

        // 检查变量是否为数组类型
        if (var->getType()->isPointerType()) {
            Type * t = var->getType();
            std::string typeStr;
            int pointerLevel = 0;

            // 统计指针层数
            while (t->isPointerType()) {
                pointerLevel++;
                t = const_cast<Type *>(static_cast<const PointerType *>(t)->getPointeeType());
            }
            // 基础类型字符串
            typeStr = t->toString();
            // 拼接指针层数
            for (int i = 0; i < pointerLevel; ++i) {
                typeStr += "*";
            }

            // 推荐：根据类型自动设置对齐
            int align = (pointerLevel > 0) ? 8 : 4;

            str += "\t" + var->getIRName() + " = alloca " + typeStr + ", align " + std::to_string(align);

            std::string realName = var->getName();
            if (!realName.empty()) {
                str += " ; " + std::to_string(var->getScopeLevel()) + ":" + realName;
            }
        } else if (var->getType()->isArrayType()) {
            ArrayType * arrayType = dynamic_cast<ArrayType *>(var->getType());
            if (arrayType) {
                str += "\t" + var->getIRName() + " = alloca " + arrayType->toString() + ", align 16";
                str += " ;  " + std::to_string(var->getScopeLevel()) + ":" + var->getName();
            }
        } else {
            // 普通变量声明
            str += "\t" + var->getIRName() + " = alloca " + var->getType()->toString() + ", align 4";
            std::string realName = var->getName();
            if (!realName.empty()) {
                str += " ; " + std::to_string(var->getScopeLevel()) + ":" + realName;
            }
        }

        str += "\n";
    }

    // 遍历所有的线性IR指令，文本输出
    // 记录上一个指令，避免连续空Label输出
    Instruction * lastInst = nullptr;
    for (auto & inst: code.getInsts()) {

        std::string instStr;
        inst->toString(instStr);

        if (!instStr.empty()) {

            if (inst->getOp() == IRInstOperator::IRINST_OP_LABEL) {
                if (lastInst && lastInst->getOp() != IRInstOperator::IRINST_OP_LABEL &&
                    lastInst->getOp() != IRInstOperator::IRINST_OP_GOTO_IF_ZERO &&
                    lastInst->getOp() != IRInstOperator::IRINST_OP_GOTO &&
                    lastInst->getOp() != IRInstOperator::IRINST_OP_EXIT) {
                    str += "\tbr label %" + inst->getIRName() + "\n";
                }
                // 删除连续的空Label指令
                if (lastInst && lastInst->getOp() == IRInstOperator::IRINST_OP_LABEL) {
                    str += "";
                    continue;
                } else {
                    // Label指令不加Tab键
                    str += instStr + "\n";
                }
            } else if (inst->getOp() == IRInstOperator::IRINST_OP_GOTO_IF_ZERO ||
                       inst->getOp() == IRInstOperator::IRINST_OP_GOTO) {
                if (lastInst && (lastInst->getOp() == IRInstOperator::IRINST_OP_GOTO_IF_ZERO ||
                                 lastInst->getOp() == IRInstOperator::IRINST_OP_GOTO)) {
                    str += "";
                    continue;
                } else {
                    str += "\t" + instStr + "\n";
                }
            } else {
                str += "\t" + instStr + "\n";
            }
            lastInst = inst;
        }
    }

    // 输出函数尾部
    str += "}\n";
}

/// @brief 设置函数出口指令
/// @param inst 出口Label指令
void Function::setExitLabel(Instruction * inst)
{
    exitLabel = inst;
}

/// @brief 获取函数出口指令
/// @return 出口Label指令
Instruction * Function::getExitLabel()
{
    return exitLabel;
}

/// @brief 设置函数返回值变量
/// @param val 返回值变量，要求必须是局部变量，不能是临时变量
void Function::setReturnValue(Value * val)
{
    returnValue = val;
}

/// @brief 获取函数返回值变量
/// @return 返回值变量
Value * Function::getReturnValue()
{
    return returnValue;
}

/// @brief 获取最大栈帧深度
/// @return 栈帧深度
int Function::getMaxDep()
{
    return maxDepth;
}

/// @brief 设置最大栈帧深度
/// @param dep 栈帧深度
void Function::setMaxDep(int dep)
{
    maxDepth = dep;

    // 设置函数栈帧被重定位标记，用于生成不同的栈帧保护代码
    relocated = true;
}

/// @brief 获取本函数需要保护的寄存器
/// @return 要保护的寄存器
std::vector<int32_t> & Function::getProtectedReg()
{
    return protectedRegs;
}

/// @brief 获取本函数需要保护的寄存器字符串
/// @return 要保护的寄存器
std::string & Function::getProtectedRegStr()
{
    return protectedRegStr;
}

/// @brief 获取函数调用参数个数的最大值
/// @return 函数调用参数个数的最大值
int Function::getMaxFuncCallArgCnt()
{
    return maxFuncCallArgCnt;
}

/// @brief 设置函数调用参数个数的最大值
/// @param count 函数调用参数个数的最大值
void Function::setMaxFuncCallArgCnt(int count)
{
    maxFuncCallArgCnt = count;
}

/// @brief 函数内是否存在函数调用
/// @return 是否存在函调用
bool Function::getExistFuncCall()
{
    return funcCallExist;
}

/// @brief 设置函数是否存在函数调用
/// @param exist true: 存在 false: 不存在
void Function::setExistFuncCall(bool exist)
{
    funcCallExist = exist;
}

/// @brief 新建变量型Value。先检查是否存在，不存在则创建，否则失败
/// @param name 变量ID
/// @param type 变量类型
/// @param scope_level 局部变量的作用域层级
LocalVariable * Function::newLocalVarValue(Type * type, std::string name, int32_t scope_level)
{
    // 创建变量并加入符号表
    LocalVariable * varValue = new LocalVariable(type, name, scope_level);
    // varsVector表中可能存在变量重名的信息
    varsVector.push_back(varValue);

    return varValue;
}

/// @brief 新建一个内存型的Value，并加入到符号表，用于后续释放空间
/// \param type 变量类型
/// \return 临时变量Value
MemVariable * Function::newMemVariable(Type * type)
{
    // 肯定唯一存在，直接插入即可
    MemVariable * memValue = new MemVariable(type);

    memVector.push_back(memValue);

    return memValue;
}

/// @brief 清理函数内申请的资源
void Function::Delete()
{
    // 清理IR指令
    code.Delete();

    // 清理Value
    for (auto & var: varsVector) {
        delete var;
    }

    varsVector.clear();
}

///
/// @brief 函数内的Value重命名
///
void Function::renameIR()
{
    // 内置函数忽略
    if (isBuiltin()) {
        return;
    }

    int32_t nameIndex = 0;

    // 形式参数重命名
    for (auto & param: this->params) {
        param->setIRName(IR_TEMP_VARNAME_PREFIX + std::to_string(nameIndex++));
    }

    // 局部变量重命名
    for (auto & var: this->varsVector) {

        var->setIRName(IR_LOCAL_VARNAME_PREFIX + std::to_string(nameIndex++));
    }

    // 遍历所有的指令进行命名
    Instruction * lastInst = nullptr;
    for (auto inst: this->getInterCode().getInsts()) {
        if (inst->getOp() == IRInstOperator::IRINST_OP_LABEL) {
            if (lastInst && lastInst->getOp() == IRInstOperator::IRINST_OP_LABEL) {
                // 如果上一个指令也是Label指令，则用上一条指令的名字，且在 outputIR 时不输出该指令
                inst->setIRName(lastInst->getIRName());
                continue;
            }
            // Label指令的命名
            inst->setIRName(IR_LABEL_PREFIX + std::to_string(nameIndex++));
        } else if (inst->hasResultValue()) {
            inst->setIRName(IR_TEMP_VARNAME_PREFIX + std::to_string(nameIndex++));
        }
        // 记录上一个指令
        lastInst = inst;
    }
}

///
/// @brief 获取统计的ARG指令的个数
/// @return int32_t 个数
///
int32_t Function::getRealArgcount()
{
    return this->realArgCount;
}

///
/// @brief 用于统计ARG指令个数的自增函数，个数加1
///
void Function::realArgCountInc()
{
    this->realArgCount++;
}

///
/// @brief 用于统计ARG指令个数的清零
///
void Function::realArgCountReset()
{
    this->realArgCount = 0;
}