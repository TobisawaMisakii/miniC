// ExtensionInstruction.cpp
#include "CastInstruction.h"
#include "Types/IntegerType.h"

#include <string>

// 根据_extType的值，构造不同的IR指令，选择不同的操作码
CastInstruction::CastInstruction(Function * _func, CastType _castType, Value * _value, Type * _resultType)
    : Instruction(_func, IRInstOperator::IRINST_OP_MAX, _resultType), castType(_castType), value(_value),
      resultType(_resultType)
{
    // 设置操作码
    switch (castType) {
        case CastType::ZEXT:
            op = IRInstOperator::IRINST_OP_ZEXT;
            break;
        case CastType::SEXT:
            op = IRInstOperator::IRINST_OP_SEXT;
            break;
        case CastType::SITOFP:
            op = IRInstOperator::IRINST_OP_SITOFP;
            break;
        case CastType::FPTOSI:
            op = IRInstOperator::IRINST_OP_FPTOSI;
            break;
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