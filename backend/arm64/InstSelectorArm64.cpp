///
/// @file InstSelectorArm64.cpp
/// @brief 指令选择器-ARM64的实现
/// @author zenglj (zenglj@live.com)
/// @version 1.0
/// @date 2024-11-21
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-11-21 <td>1.0     <td>zenglj  <td>新做
/// </table>
///
#include <cstdio>

#include "Common.h"
#include "ILocArm64.h"
#include "InstSelectorArm64.h"
#include "PlatformArm64.h"

#include "PointerType.h"
#include "RegVariable.h"
#include "Function.h"

#include "LabelInstruction.h"
#include "GotoInstruction.h"
#include "FuncCallInstruction.h"
#include "MoveInstruction.h"
#include "SimpleRegisterAllocator.h"
///
/// @brief 引用main.c的全局变量，为了便于控制
///
extern bool gAsmAlsoShowIR;

/// @brief 构造函数
/// @param _irCode 指令
/// @param _iloc ILoc
/// @param _func 函数
InstSelectorArm64::InstSelectorArm64(vector<Instruction *> & _irCode,
                                     ILocArm64 & _iloc,
                                     Function * _func,
                                     SimpleRegisterAllocator & allocator)
    : ir(_irCode), iloc(_iloc), func(_func), simpleRegisterAllocator(allocator)
{
    translator_handlers[IRInstOperator::IRINST_OP_ENTRY] = &InstSelectorArm64::translate_entry;
    translator_handlers[IRInstOperator::IRINST_OP_EXIT] = &InstSelectorArm64::translate_exit;

    translator_handlers[IRInstOperator::IRINST_OP_LABEL] = &InstSelectorArm64::translate_label;
    translator_handlers[IRInstOperator::IRINST_OP_GOTO] = &InstSelectorArm64::translate_goto;

    translator_handlers[IRInstOperator::IRINST_OP_ASSIGN] = &InstSelectorArm64::translate_assign;

    translator_handlers[IRInstOperator::IRINST_OP_ADD_I] = &InstSelectorArm64::translate_add_int64;
    translator_handlers[IRInstOperator::IRINST_OP_ADD_F] = &InstSelectorArm64::translate_add_float;
    translator_handlers[IRInstOperator::IRINST_OP_SUB_I] = &InstSelectorArm64::translate_sub_int64;
    translator_handlers[IRInstOperator::IRINST_OP_SUB_F] = &InstSelectorArm64::translate_sub_float;

    // 乘除法
    translator_handlers[IRInstOperator::IRINST_OP_MUL_I] = &InstSelectorArm64::translate_mul_int64;
    translator_handlers[IRInstOperator::IRINST_OP_MUL_F] = &InstSelectorArm64::translate_mul_float;
    translator_handlers[IRInstOperator::IRINST_OP_DIV_I] = &InstSelectorArm64::translate_div_int64;
    translator_handlers[IRInstOperator::IRINST_OP_DIV_F] = &InstSelectorArm64::translate_div_float;

    translator_handlers[IRInstOperator::IRINST_OP_FUNC_CALL] = &InstSelectorArm64::translate_call;
    translator_handlers[IRInstOperator::IRINST_OP_ARG] = &InstSelectorArm64::translate_arg;
    // load
    translator_handlers[IRInstOperator::IRINST_OP_LOAD] = &InstSelectorArm64::translate_load;
}

///
/// @brief 析构函数
///
InstSelectorArm64::~InstSelectorArm64()
{}

/// @brief 指令选择执行
void InstSelectorArm64::run()
{
    for (auto inst: ir) {

        // 逐个指令进行翻译
        if (!inst->isDead()) {
            translate(inst);
        }
    }
}

/// @brief 指令翻译成ARM64汇编
/// @param inst IR指令
void InstSelectorArm64::translate(Instruction * inst)
{
    // 操作符
    IRInstOperator op = inst->getOp();

    map<IRInstOperator, translate_handler>::const_iterator pIter;
    pIter = translator_handlers.find(op);
    if (pIter == translator_handlers.end()) {
        // 没有找到，则说明当前不支持
        printf("Translate: Operator(%d) not support", (int) op);
        return;
    }

    // 开启时输出IR指令作为注释
    // if (gAsmAlsoShowIR) {
    //     outputIRInstruction(inst);
    // }

    (this->*(pIter->second))(inst);
}

///
/// @brief 输出IR指令
///
void InstSelectorArm64::outputIRInstruction(Instruction * inst)
{
    std::string irStr;
    inst->toString(irStr);
    if (!irStr.empty()) {
        iloc.comment(irStr);
    }
}

/// @brief NOP翻译成ARM64汇编
/// @param inst IR指令
void InstSelectorArm64::translate_nop(Instruction * inst)
{
    (void) inst;
    iloc.nop();
}

/// @brief Label指令指令翻译成ARM64汇编
/// @param inst IR指令
void InstSelectorArm64::translate_label(Instruction * inst)
{
    Instanceof(labelInst, LabelInstruction *, inst);

    iloc.label(labelInst->getName());
}

/// @brief goto指令指令翻译成ARM64汇编
/// @param inst IR指令
void InstSelectorArm64::translate_goto(Instruction * inst)
{
    Instanceof(gotoInst, GotoInstruction *, inst);

    // 无条件跳转
    iloc.jump(gotoInst->getTarget()->getName());
}

/// @brief 函数入口指令翻译成ARM64汇编
/// @param inst IR指令
void InstSelectorArm64::translate_entry(Instruction * inst)
{
    auto & protectedRegNo = func->getProtectedReg();
    auto & protectedRegStr = func->getProtectedRegStr();
    bool first = true;
    for (auto regno: protectedRegNo) {
        if (first) {
            protectedRegStr = PlatformArm64::regName[regno];
            first = false;
        } else {
            protectedRegStr += "," + PlatformArm64::regName[regno];
        }
    }

    // 计算总栈帧大小（含保护寄存器空间，保证16字节对齐）
    int funcCallArgCnt = func->getMaxFuncCallArgCnt() - 8;
    funcCallArgCnt = std::max(funcCallArgCnt, 0);
    int off = func->getMaxDep();
    off += funcCallArgCnt * 8;
    int save_size = 0;
    if (protectedRegNo.size() == 2)
        save_size = 16;
    else if (protectedRegNo.size() == 1)
        save_size = 8;
    int frame_size = off + save_size;
    if (frame_size % 16 != 0)
        frame_size += 16 - (frame_size % 16);

    // 保存fp/lr并分配栈帧
    if (protectedRegNo.size() == 2) {
        iloc.inst("stp",
                  PlatformArm64::regName[protectedRegNo[0]],
                  PlatformArm64::regName[protectedRegNo[1]],
                  "[sp, #-" + iloc.toStr(save_size, false) + "]!");
    } else if (protectedRegNo.size() == 1) {
        iloc.inst("str", PlatformArm64::regName[protectedRegNo[0]], "[sp, #-" + iloc.toStr(save_size, false) + "]!");
    }

    iloc.inst("sub",
              PlatformArm64::regName[ARM64_SP_REG_NO],
              PlatformArm64::regName[ARM64_SP_REG_NO],
              iloc.toStr(frame_size - save_size, false));

    // 设置fp = sp
    iloc.inst("mov", PlatformArm64::regName[ARM64_FP_REG_NO], PlatformArm64::regName[ARM64_SP_REG_NO]);

    int paramsNum = inst->getOperandsNum();
    if (paramsNum) {
        for (int i = 0; i < paramsNum; ++i) {
            Value * arg = inst->getOperand(i);
            int32_t arg_regId = arg->getRegId();
            if (arg_regId != -1) {
                iloc.store_var(arg_regId, arg, ARM64_TMP_REG_NO);
            } else {
                int32_t temp_regno = simpleRegisterAllocator.Allocate();
                iloc.load_var(temp_regno, arg);
                iloc.store_var(temp_regno, arg, ARM64_TMP_REG_NO);
                simpleRegisterAllocator.free(temp_regno);
            }
        }
    }
}

void InstSelectorArm64::translate_exit(Instruction * inst)
{
    if (inst->getOperandsNum()) {
        Value * retVal = inst->getOperand(0);
        iloc.load_var(0, retVal);
    }

    auto & protectedRegStr = func->getProtectedRegStr();

    iloc.inst("add",
              PlatformArm64::regName[ARM64_FP_REG_NO],
              PlatformArm64::regName[ARM64_FP_REG_NO],
              iloc.toStr(func->getMaxDep()));
    iloc.inst("mov", "sp", PlatformArm64::regName[ARM64_FP_REG_NO]);

    if (!protectedRegStr.empty()) {
        iloc.inst("ldp", "{" + protectedRegStr + "}");
    }

    iloc.inst("ret", "lr");
}

/// @brief 赋值指令翻译成ARM64汇编
/// @param inst IR指令
void InstSelectorArm64::translate_assign(Instruction * inst)
{
    Value * result = inst->getOperand(0);
    Value * arg1 = inst->getOperand(1);

    int64_t arg1_regId = arg1->getRegId();
    int64_t result_regId = result->getRegId();

    if (arg1_regId != -1) {
        // 寄存器 => 内存
        // 寄存器 => 寄存器

        // r8 -> rs 可能用到r9
        iloc.store_var(arg1_regId, result, ARM64_TMP_REG_NO);
    } else if (result_regId != -1) {
        // 内存变量 => 寄存器

        iloc.load_var(result_regId, arg1);
    } else {
        // 内存变量 => 内存变量

        int64_t temp_regno = simpleRegisterAllocator.Allocate();

        // arg1 -> r8
        iloc.load_var(temp_regno, arg1);

        // r8 -> rs 可能用到r9
        iloc.store_var(temp_regno, result, ARM64_TMP_REG_NO);

        simpleRegisterAllocator.free(temp_regno);
    }
}

/// @brief 二元操作指令翻译成ARM64汇编
/// @param inst IR指令
/// @param operator_name 操作码
/// @param rs_reg_no 结果寄存器号
/// @param op1_reg_no 源操作数1寄存器号
/// @param op2_reg_no 源操作数2寄存器号
void InstSelectorArm64::translate_two_operator(Instruction * inst, string operator_name)
{
    Value * result = inst;
    Value * arg1 = inst->getOperand(0);
    Value * arg2 = inst->getOperand(1);

    int32_t arg1_reg_no = arg1->getRegId();
    int32_t arg2_reg_no = arg2->getRegId();
    int32_t result_reg_no = inst->getRegId();
    int32_t load_result_reg_no, load_arg1_reg_no, load_arg2_reg_no;

    // 看arg1是否是寄存器，若是则寄存器寻址，否则要load变量到寄存器中
    if (arg1_reg_no == -1) {

        // 分配一个寄存器r8
        load_arg1_reg_no = simpleRegisterAllocator.Allocate(arg1);

        // arg1 -> r8，这里可能由于偏移不满足指令的要求，需要额外分配寄存器
        iloc.load_var(load_arg1_reg_no, arg1);
    } else {
        load_arg1_reg_no = arg1_reg_no;
    }

    // 看arg2是否是寄存器，若是则寄存器寻址，否则要load变量到寄存器中
    if (arg2_reg_no == -1) {

        // 分配一个寄存器r9
        load_arg2_reg_no = simpleRegisterAllocator.Allocate(arg2);

        // arg2 -> r9
        iloc.load_var(load_arg2_reg_no, arg2);
    } else {
        load_arg2_reg_no = arg2_reg_no;
    }

    // 看结果变量是否是寄存器，若不是则需要分配一个新的寄存器来保存运算的结果
    if (result_reg_no == -1) {
        // 分配一个寄存器r10，用于暂存结果
        load_result_reg_no = simpleRegisterAllocator.Allocate(result);
    } else {
        load_result_reg_no = result_reg_no;
    }

    // r8 + r9 -> r10
    iloc.inst(operator_name,
              PlatformArm64::regName[load_result_reg_no],
              PlatformArm64::regName[load_arg1_reg_no],
              PlatformArm64::regName[load_arg2_reg_no]);

    // 结果不是寄存器，则需要把rs_reg_name保存到结果变量中
    if (result_reg_no == -1) {

        // 这里使用预留的临时寄存器，因为立即数可能过大，必须借助寄存器才可操作。

        // r10 -> result
        iloc.store_var(load_result_reg_no, result, ARM64_TMP_REG_NO);
    }

    // 释放寄存器
    simpleRegisterAllocator.free(arg1);
    simpleRegisterAllocator.free(arg2);
    simpleRegisterAllocator.free(result);
}

/// @brief 整数加法指令翻译成ARM64汇编
/// @param inst IR指令
void InstSelectorArm64::translate_add_int64(Instruction * inst)
{
    translate_two_operator(inst, "add");
}
/// @brief 浮点加法指令翻译成ARM64汇编
/// @param inst IR指令
void InstSelectorArm64::translate_add_float(Instruction * inst)
{
    Value * result = inst;
    Value * arg1 = inst->getOperand(0);
    Value * arg2 = inst->getOperand(1);

    int32_t arg1_reg_no = arg1->getRegId();
    int32_t arg2_reg_no = arg2->getRegId();
    int32_t result_reg_no = inst->getRegId();
    int32_t load_result_reg_no, load_arg1_reg_no, load_arg2_reg_no;

    // 看arg1是否是寄存器，若是则寄存器寻址，否则要load变量到寄存器中
    if (arg1_reg_no == -1) {

        // 分配一个寄存器r8
        load_arg1_reg_no = simpleRegisterAllocator.floatAllocate(arg1);

        // arg1 -> r8，这里可能由于偏移不满足指令的要求，需要额外分配寄存器
        iloc.load_var(load_arg1_reg_no, arg1);
    } else {
        load_arg1_reg_no = arg1_reg_no;
    }

    // 看arg2是否是寄存器，若是则寄存器寻址，否则要load变量到寄存器中
    if (arg2_reg_no == -1) {

        // 分配一个寄存器r9
        load_arg2_reg_no = simpleRegisterAllocator.floatAllocate(arg2);

        // arg2 -> r9
        iloc.load_var(load_arg2_reg_no, arg2);
    } else {
        load_arg2_reg_no = arg2_reg_no;
    }

    // 看结果变量是否是寄存器，若不是则需要分配一个新的寄存器来保存运算的结果
    if (result_reg_no == -1) {
        // 分配一个寄存器r10，用于暂存结果
        load_result_reg_no = simpleRegisterAllocator.floatAllocate(result);
    } else {
        load_result_reg_no = result_reg_no;
    }
    std::string op_name = "fadd";
    // r8 + r9 -> r10
    iloc.inst(op_name,
              PlatformArm64::floatregName[load_result_reg_no],
              PlatformArm64::floatregName[load_arg1_reg_no],
              PlatformArm64::floatregName[load_arg2_reg_no]);

    // 结果不是寄存器，则需要把rs_reg_name保存到结果变量中
    if (result_reg_no == -1) {

        // 这里使用预留的临时寄存器，因为立即数可能过大，必须借助寄存器才可操作。

        // r10 -> result
        iloc.store_var(load_result_reg_no, result, ARM64_TMP_REG_NO);
    }

    // 释放寄存器
    simpleRegisterAllocator.floatfree(arg1);
    simpleRegisterAllocator.floatfree(arg2);
    simpleRegisterAllocator.floatfree(result);
}

/// @brief 整数减法指令翻译成ARM64汇编
/// @param inst IR指令
void InstSelectorArm64::translate_sub_int64(Instruction * inst)
{
    translate_two_operator(inst, "sub");
}

/// @brief 浮点减法指令翻译成ARM64汇编
/// @param inst IR指令
void InstSelectorArm64::translate_sub_float(Instruction * inst)
{
    // translate_two_operator(inst, "fsub");todo
    Value * result = inst;
    Value * arg1 = inst->getOperand(0);
    Value * arg2 = inst->getOperand(1);

    int32_t arg1_reg_no = arg1->getRegId();
    int32_t arg2_reg_no = arg2->getRegId();
    int32_t result_reg_no = inst->getRegId();
    int32_t load_result_reg_no, load_arg1_reg_no, load_arg2_reg_no;

    // 看arg1是否是寄存器，若是则寄存器寻址，否则要load变量到寄存器中
    if (arg1_reg_no == -1) {

        // 分配一个寄存器r8
        load_arg1_reg_no = simpleRegisterAllocator.floatAllocate(arg1);

        // arg1 -> r8，这里可能由于偏移不满足指令的要求，需要额外分配寄存器
        iloc.load_var(load_arg1_reg_no, arg1);
    } else {
        load_arg1_reg_no = arg1_reg_no;
    }

    // 看arg2是否是寄存器，若是则寄存器寻址，否则要load变量到寄存器中
    if (arg2_reg_no == -1) {

        // 分配一个寄存器r9
        load_arg2_reg_no = simpleRegisterAllocator.floatAllocate(arg2);

        // arg2 -> r9
        iloc.load_var(load_arg2_reg_no, arg2);
    } else {
        load_arg2_reg_no = arg2_reg_no;
    }

    // 看结果变量是否是寄存器，若不是则需要分配一个新的寄存器来保存运算的结果
    if (result_reg_no == -1) {
        // 分配一个寄存器r10，用于暂存结果
        load_result_reg_no = simpleRegisterAllocator.floatAllocate(result);
    } else {
        load_result_reg_no = result_reg_no;
    }
    std::string op_name = "fsub";
    // r8 + r9 -> r10
    iloc.inst(op_name,
              PlatformArm64::floatregName[load_result_reg_no],
              PlatformArm64::floatregName[load_arg1_reg_no],
              PlatformArm64::floatregName[load_arg2_reg_no]);

    // 结果不是寄存器，则需要把rs_reg_name保存到结果变量中
    if (result_reg_no == -1) {

        // 这里使用预留的临时寄存器，因为立即数可能过大，必须借助寄存器才可操作。

        // r10 -> result
        iloc.store_var(load_result_reg_no, result, ARM64_TMP_REG_NO);
    }

    // 释放寄存器
    simpleRegisterAllocator.floatfree(arg1);
    simpleRegisterAllocator.floatfree(arg2);
    simpleRegisterAllocator.floatfree(result);
}
/// @brief 整数乘法指令翻译成ARM64汇编
/// @param inst IR指令
void InstSelectorArm64::translate_mul_int64(Instruction * inst)
{
    translate_two_operator(inst, "mul");
}

/// @brief 浮点数乘法指令翻译成ARM64汇编
/// @param inst IR指令
void InstSelectorArm64::translate_mul_float(Instruction * inst)
{
    // translate_two_operator(inst, "fmul");寄存器分配有问题
    Value * result = inst;
    Value * arg1 = inst->getOperand(0);
    Value * arg2 = inst->getOperand(1);

    int32_t arg1_reg_no = arg1->getRegId();
    int32_t arg2_reg_no = arg2->getRegId();
    int32_t result_reg_no = inst->getRegId();
    int32_t load_result_reg_no, load_arg1_reg_no, load_arg2_reg_no;

    // 看arg1是否是寄存器，若是则寄存器寻址，否则要load变量到寄存器中
    if (arg1_reg_no == -1) {

        // 分配一个寄存器r8
        load_arg1_reg_no = simpleRegisterAllocator.floatAllocate(arg1);

        // arg1 -> r8，这里可能由于偏移不满足指令的要求，需要额外分配寄存器
        iloc.load_var(load_arg1_reg_no, arg1);
    } else {
        load_arg1_reg_no = arg1_reg_no;
    }

    // 看arg2是否是寄存器，若是则寄存器寻址，否则要load变量到寄存器中
    if (arg2_reg_no == -1) {

        // 分配一个寄存器r9
        load_arg2_reg_no = simpleRegisterAllocator.floatAllocate(arg2);

        // arg2 -> r9
        iloc.load_var(load_arg2_reg_no, arg2);
    } else {
        load_arg2_reg_no = arg2_reg_no;
    }

    // 看结果变量是否是寄存器，若不是则需要分配一个新的寄存器来保存运算的结果
    if (result_reg_no == -1) {
        // 分配一个寄存器r10，用于暂存结果
        load_result_reg_no = simpleRegisterAllocator.floatAllocate(result);
    } else {
        load_result_reg_no = result_reg_no;
    }
    std::string op_name = "fmul";
    // r8 + r9 -> r10
    iloc.inst(op_name,
              PlatformArm64::floatregName[load_result_reg_no],
              PlatformArm64::floatregName[load_arg1_reg_no],
              PlatformArm64::floatregName[load_arg2_reg_no]);

    // 结果不是寄存器，则需要把rs_reg_name保存到结果变量中
    if (result_reg_no == -1) {

        // 这里使用预留的临时寄存器，因为立即数可能过大，必须借助寄存器才可操作。

        // r10 -> result
        iloc.store_var(load_result_reg_no, result, ARM64_TMP_REG_NO);
    }

    // 释放寄存器
    simpleRegisterAllocator.floatfree(arg1);
    simpleRegisterAllocator.floatfree(arg2);
    simpleRegisterAllocator.floatfree(result);
}

/// @brief 整数除法指令翻译成ARM64汇编
/// @param inst IR指令
void InstSelectorArm64::translate_div_int64(Instruction * inst)
{
    translate_two_operator(inst, "sdiv");
}

/// @brief 浮点数除法指令翻译成ARM64汇编
/// @param inst IR指令
void InstSelectorArm64::translate_div_float(Instruction * inst)
{
    // translate_two_operator(inst, "fdiv");寄存器分配有问题
    Value * result = inst;
    Value * arg1 = inst->getOperand(0);
    Value * arg2 = inst->getOperand(1);

    int32_t arg1_reg_no = arg1->getRegId();
    int32_t arg2_reg_no = arg2->getRegId();
    int32_t result_reg_no = inst->getRegId();
    int32_t load_result_reg_no, load_arg1_reg_no, load_arg2_reg_no;

    // 看arg1是否是寄存器，若是则寄存器寻址，否则要load变量到寄存器中
    if (arg1_reg_no == -1) {

        // 分配一个寄存器r8
        load_arg1_reg_no = simpleRegisterAllocator.floatAllocate(arg1);

        // arg1 -> r8，这里可能由于偏移不满足指令的要求，需要额外分配寄存器
        iloc.load_var(load_arg1_reg_no, arg1);
    } else {
        load_arg1_reg_no = arg1_reg_no;
    }

    // 看arg2是否是寄存器，若是则寄存器寻址，否则要load变量到寄存器中
    if (arg2_reg_no == -1) {

        // 分配一个寄存器r9
        load_arg2_reg_no = simpleRegisterAllocator.floatAllocate(arg2);

        // arg2 -> r9
        iloc.load_var(load_arg2_reg_no, arg2);
    } else {
        load_arg2_reg_no = arg2_reg_no;
    }

    // 看结果变量是否是寄存器，若不是则需要分配一个新的寄存器来保存运算的结果
    if (result_reg_no == -1) {
        // 分配一个寄存器r10，用于暂存结果
        load_result_reg_no = simpleRegisterAllocator.floatAllocate(result);
    } else {
        load_result_reg_no = result_reg_no;
    }
    std::string op_name = "fdiv";
    // r8 + r9 -> r10
    iloc.inst(op_name,
              PlatformArm64::floatregName[load_result_reg_no],
              PlatformArm64::floatregName[load_arg1_reg_no],
              PlatformArm64::floatregName[load_arg2_reg_no]);

    // 结果不是寄存器，则需要把rs_reg_name保存到结果变量中
    if (result_reg_no == -1) {

        // 这里使用预留的临时寄存器，因为立即数可能过大，必须借助寄存器才可操作。

        // r10 -> result
        iloc.store_var(load_result_reg_no, result, ARM64_TMP_REG_NO);
    }

    // 释放寄存器
    simpleRegisterAllocator.floatfree(arg1);
    simpleRegisterAllocator.floatfree(arg2);
    simpleRegisterAllocator.floatfree(result);
}

/// @brief 函数调用指令翻译成ARM64汇编
/// @param inst IR指令
void InstSelectorArm64::translate_call(Instruction * inst)
{
    FuncCallInstruction * callInst = dynamic_cast<FuncCallInstruction *>(inst);

    int32_t operandNum = callInst->getOperandsNum();

    if (operandNum != realArgCount) {

        // 两者不一致 也可能没有ARG指令，正常
        if (realArgCount != 0) {

            minic_log(LOG_ERROR, "ARG指令的个数与调用函数个数不一致");
        }
    }

    if (operandNum) {

        // 强制占用这几个寄存器参数传递的寄存器
        simpleRegisterAllocator.Allocate(0);
        simpleRegisterAllocator.Allocate(1);
        simpleRegisterAllocator.Allocate(2);
        simpleRegisterAllocator.Allocate(3);

        // 前四个的后面参数采用栈传递
        int esp = 0;
        for (int32_t k = 4; k < operandNum; k++) {

            auto arg = callInst->getOperand(k);

            // 新建一个内存变量，用于栈传值到形参变量中
            MemVariable * newVal = func->newMemVariable((Type *) PointerType::get(arg->getType()));
            newVal->setMemoryAddr(ARM64_FP_REG_NO, esp);
            esp += 4;

            Instruction * assignInst = new MoveInstruction(func, newVal, arg);

            // 翻译赋值指令
            translate_assign(assignInst);

            delete assignInst;
        }

        for (int32_t k = 0; k < operandNum && k < 4; k++) {

            auto arg = callInst->getOperand(k);

            // 检查实参的类型是否是临时变量。
            // 如果是临时变量，该变量可更改为寄存器变量即可，或者设置寄存器号
            // 如果不是，则必须开辟一个寄存器变量，然后赋值即可

            Instruction * assignInst = new MoveInstruction(func, PlatformArm64::intRegVal[k], arg);

            // 翻译赋值指令
            translate_assign(assignInst);

            delete assignInst;
        }
    }

    iloc.call_fun(callInst->getName());

    if (operandNum) {
        simpleRegisterAllocator.free(0);
        simpleRegisterAllocator.free(1);
        simpleRegisterAllocator.free(2);
        simpleRegisterAllocator.free(3);
    }

    // 赋值指令
    if (callInst->hasResultValue()) {

        // 新建一个赋值操作
        Instruction * assignInst = new MoveInstruction(func, callInst, PlatformArm64::intRegVal[0]);

        // 翻译赋值指令
        translate_assign(assignInst);

        delete assignInst;
    }

    // 函数调用后清零，使得下次可正常统计
    realArgCount = 0;
}

///
/// @brief 实参指令翻译成ARM64汇编
/// @param inst
///
void InstSelectorArm64::translate_arg(Instruction * inst)
{
    // 翻译之前必须确保源操作数要么是寄存器，要么是内存，否则出错。
    Value * src = inst->getOperand(0);

    // 当前统计的ARG指令个数
    int32_t regId = src->getRegId();

    if (realArgCount < 4) {
        // 前四个参数
        if (regId != -1) {
            if (regId != realArgCount) {
                // 肯定寄存器分配有误
                minic_log(LOG_ERROR, "第%d个ARG指令对象寄存器分配有误: %d", argCount + 1, regId);
            }
        } else {
            minic_log(LOG_ERROR, "第%d个ARG指令对象不是寄存器", argCount + 1);
        }
    } else {
        // 必须是内存分配，若不是则出错
        int32_t baseRegId;
        bool result = src->getMemoryAddr(&baseRegId);
        if ((!result) || (baseRegId != ARM64_FP_REG_NO)) {

            minic_log(LOG_ERROR, "第%d个ARG指令对象不是SP寄存器寻址", argCount + 1);
        }
    }

    realArgCount++;
}

///
/// @brief laod指令翻译成ARM64汇编
/// @param inst
///
void InstSelectorArm64::translate_load(Instruction * inst)
{
    Value * result_val = inst; // 加载操作的结果将存储在这个Value对应的位置（通常是寄存器）
    Value * address_operand_val = inst->getOperand(0); // 这个Value持有要加载数据的内存地址（它本身是一个指针）

    int32_t dest_reg_no; // 目标寄存器号

    if (result_val->getRegId() != -1) {
        dest_reg_no = result_val->getRegId(); // 使用已分配的目标寄存器
    } else {
        // 为LOAD指令的结果分配新寄存器。
        dest_reg_no = simpleRegisterAllocator.Allocate(result_val);
    }

    int32_t addr_holder_reg_no;       // 存储实际内存地址的寄存器编号
    bool addr_holder_is_temp = false; // 标记地址寄存器是否为临时分配

    if (address_operand_val->getRegId() != -1) {
        addr_holder_reg_no = address_operand_val->getRegId(); // 直接使用现有地址寄存器
    } else {
        // 分配临时寄存器并加载地址值
        addr_holder_reg_no = simpleRegisterAllocator.Allocate();
        addr_holder_is_temp = true;
        iloc.load_var(addr_holder_reg_no, address_operand_val);
    }

    Type * loaded_data_type = result_val->getType(); // 获取加载数据的类型
    std::string arm_load_inst = "ldr";               // (ldr xDest, [xAddr])

    // 根据要加载数据的类型，确定具体的LDR系列指令。
    // 注意: PlatformArm64::regName 需要能够正确地将 dest_reg_no 映射到 X, W, S, 或 D 寄存器名。
    // 这通常意味着 simpleRegisterAllocator 必须能够从不同的寄存器池分配，
    // 或者使用一种 PlatformArm64::regName 可以解释的编号方案。
    // 此处假设 simpleRegisterAllocator 和 PlatformArm64::regName 能够处理这些。

    if (loaded_data_type->isIntegerType()) {
        IntegerType * int_type = static_cast<IntegerType *>(loaded_data_type);
        switch (int_type->getBitWidth()) {
            case 8:
                arm_load_inst = "ldrsb"; // LDRSB Xd, [Xn] (加载字节并符号扩展到64位)
                break;
            case 16:
                arm_load_inst = "ldrsh"; // LDRSH Xd, [Xn] (加载半字并符号扩展到64位)
                break;
            case 32:
                // LDRSW Xd, [Xn] 加载一个32位字并将其符号扩展到64位存入X寄存器。
                // 如果是加载到W寄存器 (目标也是32位)，则会用 "ldr Wd, [Xn]"。
                // 考虑到其他操作多为int64，LDRSW到X寄存器是常见选择。
                arm_load_inst = "ldrsw";
                break;
            case 64:
                arm_load_inst = "ldr"; // 标准64位加载 LDR Xd, [Xn]
                break;
            default:
                minic_log(LOG_ERROR, "不支持的LOAD整数位宽: %d", int_type->getBitWidth());
                if (addr_holder_is_temp)
                    simpleRegisterAllocator.free(addr_holder_reg_no);
                simpleRegisterAllocator.free(result_val); // 如果是为result新分配的，也考虑释放
                simpleRegisterAllocator.free(address_operand_val);
                return;
        }
        // 对于整数类型，dest_reg_no 应该引用一个X寄存器（通用寄存器）。
        // LDRSB, LDRSH, LDRSW 指令会正确地加载数据并符号扩展到目标X寄存器。
        // 如果要加载到32位的W寄存器，则使用 LDR Wd, [Xn]。

    } else if (loaded_data_type->isFloatType()) {
        // LDR St, [Xn] (加载单精度浮点数)
        arm_load_inst = "ldr";
        // dest_reg_no 必须是从浮点寄存器池分配的 (S 寄存器)
        // PlatformArm64::regName[dest_reg_no] 应该生成 "s<n>" 这样的名字
    } else if (loaded_data_type->isPointerType()) {
        arm_load_inst = "ldr"; // 指针在ARM64上是64位的，使用通用加载
        // dest_reg_no 应该引用一个X寄存器
    } else {
        minic_log(LOG_ERROR, "不支持的LOAD操作类型: %s", loaded_data_type->toString().c_str());
        if (addr_holder_is_temp)
            simpleRegisterAllocator.free(addr_holder_reg_no);
        simpleRegisterAllocator.free(result_val);
        simpleRegisterAllocator.free(address_operand_val);
        return;
    }

    // 发出实际的加载指令。
    // 示例：LDRSW X0, [X1] (从X1寄存器中的地址加载一个有符号字到X0寄存器)
    //    LDR  S0, [X1] (从X1寄存器中的地址加载一个单精度浮点数到S0寄存器)
    iloc.inst(arm_load_inst,
              PlatformArm64::regName[dest_reg_no],                     // 目标寄存器
              "[" + PlatformArm64::regName[addr_holder_reg_no] + "]"); // 源地址，在寄存器中

    // 如果为持有地址分配了临时寄存器，现在释放它
    if (addr_holder_is_temp) {
        simpleRegisterAllocator.free(addr_holder_reg_no);
    }

    // 为寄存器分配器的活跃性分析/释放逻辑，标记操作数已被使用。
    // result_val (即inst) 现在的值在 dest_reg_no 中是活跃的。
    // address_operand_val 作为地址来源，其在此指令中的使用已经结束。
    simpleRegisterAllocator.free(address_operand_val);
    // result_val (即inst) 的释放在你的代码模式中似乎是在其生命周期结束时，
    // 或者如 translate_two_operator 中那样，在指令翻译完成后立即调用 free。
    // 这里遵循你已有的模式。
    simpleRegisterAllocator.free(result_val);
}