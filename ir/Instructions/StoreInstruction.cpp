#include "StoreInstruction.h"

StoreInstruction::StoreInstruction(Function * _func, Value * _result, Value * _sourcePtr)
    : Instruction(_func, IRInstOperator::IRINST_OP_LOAD, _result->getType()), source(_sourcePtr)
{
    addOperand(_result);
    addOperand(_sourcePtr);
}

/// @brief 转换成字符串显示
/// @param str 转换后的字符串
void StoreInstruction::toString(std::string & str)
{
    Value * result = getOperand(0);
    str = "store " + source->getType()->toString() + " " + source->getIRName() + ", " + result->getType()->toString() +
          "* " + result->getIRName() + ", align 4";
}
