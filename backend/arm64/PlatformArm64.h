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
    static const int maxRegNum = 32;

    /// @brief ��ʹ�õ�ͨ�üĴ����ĸ���
    static const int maxUsableRegNum = 32;

    /// @brief �Ĵ��������֣�x0-x31
    static const std::string regName[maxRegNum];

    /// @brief �ԼĴ�������Value����¼λ��
    static RegVariable * intRegVal[maxRegNum];
};