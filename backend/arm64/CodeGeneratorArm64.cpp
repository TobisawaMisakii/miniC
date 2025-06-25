///
/// @file CodeGeneratorArm64.cpp
/// @brief ARM32的后端处理实现
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
/// @brief 引用main.c的全局变量，为了便于控制
///
extern bool gAsmAlsoShowIR;

/// @brief 构造函数
/// @param tab 符号表
CodeGeneratorArm64::CodeGeneratorArm64(Module * _module) : CodeGeneratorAsm(_module)
{}

/// @brief 析构函数
CodeGeneratorArm64::~CodeGeneratorArm64()
{}

/// @brief 产生汇编头部分
void CodeGeneratorArm64::genHeader()
{
    fprintf(fp, "%s\n", "	.arch armv8-a");
    // fprintf(fp, "%s\n", ".arm");
    // fprintf(fp, "%s\n", ".fpu vfpv4");
}

/// @brief 全局变量Section，主要包含初始化的和未初始化过的
void CodeGeneratorArm64::genDataSection()
{
    // 生成代码段
    fprintf(fp, ".text\n");

    for (GlobalVariable * var: module->getGlobalVariables()) {
        if (var->isInBSSSection()) {
            // 未初始化的全局变量，位于 BSS 段
            fprintf(fp, ".section .bss\n");
            fprintf(fp, ".comm %s, %d, %d\n", var->getName().c_str(), var->getType()->getSize(), var->getAlignment());
        } else {
            // 已初始化的全局变量，位于 data 段
            fprintf(fp, ".section .data\n");
            fprintf(fp, ".global %s\n", var->getName().c_str());
            fprintf(fp, ".align %d\n", var->getAlignment());
            fprintf(fp, ".type %s, %%object\n", var->getName().c_str());
            fprintf(fp, "%s:\n", var->getName().c_str());

            if (var->getType()->isIntegerType()) {
                // 获取初始化值
                int value = var->GetintValue();
                fprintf(fp, ".word %d\n", value);
            }
        }
    }
}
/// @brief 获取IR变量相关信息字符串
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
        // 寄存器
        str += "\t@ " + showName + ":" + PlatformArm64::regName[regId];
    } else if (val->getMemoryAddr(&baseRegId, &offset)) {
        // 栈内寻址，[fp,#4]
        str += "\t@ " + showName + ":[" + PlatformArm64::regName[baseRegId] + ",#" + std::to_string(offset) + "]";
    }
}

/// @brief 针对函数进行汇编指令生成，放到.text代码段中
/// @param func 要处理的函数
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

/// @brief 寄存器分配
/// @param func 函数指针
void CodeGeneratorArm64::registerAllocation(Function * func)
{
    // 内置函数不需要处理
    if (func->isBuiltin()) {
        return;
    }

    // 最简单/朴素的寄存器分配策略：局部变量和临时变量都保存在栈内，全局变量在静态存储.data区中
    // R0,R1,R2和R3寄存器不需要保护，可直接使用
    // SP寄存器预留，不需要保护，但需要保证值的正确性
    // R4-R10, fp(11), lx(14)都需要保护，没有函数调用的函数可不用保护lx寄存器
    // 被保留的寄存器主要有：
    //  (1) FP寄存器用于栈寻址，即R11
    //  (2) LX寄存器用于函数调用，即R14。没有函数调用的函数可不用保护lx寄存器
    //  (3) R10寄存器用于立即数过大时要通过寄存器寻址，这里简化处理进行预留

    std::vector<int32_t> & protectedRegNo = func->getProtectedReg();
    protectedRegNo.clear();
    protectedRegNo.push_back(ARM64_FP_REG_NO);
    if (func->getExistFuncCall()) {
        protectedRegNo.push_back(ARM64_LR_REG_NO);
    }

    // 调整函数调用指令，主要是前四个寄存器传值，后面用栈传递
    // 为了更好的进行寄存器分配，可以进行对函数调用的指令进行预处理
    // 当然也可以不做处理，不过性能更差。这个处理是可选的。
    adjustFuncCallInsts(func);

    // 为局部变量和临时变量在栈内分配空间，指定偏移，进行栈空间的分配
    stackAlloc(func);

    // 函数形参要求前四个寄存器分配，后面的参数采用栈传递，实现实参的值传递给形参
    // 这一步是必须的
    adjustFormalParamInsts(func);

#if 0
    // 临时输出调整后的IR指令，用于查看当前的寄存器分配、栈内变量分配、实参入栈等信息的正确性
    std::string irCodeStr;
    func->toString(irCodeStr);
    std::cout << irCodeStr << std::endl;
#endif
}

/// @brief 寄存器分配前对函数内的指令进行调整，以便方便寄存器分配
/// @param func 要处理的函数
void CodeGeneratorArm64::adjustFormalParamInsts(Function * func)
{
    // 函数形参的前八个实参采用寄存器传值 (x0-x7)
    auto & params = func->getParams();

    // 形参的前八个通过寄存器来传值x0-x7
    for (int k = 0; k < (int) params.size() && k <= 7; k++) {
        // 前八个设置分配寄存器
        simpleRegisterAllocator.bitmapSet(k);
        params[k]->setRegId(k);
		
    }

    // 根据ARM64版C语言的调用约定，除前8个外的实参进行值传递
    // 这些参数位于调用者的栈帧中，通过FP+正偏移量访问
    int64_t param_offset = 16; // 从FP+16开始访问参数(跳过保存的FP和LR)
    for (int k = 8; k < (int) params.size(); k++) {
        // ARM64架构下变量需要8字节对齐
        params[k]->setMemoryAddr(ARM64_FP_REG_NO, param_offset); // 使用FP基址寄存器，正偏移量
        param_offset += 8;                                       // ARM64平台参数大小为8字节
    }
}

/// @brief 寄存器分配前对函数内的指令进行调整，以便方便寄存器分配
/// @param func 要处理的函数
void CodeGeneratorArm64::adjustFuncCallInsts(Function * func)
{
    // 当前函数的指令列表
    auto & insts = func->getInterCode().getInsts();

    // 获取已分配的局部变量栈帧大小
    int32_t local_vars_size = func->getMaxDep();

    // 为函数调用参数预留的栈空间从局部变量区域之后开始
    // 这样避免与局部变量区域冲突
    int param_area_base = local_vars_size;

    // 函数返回值用x0寄存器
    for (auto pIter = insts.begin(); pIter != insts.end(); pIter++) {
        // 检查是否是函数调用指令
        if (Instanceof(callInst, FuncCallInstruction *, *pIter)) {
            // 处理超过8个的参数，它们需要通过栈传递
            // 参数区域偏移量从局部变量区域之后开始
            int param_offset = param_area_base;

            for (int32_t k = 8; k < callInst->getOperandsNum(); k++) {
                auto arg = callInst->getOperand(k);

                // 新建一个内存变量，用于栈传值到形参变量中
                // 注意：这里使用SP作为基址寄存器，偏移量从局部变量区域之后开始
                LocalVariable * newVal = func->newLocalVarValue(IntegerType::getTypeInt());
                newVal->setMemoryAddr(ARM64_SP_REG_NO, param_offset); // 使用SP + 局部变量区域大小 + 参数偏移
                param_offset += 8;                                    // ARM64平台参数大小为8字节

                Instruction * assignInst = new MoveInstruction(func, newVal, arg);
                callInst->setOperand(k, newVal);
                pIter = insts.insert(pIter, assignInst);
                pIter++;
            }

            // 处理前8个参数，它们通过寄存器传递
            for (int k = 0; k < callInst->getOperandsNum() && k < 8; k++) {
                auto arg = callInst->getOperand(k);

                if (arg->getRegId() == k) {
                    // 寄存器已经正确，不需要额外处理
                    continue;
                } else {
                    // 创建临时变量，指定寄存器
                    Instruction * assignInst =
                        new MoveInstruction(func, PlatformArm64::intRegVal[k], callInst->getOperand(k));

                    simpleRegisterAllocator.bitmapSet(k);
                    callInst->setOperand(k, PlatformArm64::intRegVal[k]);
                    pIter = insts.insert(pIter, assignInst);
                    pIter++;
                }
            }

            // 处理函数返回值
            if (callInst->hasResultValue()) {
                if (callInst->getRegId() == 0) {
                    // 结果已在x0中，不需要额外处理
                } else {
                    // 将x0中的返回值移动到目标位置
                    Instruction * assignInst = new MoveInstruction(func, callInst, PlatformArm64::intRegVal[0]);
                    pIter = insts.insert(pIter + 1, assignInst);
                }
            }
        }
    }

    // 计算所有函数调用中需要的最大参数空间
    int max_args_space = 0;
    for (auto inst: insts) {
        if (Instanceof(callInst, FuncCallInstruction *, inst)) {
            int args_cnt = callInst->getOperandsNum();
            if (args_cnt > 8) {
                // 只计算超过8个参数后需要栈传递的部分
                int args_space = (args_cnt - 8) * 8;
                max_args_space = std::max(max_args_space, args_space);
            }
        }
    }

    // 记录调用其他函数时需要的最大参数数量
    func->setMaxFuncCallArgCnt(max_args_space / 8 + 8);
}

/// @brief 栈空间分配
/// @param func 要处理的函数
void CodeGeneratorArm64::stackAlloc(Function * func)
{

    // 栈变量分配起始偏移量
    int32_t var_offset = 0;

    // 获取函数变量列表
    std::vector<LocalVariable *> & vars = func->getVarValues();

    // 遍历所有局部变量进行栈空间分配
    for (auto var: vars) {
        // 只处理未分配寄存器且未分配内存地址的变量
        if ((var->getRegId() == -1) && (!var->getMemoryAddr())) {
            int32_t size;
            // 计算变量大小

            size = var->getType()->getSize();

            // 64位ARM平台按照8字节对齐
            size += (8 - size % 8) % 8;

            // 所有局部变量通过SP的正偏移量访问
            // 这与生成的标准汇编代码一致
            var->setMemoryAddr(ARM64_SP_REG_NO, var_offset);

            // 累加偏移量，确保下一个变量不会与当前变量重叠
            var_offset += size;
        }
    }

    // 遍历指令中临时变量，与局部变量采用相同的分配策略
    for (auto inst: func->getInterCode().getInsts()) {
        if (inst->hasResultValue() && inst->getRegId() == -1 && !inst->getMemoryAddr()) {
            int32_t size = inst->getType()->getSize();

            // 64位ARM平台按照8字节对齐
            size += (8 - size % 8) % 8;

            // 临时变量也通过SP的正偏移量访问
            inst->setMemoryAddr(ARM64_SP_REG_NO, var_offset);

            // 累加偏移量，确保不重叠
            var_offset += size;
        }
    }

    // 确保栈帧16字节对齐(ARM64 ABI要求)
    if (var_offset % 16 != 0) {
        var_offset += 16 - (var_offset % 16);
    }

    // 记录函数的局部变量区域总大小
    func->setMaxDep(var_offset);
}