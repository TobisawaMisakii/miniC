// BranchCondInstruction.cpp
#include "BranchConditional.h"
#include "Types/VoidType.h"
#include "LabelInstruction.h"
#include "Function.h"

/// 构造函数
/// @param _func 所属函数
/// @param _cond 条件值
/// @param _target 跳转目标
BranchCondInstruction::BranchCondInstruction(Function * _func,
                                             Value * _cond,
                                             Instruction * _target_0,
                                             Instruction * _target_1)
    : Instruction(_func, IRInstOperator::IRINST_OP_GOTO_IF_ZERO, VoidType::getType()), cond(_cond),
      target_0(static_cast<LabelInstruction *>(_target_0)), target_1(static_cast<LabelInstruction *>(_target_1))
{
    addOperand(_cond);
}

/// 获取条件值
Value * BranchCondInstruction::getCond()
{
    return getOperand(0); // 获取条件值
}

/// 转换成字符串
void BranchCondInstruction::toString(std::string & str)
{
    str = "bc " + this->cond->getIRName() + ", label " + target_0->getIRName() + ", label " + target_1->getIRName();
}

/// 获取目标Label指令
LabelInstruction * BranchCondInstruction::getTarget(int no) const
{
    if (no == 0) {
        return target_0;
    } else if (no == 1) {
        return target_1;
    }
    return nullptr;
}
