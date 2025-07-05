// ExtensionInstruction.cpp
#include "CastInstruction.h"
#include "Types/IntegerType.h"

#include <string>

// 根据_extType的值，构造不同的IR指令，选择不同的操作码
CastInstruction::CastInstruction(Function * _func, Value * _value, Type * _resultType)
    : Instruction(_func, IRInstOperator::IRINST_OP_MAX, _resultType), value(_value), resultType(_resultType)
{
    if (value->getType() == resultType) {
        delete this;
        return;
    }
    addOperand(_value);

    // 设置操作码
    if (resultType == IntegerType::getTypeInt64() && value->getType() == IntegerType::getTypeInt()) {
        castType = CastType::SEXT;
    } else if (resultType == IntegerType::getTypeInt() && value->getType() == IntegerType::getTypeInt()) {
        castType = CastType::SEXT;
    } else if (resultType == IntegerType::getTypeInt() && value->getType() == IntegerType::getTypeBool()) {
        castType = CastType::ZEXT;
    } else if (resultType->isFloatType() && value->getType() == IntegerType::getTypeInt()) {
        castType = CastType::SITOFP;
    } else if (resultType == IntegerType::getTypeInt() && value->getType()->isFloatType()) {
        castType = CastType::FPTOSI;
    }
}

// 转换成IR指令文本
void CastInstruction::toString(std::string & str)
{
    str = getIRName() + " = ";
    std::string opStr;
    switch (castType) {
        case CastType::ZEXT:
            opStr = "zext";
            break;
        case CastType::SEXT:
            opStr = "sext";
            break;
        case CastType::SITOFP:
            opStr = "sitofp";
            break;
        case CastType::FPTOSI:
            opStr = "fptosi";
            break;
    }
    str += opStr + " ";
    str += value->getType()->toString() + " ";
    str += value->getIRName() + " to ";
    str += getResultType()->toString();
}

// 获取目标类型
Type * CastInstruction::getResultType() const
{
    return resultType;
}