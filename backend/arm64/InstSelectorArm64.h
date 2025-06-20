///
/// @file InstSelectorArm64.h
/// @brief ָ��ѡ����-ARM32
/// @author zenglj (zenglj@live.com)
/// @version 1.0
/// @date 2024-11-21
///
/// @copyright Copyright (c) 2024
///
/// @par �޸���־:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-11-21 <td>1.0     <td>zenglj  <td>����
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

/// @brief ָ��ѡ����-ARM64
class InstSelectorArm64 {

private:
    /// @brief ���е�IRָ��
    std::vector<Instruction *> & ir;

    /// @brief ָ��任
    ILocArm64 & iloc;

    /// @brief Ҫ����ĺ���
    Function * func;

protected:
    /// @brief ָ����ARM64���
    /// @param inst IRָ��
    void translate(Instruction * inst);

    /// @brief NOP�����ARM32���
    /// @param inst IRָ��
    void translate_nop(Instruction * inst);

    /// @brief �������ָ����ARM32���
    /// @param inst IRָ��
    void translate_entry(Instruction * inst);

    /// @brief ��������ָ����ARM32���
    /// @param inst IRָ��
    void translate_exit(Instruction * inst);

    /// @brief ��ֵָ����ARM32���
    /// @param inst IRָ��
    void translate_assign(Instruction * inst);

    /// @brief Labelָ��ָ����ARM32���
    /// @param inst IRָ��
    void translate_label(Instruction * inst);

    /// @brief gotoָ��ָ����ARM32���
    /// @param inst IRָ��
    void translate_goto(Instruction * inst);

    /// @brief ��������ָ֧����ARM32���
    /// @param inst IRָ��
    // void translate_goto_if_zero(Instruction * inst);

    /// @brief �����ӷ�ָ����ARM32���
    /// @param inst IRָ��
    void translate_add_int64(Instruction * inst);

    /// @brief �����ӷ�ָ����ARM32���
    /// @param inst IRָ��
    void translate_add_float(Instruction * inst);

    /// @brief ��������ָ����ARM32���
    /// @param inst IRָ��
    void translate_sub_int64(Instruction * inst);

    /// @brief ����������ָ����ARM32���
    /// @param inst IRָ��
    void translate_sub_float(Instruction * inst);

    /// @brief �����˷�ָ����ARM64���
    /// @param inst IRָ��
    void translate_mul_int64(Instruction * inst);

    /// @brief �������˷�ָ����ARM64���
    /// @param inst IRָ��
    void translate_mul_float(Instruction * inst);

    /// @brief ��������ָ����ARM64���
    /// @param inst IRָ��
    void translate_div_int64(Instruction * inst);

    /// @brief ����������ָ����ARM64���
    /// @param inst IRָ��
    void translate_div_float(Instruction * inst);

    /// @brief ����ȡģָ����ARM64���
    /// @param inst IRָ��
    void translate_mod_int64(Instruction * inst);

    /// @brief ����ȡģָ����ARM64���
    /// @param inst IRָ��
    void translate_mod_float(Instruction * inst);

    /// @brief ��Ԫ����ָ����ARM32���
    /// @param inst IRָ��
    /// @param operator_name ������
    void translate_two_operator(Instruction * inst, string operator_name);

    /// @brief ��������ָ����ARM32���
    /// @param inst IRָ��
    void translate_call(Instruction * inst);

    /// @brief ʵ��ָ����ARM32���
    /// @param inst
    void translate_arg(Instruction * inst);

    /// @brief loadָ����ARM32���
    /// @param inst
    void translate_load(Instruction * inst);

    /// @brief storeָ����ARM32���
    /// @param inst
    void translate_store(Instruction * inst);

    /// @brief zxet����չָ��ָ����ARM32���
    /// @param inst
    ///
    void translate_zext(Instruction * inst);

    /// @brief sxet������չָ��ָ����ARM32���
    /// @param inst
    void translate_sext(Instruction * inst);

    /// @brief i32ת����ָ����ARM32���
    /// @param inst
    void translate_sitofp(Instruction * inst);

    /// @brief ����תi32ָ����ARM32���
    /// @param inst
    void translate_fptosi(Instruction * inst);

    /// @brief �Ƚ�ָ����ARM32���
    /// @param inst
    void translate_cmp_int64(Instruction * inst, IRInstOperator op);
    const char * getA64Cond(IRInstOperator op);
    void translate_lt_int64(Instruction * inst);
    void translate_le_int64(Instruction * inst);
    void translate_gt_int64(Instruction * inst);
    void translate_ge_int64(Instruction * inst);
    void translate_eq_int64(Instruction * inst);
    void translate_ne_int64(Instruction * inst);

    /// @brief ���IRָ��
    void outputIRInstruction(Instruction * inst);

    /// @brief IR���붯������ԭ��
    typedef void (InstSelectorArm64::*translate_handler)(Instruction *);

    /// @brief IR�����������嵥
    map<IRInstOperator, translate_handler> translator_handlers;

    /// @brief �򵥵����ؼĴ������䷽��
    SimpleRegisterAllocator & simpleRegisterAllocator;

    /// @brief ����ʵ���ۼ�
    int32_t argCount = 0;

    /// @brief �ۼƵ�ʵ�θ���
    int32_t realArgCount = 0;

public:
    /// @brief ���캯��
    /// @param _irCode IRָ��
    /// @param _func ����
    /// @param _iloc ���ָ��
public:
    InstSelectorArm64(std::vector<Instruction *> & _irCode,
                      ILocArm64 & _iloc,
                      Function * _func,
                      SimpleRegisterAllocator & allocator);
    ~InstSelectorArm64();

    /// @brief ָ��ѡ��
    void run();
};