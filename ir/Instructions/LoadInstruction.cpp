#include "LoadInstruction.h"

LoadInstruction::LoadInstruction(Function * _func, Value * _sourcePtr)
    : Instruction(_func, IRInstOperator::IRINST_OP_LOAD, _sourcePtr->getType()), source(_sourcePtr)
{
    addOperand(_sourcePtr);
}

/// @brief 转换成字符串显示
/// @param str 转换后的字符串
void LoadInstruction::toString(std::string & str)
{
    str = getIRName() + " = load " + source->getType()->toString() + ", " + source->getType()->toString() + "* " +
          source->getIRName() + ", align 4";
}
