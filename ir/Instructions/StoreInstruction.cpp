#include "StoreInstruction.h"
#include "PointerType.h"

StoreInstruction::StoreInstruction(Function * _func,
                                   Value * _result,
                                   Value * _sourcePtr,
                                   bool _isFormalRes,
                                   bool _isFormalSrc)
    : Instruction(_func, IRInstOperator::IRINST_OP_LOAD, _result->getType()), result(_result), source(_sourcePtr),
      isFormalRes(_isFormalRes), isFormalSrc(_isFormalSrc)
{
    addOperand(_result);
    addOperand(_sourcePtr);
}

/// @brief 转换成字符串显示
/// @param str 转换后的字符串
void StoreInstruction::toString(std::string & str)
{
    // 处理 source 类型
    Type * tSrc = source->getType();
    int pointerLevelSrc = 0;
    while (tSrc->isPointerType()) {
        pointerLevelSrc++;
        tSrc = const_cast<Type *>(static_cast<const PointerType *>(tSrc)->getPointeeType());
    }
    if (isFormalSrc)
        pointerLevelSrc++;
    std::string typeStrSrc = tSrc->toString();
    for (int i = 0; i < pointerLevelSrc - 1; ++i) {
        typeStrSrc += "*";
    }

    // 处理 result 类型（注意：LLVM IR store 的目标类型本身已经是指针，不要多加一层*）
    Type * tRes = result->getType();
    int pointerLevelRes = 0;
    while (tRes->isPointerType()) {
        pointerLevelRes++;
        tRes = const_cast<Type *>(static_cast<const PointerType *>(tRes)->getPointeeType());
    }
    if (isFormalRes)
        pointerLevelRes++;
    std::string typeStrRes = tRes->toString();
    for (int i = 0; i < pointerLevelRes; ++i) {
        typeStrRes += "*";
    }

    if (result->getType()->isPointerType()) {
        str = "store " + typeStrSrc + " " + source->getIRName() + ", " + typeStrRes + " " + result->getIRName() +
              ", align 8";
    } else {
        str = "store " + typeStrSrc + " " + source->getIRName() + ", " + typeStrRes + " " + result->getIRName() +
              ", align 4";
    }
}
