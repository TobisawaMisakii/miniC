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
                                             Instruction * _target_1,
                                             Instruction * _target_0)
    : Instruction(_func, IRInstOperator::IRINST_OP_GOTO_IF_ZERO, VoidType::getType()), cond(_cond),
      target_1(static_cast<LabelInstruction *>(_target_1)), target_0(static_cast<LabelInstruction *>(_target_0))
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
    str = "br " + this->cond->getType()->toString() + " " + this->cond->getIRName() + ", label %" +
          target_1->getIRName() + ", label %" + target_0->getIRName();
}

/// 获取目标Label指令
LabelInstruction * BranchCondInstruction::getTarget(int condIsCorrect) const
{
    if (condIsCorrect == 0) {
        return target_0;
    } else if (condIsCorrect == 1) {
        return target_1;
    }
    return nullptr;
}
