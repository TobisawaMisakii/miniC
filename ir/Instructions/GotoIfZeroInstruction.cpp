// GotoIfZeroInstruction.cpp
#include "GotoIfZeroInstruction.h"
#include "VoidType.h"
#include "LabelInstruction.h"
#include "Function.h"

/// 构造函数
/// @param _func 所属函数
/// @param _cond 条件值
/// @param _target 跳转目标
GotoIfZeroInstruction::GotoIfZeroInstruction(Function * _func, Value * _cond, Instruction * _target)
    : Instruction(_func, IRInstOperator::IRINST_OP_GOTO_IF_ZERO, VoidType::getType())
{
    this->target = static_cast<LabelInstruction *>(_target);
    this->addOperand(_cond); // 添加条件值
}

/// 获取条件值
Value * GotoIfZeroInstruction::getCond()
{
    return getOperand(0); // 获取条件值
}

/// 转换成字符串
void GotoIfZeroInstruction::toString(std::string & str)
{
    str = "br_if_zero " + this->cond->getIRName() + ", label " + target->getIRName();
}

/// 获取目标Label指令
LabelInstruction * GotoIfZeroInstruction::getTarget() const
{
    return target;
}
