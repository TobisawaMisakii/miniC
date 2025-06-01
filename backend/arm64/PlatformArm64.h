///
/// @file PlatformArm64.h
/// @brief  ARM64ƽ̨���ͷ�ļ�
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

#include <string>
#include "RegVariable.h"
// ��ӽ���Ĵ����������ڴ��ݼ�ӽ���ĵ�ַλ��
#define ARM64_XR_REG_NO 8
// �����ڲ����õ���ʱ�Ĵ���
#define ARM64_IP0_REG_NO 16
#define ARM64_IP1_REG_NO 17
// ƽ̨�Ĵ�����������ƽ̨ABIʹ�á��ڲ������⺬������X18��ƽ̨�ϣ����Ǹ��ӵ���ʱ�Ĵ�����
#define ARM64_PR_REG_NO 18
// ָ֡��Ĵ���
#define ARM64_FP_REG_NO 29
// ���ӼĴ���
#define ARM64_LP_REG_NO 30

/// @brief ARM64ƽ̨��Ϣ
class PlatformArm64 {

public:
    /// @brief ͬʱ���������͸���
    /// @param num
    /// @return
    static bool constExpr(int num);

    /// @brief �ж��Ƿ��ǺϷ���ƫ��
    /// @param num
    /// @return
    static bool isDisp(int num);

    /// @brief �ж��Ƿ��ǺϷ��ļĴ�����
    /// @param name �Ĵ�������
    /// @return �Ƿ���
    static bool isReg(std::string name);

    /// @brief ���Ĵ�����Ŀ
    static const int maxRegNum = 31;

    /// @brief ��ʹ�õ�ͨ�üĴ����ĸ���
    static const int maxUsableRegNum = 31;

    /// @brief �Ĵ��������֣�x0-x30
    static const std::string regName[maxRegNum];

    /// @brief �ԼĴ�������Value����¼λ��
    static RegVariable * intRegVal[maxRegNum];

public:
    ~PlatformArm64();
};