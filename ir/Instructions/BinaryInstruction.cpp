///
/// @file BinaryInstruction.cpp
/// @brief 二元操作指令
///
/// @author zenglj (zenglj@live.com)
/// @version 1.0
/// @date 2024-09-29
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-09-29 <td>1.0     <td>zenglj  <td>新建
/// </table>
///
#include "BinaryInstruction.h"

/// @brief 构造函数
/// @param _op 操作符
/// @param _result 结果操作数
/// @param _srcVal1 源操作数1
/// @param _srcVal2 源操作数2
BinaryInstruction::BinaryInstruction(Function * _func,
                                     IRInstOperator _op,
                                     Value * _srcVal1,
                                     Value * _srcVal2,
                                     Type * _type)
    : Instruction(_func, _op, _type)
{
    addOperand(_srcVal1);
    addOperand(_srcVal2);
}

/// @brief 转换成字符串
/// @param str 转换后的字符串
void BinaryInstruction::toString(std::string & str)
{

    Value *src1 = getOperand(0), *src2 = getOperand(1);

    switch (op) {
        case IRInstOperator::IRINST_OP_ADD_I:
            // 整数加法指令
            str = getIRName() + " = add i32 " + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_ADD_F:
            // 浮点数加法指令
            str = getIRName() + " = fadd float " + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_SUB_I:
            // 减法指令
            str = getIRName() + " = sub i32 " + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_SUB_F:
            // 浮点数减法指令
            str = getIRName() + " = fsub float " + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_MUL_I:
            // 乘法指令
            str = getIRName() + " = mul i32 " + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_MUL_F:
            // 浮点数乘法指令
            str = getIRName() + " = fmul float " + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_DIV_I:
            // 浮点数乘法指令
            str = getIRName() + " = div i32 " + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_DIV_F:
            // 浮点数乘法指令
            str = getIRName() + " = fdiv float " + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_MOD_I:
            // 浮点数乘法指令
            str = getIRName() + " = mod i32 " + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_MOD_F:
            // 浮点数乘法指令
            str = getIRName() + " = fmod float " + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_ICMP_LT:
            // 小于比较指令，指令格式为：<result> = icmp <cond> <ty> <op1>, <op2>
            str = getIRName() + " = icmp slt i32 " + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_FCMP_LT:
            // 小于比较指令 float
            str = getIRName() + " = fcmp olt float" + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_ICMP_GT:
            // 大于比较指令
            str = getIRName() + " = icmp sgt i32 " + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_FCMP_GT:
            // 大于比较指令 float
            str = getIRName() + " = fcmp ogt float " + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_ICMP_EQ:
            // 等于比较指令
            str = getIRName() + " = icmp eq i32 " + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_FCMP_EQ:
            // 等于比较指令 float
            str = getIRName() + " = fcmp oeq float " + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_ICMP_NE:
            // 不等于比较指令
            str = getIRName() + " = icmp ne i32 " + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_FCMP_NE:
            // 不等于比较指令 float
            str = getIRName() + " = fcmp one float " + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_ICMP_LE:
            // 小于等于比较指令
            str = getIRName() + " = icmp sle i32 " + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_FCMP_LE:
            // 小于等于比较指令 float
            str = getIRName() + " = fcmp ole float " + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_ICMP_GE:
            // 大于等于比较指令
            str = getIRName() + " = icmp sge i32 " + src1->getIRName() + ", " + src2->getIRName();
            break;
        case IRInstOperator::IRINST_OP_FCMP_GE:
            // 大于等于比较指令 float
            str = getIRName() + " = fcmp oge float " + src1->getIRName() + ", " + src2->getIRName();
            break;

        default:
            // 未知指令
            Instruction::toString(str);
            break;
    }
}
