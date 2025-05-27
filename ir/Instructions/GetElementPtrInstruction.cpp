#include "GetElementPtrInstruction.h"
#include "PointerType.h"

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
    // 展开 basePtr 类型的指针层数
    Type * t = basePtr->getType();
    int pointerLevel = 0;
    while (t->isPointerType()) {
        pointerLevel++;
        t = const_cast<Type *>(static_cast<const PointerType *>(t)->getPointeeType());
    }
    std::string typeStr = t->toString();
    for (int i = 0; i < pointerLevel - 1; ++i) {
        typeStr += "*";
    }

    str = getIRName() + " = getelementptr inbounds ";
    str += typeStr + ", ";
    str += typeStr + "* " + basePtr->getIRName();
    for (auto idx: indices) {
        str += ", " + idx->getType()->toString() + " ";
        str += idx->getIRName();
    }
}