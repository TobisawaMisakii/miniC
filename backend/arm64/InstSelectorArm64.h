///
/// @file InstSelectorArm64.h
/// @brief 指令选择器-ARM32
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
#pragma once

#include <map>
#include <vector>

#include "Function.h"
#include "ILocArm64.h"
#include "Instruction.h"
#include "PlatformArm64.h"
#include "SimpleRegisterAllocator.h"
#include "RegVariable.h"

using namespace std;

/// @brief 指令选择器-ARM64
class InstSelectorArm64 {

private:
    /// @brief 所有的IR指令
    std::vector<Instruction *> & ir;

    /// @brief 指令变换
    ILocArm64 & iloc;

    /// @brief 要处理的函数
    Function * func;

protected:
    /// @brief 指令翻译成ARM64汇编
    /// @param inst IR指令
    void translate(Instruction * inst);

    /// @brief NOP翻译成ARM32汇编
    /// @param inst IR指令
    void translate_nop(Instruction * inst);

    /// @brief 函数入口指令翻译成ARM32汇编
    /// @param inst IR指令
    void translate_entry(Instruction * inst);

    /// @brief 函数出口指令翻译成ARM32汇编
    /// @param inst IR指令
    void translate_exit(Instruction * inst);

    /// @brief 赋值指令翻译成ARM32汇编
    /// @param inst IR指令
    void translate_assign(Instruction * inst);

    /// @brief Label指令指令翻译成ARM32汇编
    /// @param inst IR指令
    void translate_label(Instruction * inst);

    /// @brief goto指令指令翻译成ARM32汇编
    /// @param inst IR指令
    void translate_goto(Instruction * inst);

    /// @brief 有条件分支指令翻译成ARM32汇编
    /// @param inst IR指令
    // void translate_goto_if_zero(Instruction * inst);

    /// @brief 整数加法指令翻译成ARM32汇编
    /// @param inst IR指令
    void translate_add_int64(Instruction * inst);

    /// @brief 整数加法指令翻译成ARM32汇编
    /// @param inst IR指令
    void translate_add_float(Instruction * inst);

    /// @brief 整数减法指令翻译成ARM32汇编
    /// @param inst IR指令
    void translate_sub_int64(Instruction * inst);

    /// @brief 浮点数减法指令翻译成ARM32汇编
    /// @param inst IR指令
    void translate_sub_float(Instruction * inst);

    /// @brief 整数乘法指令翻译成ARM64汇编
    /// @param inst IR指令
    void translate_mul_int64(Instruction * inst);

    /// @brief 浮点数乘法指令翻译成ARM64汇编
    /// @param inst IR指令
    void translate_mul_float(Instruction * inst);

    /// @brief 整数除法指令翻译成ARM64汇编
    /// @param inst IR指令
    void translate_div_int64(Instruction * inst);

    /// @brief 浮点数除法指令翻译成ARM64汇编
    /// @param inst IR指令
    void translate_div_float(Instruction * inst);

    /// @brief 整数取模指令翻译成ARM64汇编
    /// @param inst IR指令
    void translate_mod_int64(Instruction * inst);

    /// @brief 浮点取模指令翻译成ARM64汇编
    /// @param inst IR指令
    void translate_mod_float(Instruction * inst);

    /// @brief 二元操作指令翻译成ARM32汇编
    /// @param inst IR指令
    /// @param operator_name 操作码
    void translate_two_operator(Instruction * inst, string operator_name);

    /// @brief 函数调用指令翻译成ARM32汇编
    /// @param inst IR指令
    void translate_call(Instruction * inst);

    /// @brief 实参指令翻译成ARM32汇编
    /// @param inst
    void translate_arg(Instruction * inst);

    /// @brief load指令翻译成ARM32汇编
    /// @param inst
    void translate_load(Instruction * inst);

    /// @brief store指令翻译成ARM32汇编
    /// @param inst
    void translate_store(Instruction * inst);

    /// @brief zxet零扩展指令指令翻译成ARM32汇编
    /// @param inst
    ///
    void translate_zext(Instruction * inst);

    /// @brief sxet符号扩展指令指令翻译成ARM32汇编
    /// @param inst
    void translate_sext(Instruction * inst);

    /// @brief i32转浮点指令翻译成ARM32汇编
    /// @param inst
    void translate_sitofp(Instruction * inst);

    /// @brief 浮点转i32指令翻译成ARM32汇编
    /// @param inst
    void translate_fptosi(Instruction * inst);

    /// @brief 比较指令翻译成ARM32汇编
    /// @param inst
    void translate_cmp_int64(Instruction * inst, IRInstOperator op);
    const char * getA64Cond(IRInstOperator op);
    void translate_lt_int64(Instruction * inst);
    void translate_le_int64(Instruction * inst);
    void translate_gt_int64(Instruction * inst);
    void translate_ge_int64(Instruction * inst);
    void translate_eq_int64(Instruction * inst);
    void translate_ne_int64(Instruction * inst);

    /// @brief 输出IR指令
    void outputIRInstruction(Instruction * inst);

    /// @brief IR翻译动作函数原型
    typedef void (InstSelectorArm64::*translate_handler)(Instruction *);

    /// @brief IR动作处理函数清单
    map<IRInstOperator, translate_handler> translator_handlers;

    /// @brief 简单的朴素寄存器分配方法
    SimpleRegisterAllocator & simpleRegisterAllocator;

    /// @brief 函数实参累计
    int32_t argCount = 0;

    /// @brief 累计的实参个数
    int32_t realArgCount = 0;

public:
    /// @brief 构造函数
    /// @param _irCode IR指令
    /// @param _func 函数
    /// @param _iloc 后端指令
public:
    InstSelectorArm64(std::vector<Instruction *> & _irCode,
                      ILocArm64 & _iloc,
                      Function * _func,
                      SimpleRegisterAllocator & allocator);
    ~InstSelectorArm64();

    /// @brief 指令选择
    void run();
};