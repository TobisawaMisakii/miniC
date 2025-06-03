#pragma once

#include <string>
#include "RegVariable.h"

#define ARM64_SAVED_REG1 19
#define ARM64_SAVED_REG2 20

// ��ʱ�Ĵ���
#define ARM64_TMP_REG_NO 16

// ջ�Ĵ���SP��FP
#define ARM64_SP_REG_NO 31
#define ARM64_FP_REG_NO 29

// ���ӼĴ���LR
#define ARM64_LR_REG_NO 30

/// @brief ARM64ƽ̨��Ϣ
class PlatformArm64 {

    static void roundLeftShiftTwoBit(unsigned int & num);
    static bool __constExpr(int64_t num);

public:
    static bool constExpr(int64_t num);
    static bool isDisp(int64_t num);
    static bool isReg(std::string name);

    // ��������64λ�Ĵ�����(x0-x30)ת��Ϊ32λ��ʽ(w0-w30)
    static std::string toWReg(const std::string & xreg);

    static const int maxRegNum = 32;       // x0-x30, sp
    static const int maxUsableRegNum = 16; // x0-x15 ����ͨ�üĴ���

    static const std::string regName[maxRegNum];
    static const std::string floatregName[maxRegNum];
    static RegVariable * intRegVal[PlatformArm64::maxRegNum];
    static RegVariable * floatRegVal[PlatformArm64::maxRegNum];
};