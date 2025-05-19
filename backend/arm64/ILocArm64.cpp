///
/// @file ILocArm64.cpp
/// @brief ָ�����й����ʵ�֣�ILOC��ȫ��ΪIntermediate Language for Optimizing Compilers
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
#include <cstdio>
#include <string>

#include "ILocArm64.h"
#include "Common.h"
#include "Function.h"
#include "PlatformArm64.h"
#include "Module.h"

ArmInst64::ArmInst64(std::string _opcode,
                     std::string _result,
                     std::string _arg1,
                     std::string _arg2,
                     std::string _cond,
                     std::string _addition)
    : opcode(_opcode), cond(_cond), result(_result), arg1(_arg1), arg2(_arg2), addition(_addition), dead(false)
{}

/*
    ָ�������滻
*/
void ArmInst64::replace(std::string _opcode,
                        std::string _result,
                        std::string _arg1,
                        std::string _arg2,
                        std::string _cond,
                        std::string _addition)
{
    opcode = _opcode;
    result = _result;
    arg1 = _arg1;
    arg2 = _arg2;
    cond = _cond;
    addition = _addition;

#if 0
    // �ղ�����������Ϊdead
    if (op == "") {
        dead = true;
    }
#endif
}

/*
    ����Ϊ��Чָ��
*/
void ArmInst64::setDead()
{
    dead = true;
}

/*
    �������
*/
std::string ArmInst64::outPut()
{
    // ���ô��룬ʲô�������
    if (dead) {
        return "";
    }

    // ռλָ��,������Ҫ���һ���ղ��������Ƿ�֧�� FIXME
    if (opcode.empty()) {
        return "";
    }

    std::string ret = opcode;

    if (!cond.empty()) {
        ret += cond;
    }

    // ������
    if (!result.empty()) {
        if (result == ":") {
            ret += result;
        } else {
            ret += " " + result;
        }
    }

    // ��һԪ�������
    if (!arg1.empty()) {
        ret += "," + arg1;
    }

    // �ڶ�Ԫ�������
    if (!arg2.empty()) {
        ret += "," + arg2;
    }

    // ����������Ϣ���
    if (!addition.empty()) {
        ret += "," + addition;
    }

    return ret;
}

#define emit(...) code.push_back(new ArmInst64(__VA_ARGS__))

/// @brief ���캯��
/// @param _module ���ű�
ILocArm64::ILocArm64(Module * _module)
{
    this->module = _module;
}

/// @brief ��������
ILocArm64::~ILocArm64()
{
    std::list<ArmInst64 *>::iterator pIter;

    for (pIter = code.begin(); pIter != code.end(); ++pIter) {
        delete (*pIter);
    }
}

/// @brief ɾ�����õ�Labelָ��
void ILocArm64::deleteUsedLabel()
{
    std::list<ArmInst64 *> labelInsts;
    for (ArmInst64 * arm: code) {
        if ((!arm->dead) && (arm->opcode[0] == '.') && (arm->result == ":")) {
            labelInsts.push_back(arm);
        }
    }

    for (ArmInst64 * labelArm: labelInsts) {
        bool labelUsed = false;

        for (ArmInst64 * arm: code) {
            // TODO ת������ָ���ʶ�����ݶ����޸��ж�
            if ((!arm->dead) && (arm->opcode[0] == 'b') && (arm->result == labelArm->opcode)) {
                labelUsed = true;
                break;
            }
        }

        if (!labelUsed) {
            labelArm->setDead();
        }
    }
}

/// @brief ������
/// @param file ������ļ�ָ��
/// @param outputEmpty �Ƿ���������
void ILocArm64::outPut(FILE * file, bool outputEmpty)
{
    for (auto arm: code) {

        std::string s = arm->outPut();

        if (arm->result == ":") {
            // Labelָ�����ҪTab���
            fprintf(file, "%s\n", s.c_str());
            continue;
        }

        if (!s.empty()) {
            fprintf(file, "\t%s\n", s.c_str());
        } else if ((outputEmpty)) {
            fprintf(file, "\n");
        }
    }
}

/// @brief ��ȡ��ǰ�Ĵ�������
/// @return ��������
std::list<ArmInst64 *> & ILocArm64::getCode()
{
    return code;
}

/**
 * ���ֱ��ַ�������flagΪ�棬���Ϊ������Ѱַ����#��
 */
std::string ILocArm64::toStr(int num, bool flag)
{
    std::string ret;

    if (flag) {
        ret = "#";
    }

    ret += std::to_string(num);

    return ret;
}

/*
    ������ǩ
*/
void ILocArm64::label(std::string name)
{
    // .L1:
    emit(name, ":");
}

/// @brief 0��Դ������ָ��
/// @param op ������
/// @param rs ������
void ILocArm64::inst(std::string op, std::string rs)
{
    emit(op, rs);
}

/// @brief һ��������ָ��
/// @param op ������
/// @param rs ������
/// @param arg1 Դ������
void ILocArm64::inst(std::string op, std::string rs, std::string arg1)
{
    emit(op, rs, arg1);
}

/// @brief һ��������ָ��
/// @param op ������
/// @param rs ������
/// @param arg1 Դ������
/// @param arg2 Դ������
void ILocArm64::inst(std::string op, std::string rs, std::string arg1, std::string arg2)
{
    emit(op, rs, arg1, arg2);
}

///
/// @brief ע��ָ��������ֺ�
///
void ILocArm64::comment(std::string str)
{
    emit("@", str);
}

/*
    ���������� ldr r0,=#100
*/
void ILocArm64::load_imm(int rs_reg_no, int constant)
{
    // movw:�� 16 λ�������ŵ��Ĵ����ĵ�16λ����16λ��0
    // movt:�� 16 λ�������ŵ��Ĵ����ĸ�16λ���� 16λ��Ӱ��
    if (0 == ((constant >> 16) & 0xFFFF)) {
        // �����16λ������Ϊ0��ֱ��movw
        emit("movw", PlatformArm64::regName[rs_reg_no], "#:lower16:" + std::to_string(constant));
    } else {
        // �����16λ��Ϊ0����movw��Ȼ��movt
        emit("movw", PlatformArm64::regName[rs_reg_no], "#:lower16:" + std::to_string(constant));
        emit("movt", PlatformArm64::regName[rs_reg_no], "#:upper16:" + std::to_string(constant));
    }
}

/// @brief ���ط���ֵ ldr r0,=g ldr r0,=.L1
/// @param rs_reg_no ����Ĵ������
/// @param name ������
void ILocArm64::load_symbol(int rs_reg_no, std::string name)
{
    // movw r10, #:lower16:a
    // movt r10, #:upper16:a
    emit("movw", PlatformArm64::regName[rs_reg_no], "#:lower16:" + name);
    emit("movt", PlatformArm64::regName[rs_reg_no], "#:upper16:" + name);
}

/// @brief ��ַѰַ ldr r0,[fp,#100]
/// @param rsReg ����Ĵ���
/// @param base_reg_no ��ַ�Ĵ���
/// @param offset ƫ��
void ILocArm64::load_base(int rs_reg_no, int base_reg_no, int offset)
{
    std::string rsReg = PlatformArm64::regName[rs_reg_no];
    std::string base = PlatformArm64::regName[base_reg_no];

    if (PlatformArm64::isDisp(offset)) {
        // ��Ч��ƫ�Ƴ���
        if (offset) {
            // [fp,#-16] [fp]
            base += "," + toStr(offset);
        }
    } else {

        // ldr r8,=-4096
        load_imm(rs_reg_no, offset);

        // fp,r8
        base += "," + rsReg;
    }

    // �ڴ�Ѱַ
    base = "[" + base + "]";

    // ldr r8,[fp,#-16]
    // ldr r8,[fp,r8]
    emit("ldr", rsReg, base);
}

/// @brief ��ַѰַ str r0,[fp,#100]
/// @param srcReg Դ�Ĵ���
/// @param base_reg_no ��ַ�Ĵ���
/// @param disp ƫ��
/// @param tmp_reg_no ������Ҫ��ʱ�Ĵ������
void ILocArm64::store_base(int src_reg_no, int base_reg_no, int disp, int tmp_reg_no)
{
    std::string base = PlatformArm64::regName[base_reg_no];

    if (PlatformArm64::isDisp(disp)) {
        // ��Ч��ƫ�Ƴ���

        // ��dispΪ0����ֱ�Ӳ��û�ַ��������û�ַ+ƫ��
        // [fp,#-16] [fp]
        if (disp) {
            base += "," + toStr(disp);
        }
    } else {
        // �Ȱ���������ֵ��ָ���ļĴ���tmpReg��Ȼ����û�ַ+�Ĵ����ķ�ʽ����

        // ldr r9,=-4096
        load_imm(tmp_reg_no, disp);

        // fp,r9
        base += "," + PlatformArm64::regName[tmp_reg_no];
    }

    // �ڴ���Ѱַ
    base = "[" + base + "]";

    // str r8,[fp,#-16]
    // str r8,[fp,r9]
    emit("str", PlatformArm64::regName[src_reg_no], base);
}

/// @brief �Ĵ���Mov����
/// @param rs_reg_no ����Ĵ���
/// @param src_reg_no Դ�Ĵ���
void ILocArm64::mov_reg(int rs_reg_no, int src_reg_no)
{
    emit("mov", PlatformArm64::regName[rs_reg_no], PlatformArm64::regName[src_reg_no]);
}

/// @brief ���ر������Ĵ�������֤�������ŵ�reg��
/// @param rs_reg_no ����Ĵ���
/// @param src_var Դ������
void ILocArm64::load_var(int rs_reg_no, Value * src_var)
{

    if (Instanceof(constVal, ConstInt *, src_var)) {
        // ���ͳ���

        // TODO Ŀǰֻ������������ 100
        // ldr r8,#100
        load_imm(rs_reg_no, constVal->getVal());
    } else if (src_var->getRegId() != -1) {

        // Դ������Ϊ�Ĵ�������
        int32_t src_regId = src_var->getRegId();

        if (src_regId != rs_reg_no) {

            // mov r8,r2 | �������Ż��ռ䡪������r8
            emit("mov", PlatformArm64::regName[rs_reg_no], PlatformArm64::regName[src_regId]);
        }
    } else if (Instanceof(globalVar, GlobalVariable *, src_var)) {
        // ȫ�ֱ���

        // ��ȡȫ�ֱ����ĵ�ַ
        // movw r8, #:lower16:a
        // movt r8, #:lower16:a
        load_symbol(rs_reg_no, globalVar->getName());

        // ldr r8, [r8]
        emit("ldr", PlatformArm64::regName[rs_reg_no], "[" + PlatformArm64::regName[rs_reg_no] + "]");

    } else {

        // ջ+ƫ�Ƶ�Ѱַ��ʽ

        // ջ֡ƫ��
        int32_t var_baseRegId = -1;
        int64_t var_offset = -1;

        bool result = src_var->getMemoryAddr(&var_baseRegId, &var_offset);
        if (!result) {
            minic_log(LOG_ERROR, "BUG");
        }

        // ����ջ�ڷ���ľֲ����飬��ֱ����ջָ���Ͻ����ƶ�������
        // �������βΣ��䱣����ǵ��ú���ջ������ĵ�ַ����Ҫ��ȡ����

        // ldr r8,[sp,#16]
        load_base(rs_reg_no, var_baseRegId, var_offset);
    }
}

/// @brief ���ر�����ַ���Ĵ���
/// @param rs_reg_no
/// @param var
void ILocArm64::lea_var(int rs_reg_no, Value * var)
{
    // �����صı����϶����ǳ�����
    // �����صı����϶����ǼĴ���������

    // Ŀǰֻ���Ǿֲ�����

    // ջ֡ƫ��
    int32_t var_baseRegId = -1;
    int64_t var_offset = -1;

    bool result = var->getMemoryAddr(&var_baseRegId, &var_offset);
    if (!result) {
        minic_log(LOG_ERROR, "BUG");
    }

    // lea r8, [fp,#-16]
    leaStack(rs_reg_no, var_baseRegId, var_offset);
}

/// @brief ����Ĵ�������������֤����������r8�����浽����
/// @param src_reg_no Դ�Ĵ���
/// @param dest_var  ����
/// @param tmp_reg_no �������Ĵ���
void ILocArm64::store_var(int src_reg_no, Value * dest_var, int tmp_reg_no)
{
    // ������Ŀ������϶����ǳ���

    if (dest_var->getRegId() != -1) {

        // �Ĵ�������

        // -1��ʾ�ǼĴ�����������ʾ�Ĵ���������ֵ
        int dest_reg_id = dest_var->getRegId();

        // �Ĵ�����һ������Ҫmov����
        if (src_reg_no != dest_reg_id) {

            // mov r2,r8 | �������Ż��ռ䡪������r8
            emit("mov", PlatformArm64::regName[dest_reg_id], PlatformArm64::regName[src_reg_no]);
        }

    } else if (Instanceof(globalVar, GlobalVariable *, dest_var)) {
        // ȫ�ֱ���

        // ��ȡ���ŵĵ�ַ���Ĵ���r10
        load_symbol(tmp_reg_no, globalVar->getName());

        // str r8, [r10]
        emit("str", PlatformArm64::regName[src_reg_no], "[" + PlatformArm64::regName[tmp_reg_no] + "]");

    } else {

        // ���ھֲ���������ֱ�Ӵ�ջ��ַ+ƫ��Ѱַ

        // TODO Ŀǰֻ���Ǿֲ�����

        // ջ֡ƫ��
        int32_t dest_baseRegId = -1;
        int64_t dest_offset = -1;

        bool result = dest_var->getMemoryAddr(&dest_baseRegId, &dest_offset);
        if (!result) {
            minic_log(LOG_ERROR, "BUG");
        }

        // str r8,[r9]
        // str r8, [fp, # - 16]
        store_base(src_reg_no, dest_baseRegId, dest_offset, tmp_reg_no);
    }
}

/// @brief ����ջ�ڱ�����ַ
/// @param rsReg ����Ĵ�����
/// @param base_reg_no ��ַ�Ĵ���
/// @param off ƫ��
void ILocArm64::leaStack(int rs_reg_no, int base_reg_no, int off)
{
    std::string rs_reg_name = PlatformArm64::regName[rs_reg_no];
    std::string base_reg_name = PlatformArm64::regName[base_reg_no];

    if (PlatformArm64::constExpr(off))
        // add r8,fp,#-16
        emit("add", rs_reg_name, base_reg_name, toStr(off));
    else {
        // ldr r8,=-257
        load_imm(rs_reg_no, off);

        // add r8,fp,r8
        emit("add", rs_reg_name, base_reg_name, rs_reg_name);
    }
}

/// @brief ������ջ�ڿռ���䣨�ֲ��������βα���������������ֵ�����ܼĴ����������ʱ�����ȣ�
/// @param func ����
/// @param tmp_reg_No
void ILocArm64::allocStack(Function * func, int tmp_reg_no)
{
    // �����ĸ��ĺ������ò�������������4��������Ҫջ��ֵ
    int funcCallArgCnt = func->getMaxFuncCallArgCnt() - 4;
    if (funcCallArgCnt < 0) {
        funcCallArgCnt = 0;
    }

    // ����ջ֡��С
    int off = func->getMaxDep();

    off += funcCallArgCnt * 4;

    // ����Ҫ��ջ�ڶ������ռ䣬��ʲô������
    if (0 == off)
        return;

    if (PlatformArm64::constExpr(off)) {
        // sub sp,sp,#16
        emit("sub", "sp", "sp", toStr(off));
    } else {
        // ldr r8,=257
        load_imm(tmp_reg_no, off);

        // sub sp,sp,r8
        emit("sub", "sp", "sp", PlatformArm64::regName[tmp_reg_no]);
    }

    // ��������ͨ��ջ���ݵĻ�ַ�Ĵ�������
    inst("add", PlatformArm64::regName[ARM64_FP_REG_NO], "sp", toStr(funcCallArgCnt * 4));
}

/// @brief ���ú���fun
/// @param fun
void ILocArm64::call_fun(std::string name)
{
    // ��������ֵ��r0,����Ҫ����
    emit("bl", name);
}

/// @brief NOP����
void ILocArm64::nop()
{
    // FIXME �޲�������Ҫȷ���Ƿ���nopָ��
    emit("");
}

///
/// @brief ��������תָ��
/// @param label Ŀ��Label����
///
void ILocArm64::jump(std::string label)
{
    emit("b", label);
}
