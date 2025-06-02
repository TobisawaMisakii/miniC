///
/// @file ILocArm64.h
/// @brief ָ�����й����ͷ�ļ���ILOC��ȫ��ΪIntermediate Language for Optimizing Compilers
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

#include <list>
#include <string>

#include "Instruction.h"
#include "Module.h"

#define Instanceof(res, type, var) auto res = dynamic_cast<type>(var)

/// @brief �ײ���ָ�ARM32
struct ArmInst64 {

    /// @brief ������
    std::string opcode;

    /// @brief ����
    std::string cond;

    /// @brief ���
    std::string result;

    /// @brief Դ������1
    std::string arg1;

    /// @brief Դ������2
    std::string arg2;

    /// @brief ������Ϣ
    std::string addition;

    /// @brief ��ʶָ���Ƿ���Ч
    bool dead;

    /// @brief ���캯��
    /// @param op
    /// @param rs
    /// @param s1
    /// @param s2
    /// @param add
    ArmInst64(std::string op,
              std::string rs = "",
              std::string s1 = "",
              std::string s2 = "",
              std::string cond = "",
              std::string extra = "");

    /// @brief ָ�����
    /// @param op
    /// @param rs
    /// @param s1
    /// @param s2
    /// @param add
    void replace(std::string op,
                 std::string rs = "",
                 std::string s1 = "",
                 std::string s2 = "",
                 std::string cond = "",
                 std::string extra = "");

    /// @brief ������ָ��
    void setDead();
    void load_imm(int rs_reg_no, int constant);
    /// @brief ָ���ַ����������
    /// @return
    std::string outPut();
};

/// @brief �ײ�������-ARM32
class ILocArm64 {

    /// @brief ARM�������
    std::list<ArmInst64 *> code;

    /// @brief ���ű�
    Module * module;

    /// @brief ���������� ldr r0,=#100
    /// @param rs_reg_no ����Ĵ�����
    /// @param num ������
    void load_imm(int rs_reg_no, int num);
    bool is_mov_imm(uint64_t value);
    bool is_movn_imm(uint64_t value);

    /// @brief ���ط���ֵ ldr r0,=g; ldr r0,[r0]
    /// @param rsReg ����Ĵ�����
    /// @param name Label����
    void load_symbol(int rs_reg_no, std::string name);

    /// @brief ����ջ�ڱ�����ַ
    /// @param rsReg ����Ĵ�����
    /// @param base_reg_no ��ַ�Ĵ���
    /// @param off ƫ��
    void leaStack(int rs_reg_no, int base_reg_no, int offset);

public:
    /// @brief ���캯��
    /// @param _module ���ű�-ģ��
    ILocArm64(Module * _module);

    /// @brief ��������
    ~ILocArm64();

    ///
    /// @brief ע��ָ��������ֺ�
    /// @param str ע������
    ///
    void comment(std::string str);

    /// @brief ���ֱ��ַ�������flagΪ�棬���Ϊ������Ѱַ����#��
    /// @param num ������
    /// @param flag �Ƿ��#
    /// @return �ַ���
    std::string toStr(int num, bool flag = true);

    /// @brief ��ȡ��ǰ�Ĵ�������
    /// @return ��������
    std::list<ArmInst64 *> & getCode();

    /// @brief Loadָ���ַѰַ ldr r0,[fp,#100]
    /// @param rs_reg_no ����Ĵ���
    /// @param base_reg_no ��ַ�Ĵ���
    /// @param disp ƫ��
    void load_base(int rs_reg_no, int base_reg_no, int disp);

    /// @brief Storeָ���ַѰַ str r0,[fp,#100]
    /// @param src_reg_no Դ�Ĵ���
    /// @param base_reg_no ��ַ�Ĵ���
    /// @param disp ƫ��
    /// @param tmp_reg_no ������Ҫ��ʱ�Ĵ������
    void store_base(int src_reg_no, int base_reg_no, int disp, int tmp_reg_no);

    /// @brief ��ǩָ��
    /// @param name
    void label(std::string name);

    /// @brief һ��������ָ��
    /// @param op ������
    /// @param rs ������
    void inst(std::string op, std::string rs);

    /// @brief һ��������ָ��
    /// @param op ������
    /// @param rs ������
    /// @param arg1 Դ������
    void inst(std::string op, std::string rs, std::string arg1);

    /// @brief һ��������ָ��
    /// @param op ������
    /// @param rs ������
    /// @param arg1 Դ������
    /// @param arg2 Դ������
    void inst(std::string op, std::string rs, std::string arg1, std::string arg2);

    /// @brief ���ر������Ĵ���
    /// @param rs_reg_no ����Ĵ���
    /// @param var ����
    void load_var(int rs_reg_no, Value * var);

    /// @brief ���ر�����ַ���Ĵ���
    /// @param rs_reg_no ����Ĵ���
    /// @param var ����
    void lea_var(int rs_reg_no, Value * var);

    /// @brief ����Ĵ���������
    /// @param src_reg_no Դ�Ĵ�����
    /// @param var ����
    /// @param addr_reg_no ��ַ�Ĵ�����
    void store_var(int src_reg_no, Value * var, int addr_reg_no);

    /// @brief �Ĵ���Mov����
    /// @param rs_reg_no ����Ĵ���
    /// @param src_reg_no Դ�Ĵ���
    void mov_reg(int rs_reg_no, int src_reg_no);

    /// @brief ���ú���fun
    /// @param fun
    void call_fun(std::string name);

    /// @brief ����ջ֡
    /// @param func ����
    /// @param tmp_reg_No
    void allocStack(Function * func, int tmp_reg_No);

    /// @brief ���غ����Ĳ������Ĵ���
    /// @param fun
    void ldr_args(Function * fun);

    /// @brief NOP����
    void nop();

    ///
    /// @brief ��������תָ��
    /// @param label Ŀ��Label����
    ///
    void jump(std::string label);

    /// @brief ������
    /// @param file ������ļ�ָ��
    /// @param outputEmpty �Ƿ���������
    void outPut(FILE * file, bool outputEmpty = false);

    /// @brief ɾ�����õ�Labelָ��
    void deleteUsedLabel();
};