#include "GetElementPtrInstruction.h"
#include "Types/PointerType.h"
GetElementPtrInstruction::GetElementPtrInstruction(Function * func,
                                                   Value * basePtr,
                                                   const std::vector<Value *> & indices,
                                                   Type * resultType)
    : Instruction(func, IRInstOperator::IRINST_OP_MAX, resultType), basePtr(basePtr), indices(indices),
      resultType(resultType)
{
    addOperand(basePtr);
    for (auto idx: indices)
        addOperand(idx);
}

void GetElementPtrInstruction::toString(std::string & str)
{
    str = getIRName() + " = getelementptr inbounds ";
    if (resultType->isIntegerType()) {
        str += resultType->toString() + ", ";
    } else {
        str += basePtr->getType()->toString() + ", ";
    }
    if (resultType->isPointerType() && basePtr->getType()->isArrayType()) {
        str += basePtr->getType()->toString() + "* " + basePtr->getIRName();
    } else {
        str += basePtr->getType()->toString() + " " + basePtr->getIRName();
    }

    for (auto & idx: indices) {
        str += ", " + idx->getType()->toString() + " " + idx->getIRName();
    }
}