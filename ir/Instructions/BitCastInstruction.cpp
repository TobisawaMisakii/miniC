#include "BitCastInstruction.h"

BitCastInstruction::BitCastInstruction(Function * func, Value * srcVal, Type * destType)
    : Instruction(func, IRInstOperator::IRINST_OP_MAX, destType), srcVal(srcVal), destType(destType)
{
    addOperand(srcVal);
}

void BitCastInstruction::toString(std::string & str)
{
    str = getIRName() + " = bitcast ";
    str += srcVal->getType()->toString() + "* " + srcVal->getIRName();
    str += " to " + destType->toString() + "*";
}
