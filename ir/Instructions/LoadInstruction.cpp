#include "LoadInstruction.h"

LoadInstruction::LoadInstruction(Function * _func, Value * _sourcePtr, Type * _destType)
    : Instruction(_func, IRInstOperator::IRINST_OP_LOAD, _destType), source(_sourcePtr), destType(_destType)
{
    addOperand(_sourcePtr);
}
/// @brief 转换成字符串显示
/// @param str 转换后的字符串
void LoadInstruction::toString(std::string & str)
{
    str = getIRName() + " = load ";
    str += destType->toString() + ", ";
    if (source->getType()->isPointerType())
        str += source->getType()->toString() + " ";
    else
        str += source->getType()->toString() + "* ";
    str += source->getIRName() + ", align 4";
}
