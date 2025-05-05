// GotoIfZeroInstruction.cpp
#include "GotoIfZeroInstruction.h"
#include "VoidType.h"
#include "LabelInstruction.h"
#include "Function.h"

/// 构造函数
/// @param func 所属函数
/// @param cond 条件值
/// @param target 跳转目标
GotoIfZeroInstruction::GotoIfZeroInstruction(Function * func, Value * cond, Instruction * target)
    : Instruction(func, IRInstOperator::IRINST_OP_GOTO_IF_ZERO, VoidType::getType())
{
    this->target = static_cast<LabelInstruction *>(target);
    this->addOperand(cond); // 添加条件值
}

/// 获取条件值
Value * GotoIfZeroInstruction::getCond() const
{
    return this->cond;
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
