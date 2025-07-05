#include "Instruction.h"
#include "UnaryInstruction.h"
#include "Function.h"

/// @brief 构造函数
/// @param _func 所属函数
/// @param op 操作符
/// @param srcVal1 源操作数
/// @param result 结果值
UnaryInstruction::UnaryInstruction(Function * _func, IRInstOperator _op, Value * _srcVal1)
    : Instruction(_func, _op, _srcVal1->getType()), srcVal1(_srcVal1), op(_op)
{
    addOperand(_srcVal1);
}

/// @brief 转换成字符串
/// @param str 转换后的字符串
void UnaryInstruction::toString(std::string & str)
{
    switch (op) {
        case IRInstOperator::IRINST_OP_NEG:
            if (srcVal1->getType()->isFloatType()) {
                str = getIRName() + " = fsub float 0.0, " + srcVal1->getIRName();
            } else if (srcVal1->getType()->isInt32Type()) {
                str = getIRName() + " = sub i32 0, " + srcVal1->getIRName();
            }

            break;
        case IRInstOperator::IRINST_OP_NOT:
            str = getIRName() + " = xor " + srcVal1->getType()->toString() + " " + srcVal1->getIRName() + ", true";
            break;

        default:
            str = getIRName() + " = unknown unary" + srcVal1->getIRName();
            break;
    }
}