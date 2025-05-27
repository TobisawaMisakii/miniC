#include "BitCastInstruction.h"

BitCastInstruction::BitCastInstruction(Function * func, Value * srcVal, Type * destType)
    : Instruction(func, IRInstOperator::IRINST_OP_MAX, destType), srcVal(srcVal), destType(destType)
{
    addOperand(srcVal);
}

void BitCastInstruction::toString(std::string & str)
{
    str = getIRName() + " = bitcast ";
    if (srcVal->getType()->isIntegerType())
        str += srcVal->getType()->toString() + "* " + srcVal->getIRName();
    else {
        str += srcVal->getType()->toString() + " " + srcVal->getIRName();
    }
    str += " to " + destType->toString();
}