#include "GetElementPtrInstruction.h"

GetElementPtrInstruction::GetElementPtrInstruction(Function * func,
                                                   Value * basePtr,
                                                   const std::vector<Value *> & indices,
                                                   Type * resultType)
    : Instruction(func, IRInstOperator::IRINST_OP_MAX, resultType), basePtr(basePtr), indices(indices)
{
    addOperand(basePtr);
    for (auto idx: indices)
        addOperand(idx);
}

void GetElementPtrInstruction::toString(std::string & str)
{
    str = getIRName() + " = getelementptr inbounds ";
    str += basePtr->getType()->toString() + ", ";
    str += basePtr->getType()->toString() + "* " + basePtr->getIRName();
    for (auto idx: indices) {
        str += ", " + idx->getType()->toString() + " ";
        str += idx->getIRName();
    }
}