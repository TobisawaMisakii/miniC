///
/// @file CodeGeneratorArm64.cpp
/// @brief ARM32�ĺ�˴���ʵ��
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

#include <cstdint>
#include <cstdio>
#include <string>
#include <vector>

#include "Function.h"
#include "Module.h"
#include "PlatformArm64.h"
#include "CodeGeneratorArm64.h"
#include "InstSelectorArm64.h"

#include "ILocArm64.h"
#include "RegVariable.h"
#include "FuncCallInstruction.h"
#include "ArgInstruction.h"
#include "MoveInstruction.h"

///
/// @brief ����main.c��ȫ�ֱ�����Ϊ�˱��ڿ���
///
extern bool gAsmAlsoShowIR;

/// @brief ���캯��
/// @param tab ���ű�
CodeGeneratorArm64::CodeGeneratorArm64(Module * _module) : CodeGeneratorAsm(_module)
{}

/// @brief ��������
CodeGeneratorArm64::~CodeGeneratorArm64()
{}

/// @brief �������ͷ����
void CodeGeneratorArm64::genHeader()
{
    fprintf(fp, "%s\n", "	.arch armv8-a");
    // fprintf(fp, "%s\n", ".arm");
    // fprintf(fp, "%s\n", ".fpu vfpv4");
}

/// @brief ȫ�ֱ���Section����Ҫ������ʼ���ĺ�δ��ʼ������
void CodeGeneratorArm64::genDataSection()
{
    // ���ɴ����
    fprintf(fp, ".text\n");

    for (GlobalVariable * var: module->getGlobalVariables()) {
        if (var->isInBSSSection()) {
            // δ��ʼ����ȫ�ֱ�����λ�� BSS ��
            fprintf(fp, ".section .bss\n");
            fprintf(fp, ".comm %s, %d, %d\n", var->getName().c_str(), var->getType()->getSize(), var->getAlignment());
        } else {
            // �ѳ�ʼ����ȫ�ֱ�����λ�� data ��
            fprintf(fp, ".section .data\n");
            fprintf(fp, ".global %s\n", var->getName().c_str());
            fprintf(fp, ".align %d\n", var->getAlignment());
            fprintf(fp, ".type %s, %%object\n", var->getName().c_str());
            fprintf(fp, "%s:\n", var->getName().c_str());

            if (var->getType()->isIntegerType()) {
                // ��ȡ��ʼ��ֵ
                int value = var->GetintValue();
                fprintf(fp, ".word %d\n", value);
            }
        }
    }
}
/// @brief ��ȡIR���������Ϣ�ַ���
/// @param str
///
void CodeGeneratorArm64::getIRValueStr(Value * val, std::string & str)
{
    std::string name = val->getName();
    std::string IRName = val->getIRName();
    int32_t regId = val->getRegId();
    int32_t baseRegId;
    int64_t offset;
    std::string showName;

    if (name.empty() && (!IRName.empty())) {
        showName = IRName;
    } else if ((!name.empty()) && IRName.empty()) {
        showName = IRName;
    } else if ((!name.empty()) && (!IRName.empty())) {
        showName = name + ":" + IRName;
    } else {
        showName = "";
    }

    if (regId != -1) {
        // �Ĵ���
        str += "\t@ " + showName + ":" + PlatformArm64::regName[regId];
    } else if (val->getMemoryAddr(&baseRegId, &offset)) {
        // ջ��Ѱַ��[fp,#4]
        str += "\t@ " + showName + ":[" + PlatformArm64::regName[baseRegId] + ",#" + std::to_string(offset) + "]";
    }
}

/// @brief ��Ժ������л��ָ�����ɣ��ŵ�.text�������
/// @param func Ҫ����ĺ���
void CodeGeneratorArm64::genCodeSection(Function * func)
{
    registerAllocation(func);

    std::vector<Instruction *> & IrInsts = func->getInterCode().getInsts();

    for (auto inst: IrInsts) {
        if (inst->getOp() == IRInstOperator::IRINST_OP_LABEL) {
            inst->setName(IR_LABEL_PREFIX + std::to_string(labelIndex++));
        }
    }

    ILocArm64 iloc(module);
    InstSelectorArm64 instSelector(IrInsts, iloc, func, simpleRegisterAllocator);
    instSelector.run();
    iloc.deleteUsedLabel();

    fprintf(fp, "\n.align %d\n", func->getAlignment());
    fprintf(fp, ".global %s\n", func->getName().c_str());
    fprintf(fp, ".type %s, %%function\n", func->getName().c_str());
    fprintf(fp, "%s:\n", func->getName().c_str());

    if (gAsmAlsoShowIR) {
        for (auto localVar: func->getVarValues()) {
            std::string str;
            getIRValueStr(localVar, str);
            if (!str.empty()) {
                fprintf(fp, "%s\n", str.c_str());
            }
        }

        for (auto inst: func->getInterCode().getInsts()) {
            if (inst->hasResultValue()) {
                std::string str;
                getIRValueStr(inst, str);
                if (!str.empty()) {
                    fprintf(fp, "%s\n", str.c_str());
                }
            }
        }
    }

    iloc.outPut(fp);
}

/// @brief �Ĵ�������
/// @param func ����ָ��
void CodeGeneratorArm64::registerAllocation(Function * func)
{
    // ���ú�������Ҫ����
    if (func->isBuiltin()) {
        return;
    }

    // ���/���صļĴ���������ԣ��ֲ���������ʱ������������ջ�ڣ�ȫ�ֱ����ھ�̬�洢.data����
    // R0,R1,R2��R3�Ĵ�������Ҫ��������ֱ��ʹ��
    // SP�Ĵ���Ԥ��������Ҫ����������Ҫ��ֵ֤����ȷ��
    // R4-R10, fp(11), lx(14)����Ҫ������û�к������õĺ����ɲ��ñ���lx�Ĵ���
    // �������ļĴ�����Ҫ�У�
    //  (1) FP�Ĵ�������ջѰַ����R11
    //  (2) LX�Ĵ������ں������ã���R14��û�к������õĺ����ɲ��ñ���lx�Ĵ���
    //  (3) R10�Ĵ�����������������ʱҪͨ���Ĵ���Ѱַ������򻯴������Ԥ��

    std::vector<int32_t> & protectedRegNo = func->getProtectedReg();
    protectedRegNo.clear();
    protectedRegNo.push_back(ARM64_FP_REG_NO);
    if (func->getExistFuncCall()) {
        protectedRegNo.push_back(ARM64_LR_REG_NO);
    }

    // ������������ָ���Ҫ��ǰ�ĸ��Ĵ�����ֵ��������ջ����
    // Ϊ�˸��õĽ��мĴ������䣬���Խ��жԺ������õ�ָ�����Ԥ����
    // ��ȻҲ���Բ��������������ܸ����������ǿ�ѡ�ġ�
    adjustFuncCallInsts(func);

    // Ϊ�ֲ���������ʱ������ջ�ڷ���ռ䣬ָ��ƫ�ƣ�����ջ�ռ�ķ���
    stackAlloc(func);

    // �����β�Ҫ��ǰ�ĸ��Ĵ������䣬����Ĳ�������ջ���ݣ�ʵ��ʵ�ε�ֵ���ݸ��β�
    // ��һ���Ǳ����
    adjustFormalParamInsts(func);

#if 0
    // ��ʱ����������IRָ����ڲ鿴��ǰ�ļĴ������䡢ջ�ڱ������䡢ʵ����ջ����Ϣ����ȷ��
    std::string irCodeStr;
    func->toString(irCodeStr);
    std::cout << irCodeStr << std::endl;
#endif
}

/// @brief �Ĵ�������ǰ�Ժ����ڵ�ָ����е������Ա㷽��Ĵ�������
/// @param func Ҫ����ĺ���
void CodeGeneratorArm64::adjustFormalParamInsts(Function * func)
{
    // �����βε�ǰ�ĸ�ʵ��ֵ��ʱ�������õ��ǼĴ�����ֵ
    // ǰ�ĸ�֮��ͨ��ջ����

    // ��ע���������õ������βζ��Ƕ�Ӧ��ʵ�ε�ֵ��������ʱ����
    // ������ǲ���ʹ������Ĵ���
    auto & params = func->getParams();

    // �βε�ǰ8��ͨ���Ĵ�������ֵR0-R7
    for (int k = 0; k < (int) params.size() && k <= 7; k++) {

        // ǰ8�����÷���Ĵ���
        simpleRegisterAllocator.bitmapSet(k);
        params[k]->setRegId(k);
    }

    // ����ARM��C���Եĵ���Լ������ǰ4�����ʵ�ν���ֵ���ݣ�������ջ
    int64_t fp_esp = func->getMaxDep() + (func->getProtectedReg().size() * 4);
    for (int k = 4; k < (int) params.size(); k++) {

        // Ŀǰ�ٶ�������С����4�ֽڡ�ʵ��Ҫ��������������

        params[k]->setMemoryAddr(ARM64_FP_REG_NO, fp_esp);

        // ����4�ֽ�
        fp_esp += 4;
    }
}

/// @brief �Ĵ�������ǰ�Ժ����ڵ�ָ����е������Ա㷽��Ĵ�������
/// @param func Ҫ����ĺ���
void CodeGeneratorArm64::adjustFuncCallInsts(Function * func)
{
    std::vector<Instruction *> newInsts;

    // ��ǰ������ָ���б�
    auto & insts = func->getInterCode().getInsts();

    // ��������ֵ��R0�Ĵ����������������з���ֵ����ֵR0����Ӧ�Ĵ���
    for (auto pIter = insts.begin(); pIter != insts.end(); pIter++) {

        // ����Ƿ��Ǻ�������ָ����Һ��з���ֵ
        if (Instanceof(callInst, FuncCallInstruction *, *pIter)) {

            // ʵ��ǰ8��Ҫ�Ĵ�����ֵ����������ͨ��ջ����

            // ǰ8���ĺ����������ջ����
            int esp = 0;
            for (int32_t k = 8; k < callInst->getOperandsNum(); k++) {

                auto arg = callInst->getOperand(k);

                // �½�һ���ڴ����������ջ��ֵ���βα�����
                LocalVariable * newVal = func->newLocalVarValue(IntegerType::getTypeInt());
                newVal->setMemoryAddr(ARM64_SP_REG_NO, esp);
                esp += 8;

                Instruction * assignInst = new MoveInstruction(func, newVal, arg);

                callInst->setOperand(k, newVal);

                // ��������ָ��ǰ�����pIter��ָ��������ָ��
                pIter = insts.insert(pIter, assignInst);
                pIter++;
            }

            for (int k = 0; k < callInst->getOperandsNum() && k < 8; k++) {

                // ���ʵ�ε������Ƿ�����ʱ������
                // �������ʱ�������ñ����ɸ���Ϊ�Ĵ����������ɣ��������üĴ�����
                // ������ǣ�����뿪��һ���Ĵ���������Ȼ��ֵ����
                auto arg = callInst->getOperand(k);

                if (arg->getRegId() == k) {
                    // ��˵���Ĵ����Ѿ���ʵ�δ��ݵļĴ��������ô�����ֵָ��
                    continue;
                } else {
                    // ������ʱ������ָ���Ĵ���

                    Instruction * assignInst =
                        new MoveInstruction(func, PlatformArm64::intRegVal[k], callInst->getOperand(k));

                    callInst->setOperand(k, PlatformArm64::intRegVal[k]);

                    // ��������ָ��ǰ�����pIter��ָ��������ָ��
                    pIter = insts.insert(pIter, assignInst);
                    pIter++;
                }
            }

            for (int k = 0; k < callInst->getOperandsNum(); k++) {

                auto arg = callInst->getOperand(k);

                // �ٲ���ARGָ��
                pIter = insts.insert(pIter, new ArgInstruction(func, arg));
                pIter++;
            }

            // ��argָ���ɲ��ò�����չʾ��ɾ��
            // args.clear();

            // ��ֵָ��
            if (callInst->hasResultValue()) {

                if (callInst->getRegId() == 0) {
                    // ��������ļĴ����ͷ���ֵ�Ĵ���һ������ʲô������Ҫ��
                    ;
                } else {
                    // �����������Ҫ������ֵָ��
                    // �½�һ����ֵ����
                    Instruction * assignInst = new MoveInstruction(func, callInst, PlatformArm64::intRegVal[0]);

                    // ��������ָ�����һ��ָ���ǰ�����ָ���Ϊ��Exitָ�+1�϶���Ч
                    pIter = insts.insert(pIter + 1, assignInst);
                }
            }
        }
    }
}

/// @brief ջ�ռ����
/// @param func Ҫ����ĺ���
void CodeGeneratorArm64::stackAlloc(Function * func)
{
    // ���������ڵ�����ָ�����û�мĴ�������ı�����Ȼ�����ջ�ڿռ����

    // �������ʱ�����;ֲ���������ջ�Ͻ��з���,���βζ�Ӧʵ�ε���ʱ����(FormalParam����)����Ҫ����

    int32_t sp_esp = 0;

    // ��ȡ���������б�
    std::vector<LocalVariable *> & vars = func->getVarValues();

    for (auto var: vars) {

        // ���ڼ����͵ļĴ���������ԣ��ٶ���ʱ�����;ֲ�������������ջ�У������ڴ�
        // ������ͼ��ɫ�ȣ���ʱ����һ���ǼĴ������ֲ�����Ҳ�����޸�Ϊ�Ĵ���
        // TODO ������ν��з���ʹ����ʱ�������������ڼĴ����У���Ϊ�Ż��㿼��

        // regId��Ϊ-1����˵���ñ�������Ϊ�Ĵ���
        // baseRegNo������-1����˵���ñ����϶���ջ�ϣ������ڴ������֮ǰ�϶��Ѿ������
        if ((var->getRegId() == -1) && (!var->getMemoryAddr())) {
            // �ñ���û�з���Ĵ���

            int32_t size = var->getType()->getSize();

            // 64λARMƽ̨����8�ֽڵĴ�С����������ֲ�����
            size += (8 - size % 8) % 8;

            // ����Ҫע�������ջ��ƫ�Ʒ�Χ��һ����û��ƼĴ���+��������ʽ���Ѱַ
            // ������������Ҫ�󣬿ɲ��û�ַ�Ĵ���+�����������ķ�ʽ���ʱ���
            // ������Ҫ�Ȱ�ƫ�����ŵ��Ĵ����У�Ȼ����ƼĴ���+ƫ�ƼĴ�����Ѱַ
            // ֮����Ҫ������ʹ�õ���Value��ָ���ڼĴ�������ǰҪ�任��

            // �ֲ�����ƫ������
            var->setMemoryAddr(ARM64_FP_REG_NO, sp_esp);

            // �ۼƵ�ǰ�������С
            sp_esp += size;
        }
    }

    // ����ָ������ʱ����
    for (auto inst: func->getInterCode().getInsts()) {

        if (inst->hasResultValue()) {
            // ��ֵ

            int32_t size = inst->getType()->getSize();

            // 64λARMƽ̨����8�ֽڵĴ�С����������ֲ�����
            size += (8 - size % 8) % 8;

            // ����Ҫע�������ջ��ƫ�Ʒ�Χ��һ����û��ƼĴ���+��������ʽ���Ѱַ
            // ������������Ҫ�󣬿ɲ��û�ַ�Ĵ���+�����������ķ�ʽ���ʱ���
            // ������Ҫ�Ȱ�ƫ�����ŵ��Ĵ����У�Ȼ����ƼĴ���+ƫ�ƼĴ�����Ѱַ
            // ֮����Ҫ������ʹ�õ���Value��ָ���ڼĴ�������ǰҪ�任��

            // �ֲ�����ƫ������
            inst->setMemoryAddr(ARM64_FP_REG_NO, sp_esp);

            // �ۼƵ�ǰ�������С
            sp_esp += size;
        }
    }

    // ���ú��������ջ֡��ȣ��ڼ���ʵ���ڴ洫ֵ�Ŀռ�
    // ��ע����֧�ָ�����������뱣��ջ�ڿռ�8�ֽڶ���
    if (sp_esp % 16 != 0) {
        sp_esp += 16 - (sp_esp % 16);
    }
    func->setMaxDep(sp_esp);
}