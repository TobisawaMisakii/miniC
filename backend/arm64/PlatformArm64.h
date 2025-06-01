///
/// @file PlatformArm64.h
/// @brief  ARM64平台相关头文件
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

#include <string>
#include "RegVariable.h"
// 间接结果寄存器。它用于传递间接结果的地址位置
#define ARM64_XR_REG_NO 8
// 函数内部调用的临时寄存器
#define ARM64_IP0_REG_NO 16
#define ARM64_IP1_REG_NO 17
// 平台寄存器，保留给平台ABI使用。在不将特殊含义分配给X18的平台上，它是附加的临时寄存器。
#define ARM64_PR_REG_NO 18
// 帧指针寄存器
#define ARM64_FP_REG_NO 29
// 链接寄存器
#define ARM64_LP_REG_NO 30

/// @brief ARM64平台信息
class PlatformArm64 {

public:
    /// @brief 同时处理正数和负数
    /// @param num
    /// @return
    static bool constExpr(int num);

    /// @brief 判定是否是合法的偏移
    /// @param num
    /// @return
    static bool isDisp(int num);

    /// @brief 判断是否是合法的寄存器名
    /// @param name 寄存器名字
    /// @return 是否是
    static bool isReg(std::string name);

    /// @brief 最大寄存器数目
    static const int maxRegNum = 31;

    /// @brief 可使用的通用寄存器的个数
    static const int maxUsableRegNum = 31;

    /// @brief 寄存器的名字，x0-x30
    static const std::string regName[maxRegNum];

    /// @brief 对寄存器分配Value，记录位置
    static RegVariable * intRegVal[maxRegNum];

public:
    ~PlatformArm64();
};