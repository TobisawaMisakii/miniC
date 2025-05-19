///
/// @file InstSelectorArm64.cpp
/// @brief ָ��ѡ����-ARM64��ʵ��
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

///
/// @brief ����main.c��ȫ�ֱ�����Ϊ�˱��ڿ���
///
extern bool gAsmAlsoShowIR;

/// @brief ���캯��
/// @param _irCode ָ��
/// @param _iloc ILoc
/// @param _func ����
InstSelectorArm64::InstSelectorArm64(vector<Instruction *> & _irCode,
                                     ILocArm64 & _iloc,
                                     Function * _func,
                                     LinearScanRegisterAllocator & allocator)
    : ir(_irCode), iloc(_iloc), func(_func), linearScanRegisterAllocator(allocator)
{
    translator_handlers[IRInstOperator::IRINST_OP_ENTRY] = &InstSelectorArm64::translate_entry;
    translator_handlers[IRInstOperator::IRINST_OP_EXIT] = &InstSelectorArm64::translate_exit;

    translator_handlers[IRInstOperator::IRINST_OP_LABEL] = &InstSelectorArm64::translate_label;
    translator_handlers[IRInstOperator::IRINST_OP_GOTO] = &InstSelectorArm64::translate_goto;

    translator_handlers[IRInstOperator::IRINST_OP_ASSIGN] = &InstSelectorArm64::translate_assign;

    translator_handlers[IRInstOperator::IRINST_OP_ADD_I] = &InstSelectorArm64::translate_add_int64;
    translator_handlers[IRInstOperator::IRINST_OP_SUB_I] = &InstSelectorArm64::translate_sub_int64;

    translator_handlers[IRInstOperator::IRINST_OP_FUNC_CALL] = &InstSelectorArm64::translate_call;
    translator_handlers[IRInstOperator::IRINST_OP_ARG] = &InstSelectorArm64::translate_arg;
}

///
/// @brief ��������
///
InstSelectorArm64::~InstSelectorArm64()
{}

/// @brief ָ��ѡ��ִ��
void InstSelectorArm64::run()
{
    for (auto inst: ir) {

        // ���ָ����з���
        if (!inst->isDead()) {
            translate(inst);
        }
    }
}

/// @brief ָ����ARM64���
/// @param inst IRָ��
void InstSelectorArm64::translate(Instruction * inst)
{
    // ������
    IRInstOperator op = inst->getOp();

    map<IRInstOperator, translate_handler>::const_iterator pIter;
    pIter = translator_handlers.find(op);
    if (pIter == translator_handlers.end()) {
        // û���ҵ�����˵����ǰ��֧��
        printf("Translate: Operator(%d) not support", (int) op);
        return;
    }

    // ����ʱ���IRָ����Ϊע��
    if (gAsmAlsoShowIR) {
        outputIRInstruction(inst);
    }

    (this->*(pIter->second))(inst);
}

///
/// @brief ���IRָ��
///
void InstSelectorArm64::outputIRInstruction(Instruction * inst)
{
    std::string irStr;
    inst->toString(irStr);
    if (!irStr.empty()) {
        iloc.comment(irStr);
    }
}

/// @brief NOP�����ARM64���
/// @param inst IRָ��
void InstSelectorArm64::translate_nop(Instruction * inst)
{
    (void) inst;
    iloc.nop();
}

/// @brief Labelָ��ָ����ARM64���
/// @param inst IRָ��
void InstSelectorArm64::translate_label(Instruction * inst)
{
    Instanceof(labelInst, LabelInstruction *, inst);

    iloc.label(labelInst->getName());
}

/// @brief gotoָ��ָ����ARM64���
/// @param inst IRָ��
void InstSelectorArm64::translate_goto(Instruction * inst)
{
    Instanceof(gotoInst, GotoInstruction *, inst);

    // ��������ת
    iloc.jump(gotoInst->getTarget()->getName());
}

/// @brief �������ָ����ARM64���
/// @param inst IRָ��
void InstSelectorArm64::translate_entry(Instruction * inst)
{
    // �鿴�����ļĴ���
    auto & protectedRegNo = func->getProtectedReg();
    auto & protectedRegStr = func->getProtectedRegStr();

    bool first = true;
    for (auto regno: protectedRegNo) {
        if (first) {
            protectedRegStr = PlatformArm64::regName[regno];
            first = false;
        } else if (!first) {
            protectedRegStr += "," + PlatformArm64::regName[regno];
        }
    }

    if (!protectedRegStr.empty()) {
        iloc.inst("push", "{" + protectedRegStr + "}");
    }

    // Ϊfun����ջ֡�����ֲ���������������ֵ���ݵĿռ��
    iloc.allocStack(func, ARM64_XR_REG_NO);
}

/// @brief ��������ָ����ARM64���
/// @param inst IRָ��
void InstSelectorArm64::translate_exit(Instruction * inst)
{
    if (inst->getOperandsNum()) {
        // ���ڷ���ֵ
        Value * retVal = inst->getOperand(0);

        // ��ֵ���Ĵ���R0
        iloc.load_var(0, retVal);
    }

    auto & protectedRegStr = func->getProtectedRegStr();

    // �ָ�ջ�ռ�
    iloc.inst("add",
              PlatformArm64::regName[ARM64_FP_REG_NO],
              PlatformArm64::regName[ARM64_FP_REG_NO],
              iloc.toStr(func->getMaxDep()));

    iloc.inst("mov", "sp", PlatformArm64::regName[ARM64_FP_REG_NO]);

    // �����Ĵ����Ļָ�
    if (!protectedRegStr.empty()) {
        iloc.inst("pop", "{" + protectedRegStr + "}");
    }

    iloc.inst("bx", "lr");
}

/// @brief ��ֵָ����ARM64���
/// @param inst IRָ��
void InstSelectorArm64::translate_assign(Instruction * inst)
{
    Value * result = inst->getOperand(0);
    Value * arg1 = inst->getOperand(1);

    int64_t arg1_regId = arg1->getRegId();
    int64_t result_regId = result->getRegId();

    if (arg1_regId != -1) {
        // �Ĵ��� => �ڴ�
        // �Ĵ��� => �Ĵ���

        // r8 -> rs �����õ�r9
        iloc.store_var(arg1_regId, result, ARM64_IP0_REG_NO);
    } else if (result_regId != -1) {
        // �ڴ���� => �Ĵ���

        iloc.load_var(result_regId, arg1);
    } else {
        // �ڴ���� => �ڴ����

        int64_t temp_regno = linearScanRegisterAllocator.Allocate();

        // arg1 -> r8
        iloc.load_var(temp_regno, arg1);

        // r8 -> rs �����õ�r9
        iloc.store_var(temp_regno, result, ARM64_IP0_REG_NO);

        linearScanRegisterAllocator.free(temp_regno);
    }
}

/// @brief ��Ԫ����ָ����ARM64���
/// @param inst IRָ��
/// @param operator_name ������
/// @param rs_reg_no ����Ĵ�����
/// @param op1_reg_no Դ������1�Ĵ�����
/// @param op2_reg_no Դ������2�Ĵ�����
void InstSelectorArm64::translate_two_operator(Instruction * inst, string operator_name)
{
    Value * result = inst;
    Value * arg1 = inst->getOperand(0);
    Value * arg2 = inst->getOperand(1);

    int32_t arg1_reg_no = arg1->getRegId();
    int32_t arg2_reg_no = arg2->getRegId();
    int32_t result_reg_no = inst->getRegId();
    int32_t load_result_reg_no, load_arg1_reg_no, load_arg2_reg_no;

    // ��arg1�Ƿ��ǼĴ�����������Ĵ���Ѱַ������Ҫload�������Ĵ�����
    if (arg1_reg_no == -1) {

        // ����һ���Ĵ���r8
        load_arg1_reg_no = linearScanRegisterAllocator.Allocate(arg1);

        // arg1 -> r8�������������ƫ�Ʋ�����ָ���Ҫ����Ҫ�������Ĵ���
        iloc.load_var(load_arg1_reg_no, arg1);
    } else {
        load_arg1_reg_no = arg1_reg_no;
    }

    // ��arg2�Ƿ��ǼĴ�����������Ĵ���Ѱַ������Ҫload�������Ĵ�����
    if (arg2_reg_no == -1) {

        // ����һ���Ĵ���r9
        load_arg2_reg_no = linearScanRegisterAllocator.Allocate(arg2);

        // arg2 -> r9
        iloc.load_var(load_arg2_reg_no, arg2);
    } else {
        load_arg2_reg_no = arg2_reg_no;
    }

    // ����������Ƿ��ǼĴ���������������Ҫ����һ���µļĴ�������������Ľ��
    if (result_reg_no == -1) {
        // ����һ���Ĵ���r10�������ݴ���
        load_result_reg_no = linearScanRegisterAllocator.Allocate(result);
    } else {
        load_result_reg_no = result_reg_no;
    }

    // r8 + r9 -> r10
    iloc.inst(operator_name,
              PlatformArm64::regName[load_result_reg_no],
              PlatformArm64::regName[load_arg1_reg_no],
              PlatformArm64::regName[load_arg2_reg_no]);

    // ������ǼĴ���������Ҫ��rs_reg_name���浽���������
    if (result_reg_no == -1) {

        // ����ʹ��Ԥ������ʱ�Ĵ�������Ϊ���������ܹ��󣬱�������Ĵ����ſɲ�����

        // r10 -> result
        iloc.store_var(load_result_reg_no, result, ARM64_IP0_REG_NO);
    }

    // �ͷżĴ���
    linearScanRegisterAllocator.free(arg1);
    linearScanRegisterAllocator.free(arg2);
    linearScanRegisterAllocator.free(result);
}

/// @brief �����ӷ�ָ����ARM64���
/// @param inst IRָ��
void InstSelectorArm64::translate_add_int64(Instruction * inst)
{
    translate_two_operator(inst, "add");
}

/// @brief ��������ָ����ARM64���
/// @param inst IRָ��
void InstSelectorArm64::translate_sub_int64(Instruction * inst)
{
    translate_two_operator(inst, "sub");
}

/// @brief ��������ָ����ARM64���
/// @param inst IRָ��
void InstSelectorArm64::translate_call(Instruction * inst)
{
    FuncCallInstruction * callInst = dynamic_cast<FuncCallInstruction *>(inst);

    int32_t operandNum = callInst->getOperandsNum();

    if (operandNum != realArgCount) {

        // ���߲�һ�� Ҳ����û��ARGָ�����
        if (realArgCount != 0) {

            minic_log(LOG_ERROR, "ARGָ��ĸ�������ú���������һ��");
        }
    }

    if (operandNum) {

        // ǿ��ռ���⼸���Ĵ����������ݵļĴ���
        linearScanRegisterAllocator.Allocate(0);
        linearScanRegisterAllocator.Allocate(1);
        linearScanRegisterAllocator.Allocate(2);
        linearScanRegisterAllocator.Allocate(3);

        // ǰ�ĸ��ĺ����������ջ����
        int esp = 0;
        for (int32_t k = 4; k < operandNum; k++) {

            auto arg = callInst->getOperand(k);

            // �½�һ���ڴ����������ջ��ֵ���βα�����
            MemVariable * newVal = func->newMemVariable((Type *) PointerType::get(arg->getType()));
            newVal->setMemoryAddr(ARM64_FP_REG_NO, esp);
            esp += 4;

            Instruction * assignInst = new MoveInstruction(func, newVal, arg);

            // ���븳ֵָ��
            translate_assign(assignInst);

            delete assignInst;
        }

        for (int32_t k = 0; k < operandNum && k < 4; k++) {

            auto arg = callInst->getOperand(k);

            // ���ʵ�ε������Ƿ�����ʱ������
            // �������ʱ�������ñ����ɸ���Ϊ�Ĵ����������ɣ��������üĴ�����
            // ������ǣ�����뿪��һ���Ĵ���������Ȼ��ֵ����

            Instruction * assignInst = new MoveInstruction(func, PlatformArm64::intRegVal[k], arg);

            // ���븳ֵָ��
            translate_assign(assignInst);

            delete assignInst;
        }
    }

    iloc.call_fun(callInst->getName());

    if (operandNum) {
        linearScanRegisterAllocator.free(0);
        linearScanRegisterAllocator.free(1);
        linearScanRegisterAllocator.free(2);
        linearScanRegisterAllocator.free(3);
    }

    // ��ֵָ��
    if (callInst->hasResultValue()) {

        // �½�һ����ֵ����
        Instruction * assignInst = new MoveInstruction(func, callInst, PlatformArm64::intRegVal[0]);

        // ���븳ֵָ��
        translate_assign(assignInst);

        delete assignInst;
    }

    // �������ú����㣬ʹ���´ο�����ͳ��
    realArgCount = 0;
}

///
/// @brief ʵ��ָ����ARM64���
/// @param inst
///
void InstSelectorArm64::translate_arg(Instruction * inst)
{
    // ����֮ǰ����ȷ��Դ������Ҫô�ǼĴ�����Ҫô���ڴ棬�������
    Value * src = inst->getOperand(0);

    // ��ǰͳ�Ƶ�ARGָ�����
    int32_t regId = src->getRegId();

    if (realArgCount < 4) {
        // ǰ�ĸ�����
        if (regId != -1) {
            if (regId != realArgCount) {
                // �϶��Ĵ�����������
                minic_log(LOG_ERROR, "��%d��ARGָ�����Ĵ�����������: %d", argCount + 1, regId);
            }
        } else {
            minic_log(LOG_ERROR, "��%d��ARGָ������ǼĴ���", argCount + 1);
        }
    } else {
        // �������ڴ���䣬�����������
        int32_t baseRegId;
        bool result = src->getMemoryAddr(&baseRegId);
        if ((!result) || (baseRegId != ARM64_FP_REG_NO)) {

            minic_log(LOG_ERROR, "��%d��ARGָ�������SP�Ĵ���Ѱַ", argCount + 1);
        }
    }

    realArgCount++;
}