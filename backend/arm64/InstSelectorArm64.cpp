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
#include "BranchConditional.h"
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
    //translator_handlers[IRInstOperator::IRINST_OP_GOTO_IF_ZERO] = &InstSelectorArm64::translate_goto_if_zero;

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
    translator_handlers[IRInstOperator::IRINST_OP_STORE] = &InstSelectorArm64::translate_store;
    // mod
    translator_handlers[IRInstOperator::IRINST_OP_MOD_I] = &InstSelectorArm64::translate_mod_int64;
    translator_handlers[IRInstOperator::IRINST_OP_MOD_F] = &InstSelectorArm64::translate_mod_float;
    // IRINST_OP_ZEXT,       // 零扩展指令
    //     IRINST_OP_SEXT,   // 符号扩展指令
    //     IRINST_OP_SITOFP, // i32转浮点指令
    //     IRINST_OP_FPTOSI,
    // 数据类型转换
    // 零扩展指令
    translator_handlers[IRInstOperator::IRINST_OP_ZEXT] = &InstSelectorArm64::translate_zext;
    // 符号扩展指令
    translator_handlers[IRInstOperator::IRINST_OP_SEXT] = &InstSelectorArm64::translate_sext;
    // i32转浮点指令
    translator_handlers[IRInstOperator::IRINST_OP_SITOFP] = &InstSelectorArm64::translate_sitofp;
    // 浮点转i32指令
    translator_handlers[IRInstOperator::IRINST_OP_FPTOSI] = &InstSelectorArm64::translate_fptosi;
    // 比较指令
    translator_handlers[IRInstOperator::IRINST_OP_ICMP_LT] = &InstSelectorArm64::translate_lt_int64;
    translator_handlers[IRInstOperator::IRINST_OP_ICMP_LE] = &InstSelectorArm64::translate_le_int64;
    translator_handlers[IRInstOperator::IRINST_OP_ICMP_GT] = &InstSelectorArm64::translate_gt_int64;
    translator_handlers[IRInstOperator::IRINST_OP_ICMP_GE] = &InstSelectorArm64::translate_ge_int64;
    translator_handlers[IRInstOperator::IRINST_OP_ICMP_EQ] = &InstSelectorArm64::translate_eq_int64;
    translator_handlers[IRInstOperator::IRINST_OP_ICMP_NE] = &InstSelectorArm64::translate_ne_int64;
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
    auto & protectedRegNo = func->getProtectedReg();

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

    iloc.inst("mov", PlatformArm64::regName[ARM64_SP_REG_NO], PlatformArm64::regName[ARM64_FP_REG_NO]);
    int res_size = frame_size - save_size;
    if (res_size <= 4095) {
        iloc.inst("add",
                  PlatformArm64::regName[ARM64_SP_REG_NO],
                  PlatformArm64::regName[ARM64_SP_REG_NO],
                  iloc.toStr(res_size, false));
    } else {
        auto temp_regno = simpleRegisterAllocator.Allocate();
        // iloc.load_imm(temp_regno, res_size);
        iloc.inst("add",
                  PlatformArm64::regName[ARM64_SP_REG_NO],
                  PlatformArm64::regName[ARM64_SP_REG_NO],
                  PlatformArm64::regName[temp_regno]);
        simpleRegisterAllocator.free(temp_regno);
    }
    // 恢复fp/lr并回收栈帧
    if (protectedRegNo.size() == 2) {
        iloc.inst("ldp",
                  PlatformArm64::regName[protectedRegNo[0]],
                  PlatformArm64::regName[protectedRegNo[1]],
                  "[sp], #" + iloc.toStr(save_size, false));
    } else if (protectedRegNo.size() == 1) {
        iloc.inst("ldr", PlatformArm64::regName[protectedRegNo[0]], "[sp], #" + iloc.toStr(save_size, false));
    }
    iloc.inst("ret", "");
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
    // Value * funcVal = inst;
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
/// @brief load指令翻译成ARM64汇编
/// @param inst
///
void InstSelectorArm64::translate_load(Instruction * inst)
{
    // IR 指令语义： result = LOAD address
    // result 是指令本身代表的Value
    // address 是第一个操作数
    Value * result = inst;
    Value * address = inst->getOperand(0);

    int32_t result_reg_no, address_reg_no;

    // --- 步骤 1: 将地址加载到一个寄存器中 ---
    // 检查地址是否已在寄存器中
    if (address->getRegId() != -1) {
        address_reg_no = address->getRegId();
        iloc.store_var(address_reg_no, result, ARM64_TMP_REG_NO);
    } else if (result->getRegId() != -1) {
        // 如果地址不在寄存器中（例如，它是一个存储在栈上的指针变量），
        // 则分配一个临时寄存器，并使用 iloc.load_var 将地址加载进来。
        result_reg_no = simpleRegisterAllocator.Allocate();
        iloc.load_var(result_reg_no, address);
    } else {
        // 如果没有，分配一个新的临时寄存器来存放加载的数据
        int32_t temp_regno = simpleRegisterAllocator.Allocate();
        int32_t result_regno = simpleRegisterAllocator.Allocate();
        iloc.load_var(temp_regno, address);
        iloc.store_var(temp_regno, result, ARM64_TMP_REG_NO);
        simpleRegisterAllocator.free(temp_regno);
        simpleRegisterAllocator.free(result_regno);
    }

    // --- 步骤 3: 生成 LDR 指令 ---
    // 生成 "ldr <结果寄存器>, [<地址寄存器>]"
    // 这条指令从 address_reg_no 指向的内存地址加载数据到 result_reg_no
}

/// @brief store指令翻译成ARM64汇编
/// @param inst IR指令
void InstSelectorArm64::translate_store(Instruction * inst)
{
    // IR 指令语义： STORE value, address
    // value 是第一个操作数
    // address 可能是立即数
    Value * value_to_store = inst->getOperand(0);
    Value * address = inst->getOperand(1); // 可能是

    int32_t value_reg_no, address_reg_no;

    if (value_to_store->getRegId() != -1) {
        value_reg_no = value_to_store->getRegId();
        iloc.store_var(value_reg_no, address, ARM64_TMP_REG_NO);
    } else if (address->getRegId() != -1) {
        address_reg_no = address->getRegId();

        iloc.load_var(address_reg_no, address);
    } else {
        int32_t temp_regno = simpleRegisterAllocator.Allocate();
        int32_t result_regno = simpleRegisterAllocator.Allocate();
        iloc.load_var(temp_regno, address);
        iloc.store_var(temp_regno, value_to_store, ARM64_TMP_REG_NO);
        simpleRegisterAllocator.free(temp_regno);
        simpleRegisterAllocator.free(result_regno);
    }
}

void InstSelectorArm64::translate_mod_int64(Instruction * inst)
{
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
    Value * dst = inst;
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    int32_t tmp_div = simpleRegisterAllocator.Allocate();
    int32_t tmp_mul = simpleRegisterAllocator.Allocate();
    if (lhs_reg == -1) {
        lhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(lhs_reg, lhs);
    }
    if (rhs_reg == -1) {
        rhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(rhs_reg, rhs);
    }
    if (dst_reg == -1)
        dst_reg = simpleRegisterAllocator.Allocate();
    iloc.inst("sdiv",
              PlatformArm64::regName[tmp_div],
              PlatformArm64::regName[lhs_reg],
              PlatformArm64::regName[rhs_reg]);
    iloc.inst("mul", PlatformArm64::regName[tmp_mul], PlatformArm64::regName[tmp_div], PlatformArm64::regName[rhs_reg]);
    iloc.inst("sub", PlatformArm64::regName[dst_reg], PlatformArm64::regName[lhs_reg], PlatformArm64::regName[tmp_mul]);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    simpleRegisterAllocator.free(tmp_div);
    simpleRegisterAllocator.free(tmp_mul);
    if (lhs->getRegId() == -1)
        simpleRegisterAllocator.free(lhs_reg);
    if (rhs->getRegId() == -1)
        simpleRegisterAllocator.free(rhs_reg);
    if (dst->getRegId() == -1)
        simpleRegisterAllocator.free(dst_reg);
}

void InstSelectorArm64::translate_mod_float(Instruction * inst)
{
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
    Value * dst = inst;
    int32_t dst_reg = dst->getRegId();
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    int32_t tmp_div = simpleRegisterAllocator.Allocate();
    int32_t tmp_mul = simpleRegisterAllocator.Allocate();
    if (lhs_reg == -1) {
        lhs_reg = simpleRegisterAllocator.floatAllocate();
        iloc.load_var(lhs_reg, lhs);
    }
    if (rhs_reg == -1) {
        rhs_reg = simpleRegisterAllocator.floatAllocate();
        iloc.load_var(rhs_reg, rhs);
    }
    if (dst_reg == -1)
        dst_reg = simpleRegisterAllocator.floatAllocate();
    iloc.inst("fdiv",
              PlatformArm64::floatregName[tmp_div],
              PlatformArm64::floatregName[lhs_reg],
              PlatformArm64::floatregName[rhs_reg]);
    iloc.inst("fmul",
              PlatformArm64::floatregName[tmp_mul],
              PlatformArm64::regName[tmp_div],
              PlatformArm64::regName[rhs_reg]);
    iloc.inst("fsub",
              PlatformArm64::regName[dst_reg],
              PlatformArm64::floatregName[lhs_reg],
              PlatformArm64::floatregName[tmp_mul]);
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);
    simpleRegisterAllocator.floatfree(tmp_div);
    simpleRegisterAllocator.floatfree(tmp_mul);
    if (lhs->getRegId() == -1)
        simpleRegisterAllocator.floatfree(lhs_reg);
    if (rhs->getRegId() == -1)
        simpleRegisterAllocator.floatfree(rhs_reg);
    if (dst->getRegId() == -1)
        simpleRegisterAllocator.floatfree(dst_reg);
}

void InstSelectorArm64::translate_zext(Instruction * inst)
{
    // 使用UXTW指令进行零扩展
    Value * result = inst;
    Value * arg = inst->getOperand(0);
    int32_t arg_reg_no = arg->getRegId();
    int32_t result_reg_no = result->getRegId();
    if (arg_reg_no == -1) {
        arg_reg_no = simpleRegisterAllocator.Allocate(arg);
        iloc.load_var(arg_reg_no, arg);
    }
    if (result_reg_no == -1) {
        result_reg_no = simpleRegisterAllocator.Allocate(result);
    }
    iloc.inst("uxtw", PlatformArm64::regName[result_reg_no], PlatformArm64::regName[arg_reg_no]);
    iloc.store_var(result_reg_no, result, ARM64_TMP_REG_NO);
    simpleRegisterAllocator.free(arg);
    simpleRegisterAllocator.free(result);
}

void InstSelectorArm64::translate_sext(Instruction * inst)
{
    // 使用SXTW指令进行符号扩展
    Value * result = inst;
    Value * arg = inst->getOperand(0);
    int32_t arg_reg_no = arg->getRegId();
    int32_t result_reg_no = result->getRegId();
    if (arg_reg_no == -1) {
        arg_reg_no = simpleRegisterAllocator.Allocate(arg);
        iloc.load_var(arg_reg_no, arg);
    }
    if (result_reg_no == -1) {
        result_reg_no = simpleRegisterAllocator.Allocate(result);
    }
    iloc.inst("sxtw", PlatformArm64::regName[result_reg_no], PlatformArm64::regName[arg_reg_no]);
    iloc.store_var(result_reg_no, result, ARM64_TMP_REG_NO);
    simpleRegisterAllocator.free(arg);
    simpleRegisterAllocator.free(result);
}

void InstSelectorArm64::translate_sitofp(Instruction * inst)
{
    // 使用SCVTF指令将32位整数转换为浮点数
    Value * result = inst;
    Value * arg = inst->getOperand(0);
    int32_t arg_reg_no = arg->getRegId();
    int32_t result_reg_no = result->getRegId();
    if (arg_reg_no == -1) {
        arg_reg_no = simpleRegisterAllocator.Allocate(arg);
        iloc.load_var(arg_reg_no, arg);
    }
    if (result_reg_no == -1) {
        result_reg_no = simpleRegisterAllocator.floatAllocate(result);
    }
    iloc.inst("scvtf", PlatformArm64::floatregName[result_reg_no], PlatformArm64::regName[arg_reg_no]);
    iloc.store_var(result_reg_no, result, ARM64_TMP_REG_NO);
    simpleRegisterAllocator.free(arg);
    simpleRegisterAllocator.floatfree(result);
}

void InstSelectorArm64::translate_fptosi(Instruction * inst)
{
    // 使用FCVTZS指令将浮点数转换为32位整数
    Value * result = inst;
    Value * arg = inst->getOperand(0);
    int32_t arg_reg_no = arg->getRegId();
    int32_t result_reg_no = result->getRegId();
    if (arg_reg_no == -1) {
        arg_reg_no = simpleRegisterAllocator.floatAllocate(arg);
        iloc.load_var(arg_reg_no, arg);
    }
    if (result_reg_no == -1) {
        result_reg_no = simpleRegisterAllocator.Allocate(result);
    }
    iloc.inst("fcvtzs", PlatformArm64::regName[result_reg_no], PlatformArm64::floatregName[arg_reg_no]);
    iloc.store_var(result_reg_no, result, ARM64_TMP_REG_NO);
    simpleRegisterAllocator.free(arg);
    simpleRegisterAllocator.free(result);
}

const char * InstSelectorArm64::getA64Cond(IRInstOperator op)
{
    switch (op) {
        case IRInstOperator::IRINST_OP_ICMP_EQ:
            return "eq"; // 等于 (Equal)
        case IRInstOperator::IRINST_OP_ICMP_NE:
            return "ne"; // 不等于 (Not Equal)
        case IRInstOperator::IRINST_OP_ICMP_GT:
            return "gt"; // 有符号大于 (Greater Than)
        case IRInstOperator::IRINST_OP_ICMP_GE:
            return "ge"; // 有符号大于等于 (Greater or Equal)
        case IRInstOperator::IRINST_OP_ICMP_LT:
            return "lt"; // 有符号小于 (Less Than)
        case IRInstOperator::IRINST_OP_ICMP_LE:
            return "le"; // 有符号小于等于 (Less or Equal)
        default:
            return "al";
    }
}

void InstSelectorArm64::translate_cmp_int64(Instruction * inst, IRInstOperator op)
{
    // 1. 从IR指令中获取操作数
    // lhs: 左操作数 (例如 a > b 中的 'a')
    // rhs: 右操作数 (例如 a > b 中的 'b')
    // dst: 目标操作数，用于存放比较结果(布尔值0或1)，通常是指令自身
    Value * lhs = inst->getOperand(0);
    Value * rhs = inst->getOperand(1);
    Value * dst = inst;

    // 2. 为操作数分配或获取寄存器
    // 检查每个操作数是否已经分配了物理寄存器。
    // 如果 getRegId() 返回-1，意味着该值当前存储在内存（如栈上）中，
    // 需要为它临时分配一个寄存器，并从内存加载数据。
    int32_t lhs_reg = lhs->getRegId();
    int32_t rhs_reg = rhs->getRegId();
    int32_t dst_reg = dst->getRegId();

    // 记录寄存器是否为本次调用临时分配的，以便在最后释放
    bool lhs_reg_is_temp = false;
    if (lhs_reg == -1) {
        lhs_reg = simpleRegisterAllocator.Allocate(); // 分配一个空闲寄存器
        iloc.load_var(lhs_reg, lhs);                  // 生成指令：从内存加载变量到该寄存器
        lhs_reg_is_temp = true;
    }

    bool rhs_reg_is_temp = false;
    if (rhs_reg == -1) {
        rhs_reg = simpleRegisterAllocator.Allocate();
        iloc.load_var(rhs_reg, rhs);
        rhs_reg_is_temp = true;
    }

    // 目标寄存器也需要分配，用于存放CSET的结果
    bool dst_reg_is_temp = false;
    if (dst_reg == -1) {
        dst_reg = simpleRegisterAllocator.Allocate();
        dst_reg_is_temp = true;
    }

    // 3. 生成核心汇编指令
    // 第一步：使用 CMP 指令比较两个寄存器中的值，这会更新条件标志位
    iloc.inst("cmp", PlatformArm64::regName[lhs_reg], PlatformArm64::regName[rhs_reg]);

    // 第二步：使用 CSET 指令根据条件标志位，将目标寄存器的值设置为 0 或 1
    // getA64Cond(op) 会返回 "gt", "le" 等字符串
    iloc.inst("cset", PlatformArm64::regName[dst_reg], getA64Cond(op));

    // 4. 将结果写回内存
    // 将目标寄存器中的结果 (0或1) 存回其在栈上对应的位置
    // ARM64_TMP_REG_NO 是一个预留的临时寄存器，可能用于辅助store操作（例如计算地址）
    iloc.store_var(dst_reg, dst, ARM64_TMP_REG_NO);

    // 5. 释放临时分配的寄存器
    // 如果某个操作数的寄存器是为本次翻译临时分配的，现在必须释放它，
    // 以便其他指令可以复用。
    if (lhs_reg_is_temp) {
        simpleRegisterAllocator.free(lhs_reg);
    }
    if (rhs_reg_is_temp) {
        simpleRegisterAllocator.free(rhs_reg);
    }
    if (dst_reg_is_temp) {
        simpleRegisterAllocator.free(dst_reg);
    }
}

// 翻译 大于(>) 指令
void InstSelectorArm64::translate_gt_int64(Instruction * inst)
{
    translate_cmp_int64(inst, IRInstOperator::IRINST_OP_ICMP_GT);
}

// 翻译 小于(<) 指令
void InstSelectorArm64::translate_lt_int64(Instruction * inst)
{
    translate_cmp_int64(inst, IRInstOperator::IRINST_OP_ICMP_LT);
}

// 翻译 小于等于(<=) 指令
void InstSelectorArm64::translate_le_int64(Instruction * inst)
{
    translate_cmp_int64(inst, IRInstOperator::IRINST_OP_ICMP_LE);
}

// 翻译 大于等于(>=) 指令
void InstSelectorArm64::translate_ge_int64(Instruction * inst)
{
    translate_cmp_int64(inst, IRInstOperator::IRINST_OP_ICMP_GE);
}

// 翻译 等于(==) 指令
void InstSelectorArm64::translate_eq_int64(Instruction * inst)
{
    translate_cmp_int64(inst, IRInstOperator::IRINST_OP_ICMP_EQ);
}

// 翻译 不等于(!=) 指令
void InstSelectorArm64::translate_ne_int64(Instruction * inst)
{
    translate_cmp_int64(inst, IRInstOperator::IRINST_OP_ICMP_NE);
}