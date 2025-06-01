#include "LoadInstruction.h"
#include "PointerType.h"

LoadInstruction::LoadInstruction(Function * _func, Value * _sourcePtr, bool _notstore)
    : Instruction(_func, IRInstOperator::IRINST_OP_LOAD, _sourcePtr->getType()), source(_sourcePtr), notstore(_notstore)
{
    addOperand(_sourcePtr);
}

/// @brief 转换成字符串显示
/// @param str 转换后的字符串
void LoadInstruction::toString(std::string & str)
{
    // 处理 source 类型，循环展开指针
    Type * tSrc = source->getType();
    int pointerLevelSrc = 0;
    while (tSrc->isPointerType()) {
        pointerLevelSrc++;
        tSrc = const_cast<Type *>(static_cast<const PointerType *>(tSrc)->getPointeeType());
    }
    if (notstore)
        pointerLevelSrc = 0;
    std::string typeStrSrc = tSrc->toString();
    for (int i = 0; i < pointerLevelSrc + 1; ++i) {
        typeStrSrc += "*";
    }

    // load 指令左边类型是去掉一层指针的类型
    std::string typeStrDst = tSrc->toString();
    for (int i = 0; i < pointerLevelSrc; ++i) {
        typeStrDst += "*";
    }

    int align = (pointerLevelSrc > 0) ? 8 : 4;
    str = getIRName() + " = load " + typeStrDst + ", " + typeStrSrc + " " + source->getIRName() + ", align " +
          std::to_string(align);
}
