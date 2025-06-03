///
/// @file PlatformArm64.cpp
/// @brief  ARM64平台相关实现
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
#include "PlatformArm64.h"
#include "IntegerType.h"
#include "FloatType.h"

const std::string PlatformArm64::regName[PlatformArm64::maxRegNum] = {
    "x0",  "x1",  "x2",  "x3",  "x4",  "x5",  "x6",  "x7",  "x8",  "x9",  "x10", "x11", "x12", "x13", "x14", "x15",
    "x16", "x17", "x18", "x19", "x20", "x21", "x22", "x23", "x24", "x25", "x26", "x27", "x28", "x29", "lr",  "sp"};
const std::string PlatformArm64::floatregName[PlatformArm64::maxRegNum] = {
    "d0",  "d1",  "d2",  "d3",  "d4",  "d5",  "d6",  "d7",  "d8",  "d9",  "d10", "d11", "d12", "d13", "d14", "d15",
    "d16", "d17", "d18", "d19", "d20", "d21", "d22", "d23", "d24", "d25", "d26", "d27", "d28", "d29", "d30", "d31"};

RegVariable * PlatformArm64::intRegVal[PlatformArm64::maxRegNum] = {
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[0], 0),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[1], 1),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[2], 2),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[3], 3),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[4], 4),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[5], 5),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[6], 6),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[7], 7),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[8], 8),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[9], 9),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[10], 10),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[11], 11),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[12], 12),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[13], 13),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[14], 14),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[15], 15),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[16], 16),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[17], 17),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[18], 18),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[19], 19),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[20], 20),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[21], 21),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[22], 22),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[23], 23),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[24], 24),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[25], 25),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[26], 26),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[27], 27),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[28], 28),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[29], 29), // fp
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[30], 30), // lr
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[31], 31)  // sp
};

RegVariable * PlatformArm64::floatRegVal[PlatformArm64::maxRegNum] = {
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[0], 0),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[1], 1),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[2], 2),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[3], 3),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[4], 4),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[5], 5),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[6], 6),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[7], 7),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[8], 8),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[9], 9),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[10], 10),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[11], 11),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[12], 12),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[13], 13),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[14], 14),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[15], 15),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[16], 16),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[17], 17),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[18], 18),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[19], 19),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[20], 20),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[21], 21),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[22], 22),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[23], 23),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[24], 24),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[25], 25),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[26], 26),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[27], 27),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[28], 28),
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[29], 29), // fp
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[30], 30), // lr
    new RegVariable(FloatType::getTypeFloat(), PlatformArm64::regName[31], 31)  // sp
};
void PlatformArm64::roundLeftShiftTwoBit(unsigned int & num)
{
    const unsigned int overFlow = num & 0xc0000000;
    num = (num << 2) | (overFlow >> 30);
}

// 将64位寄存器名(x0-x30)转换为32位形式(w0-w30)
std::string PlatformArm64::toWReg(const std::string & xreg)
{
    // 仅当寄存器名以'x'开头时进行转换
    if (!xreg.empty() && xreg[0] == 'x') {
        return "w" + xreg.substr(1);
    }
    // 特殊处理sp和lr
    if (xreg == "sp")
        return "wsp";
    if (xreg == "lr")
        return "w30";

    // 无法转换则返回原名
    return xreg;
}

bool PlatformArm64::__constExpr(int64_t num)
{
    uint64_t new_num = (uint64_t) num;
    for (int i = 0; i < 32; i++) {
        if (new_num <= 0xfff)
            return true;
        roundLeftShiftTwoBit((unsigned int &) new_num);
    }
    return false;
}

bool PlatformArm64::constExpr(int64_t num)
{
    return __constExpr(num) || __constExpr(-num);
}

bool PlatformArm64::isDisp(int64_t num)
{
    return num < 4096 && num > -4096;
}

bool PlatformArm64::isReg(std::string name)
{
    for (int i = 0; i < maxRegNum; ++i) {
        if (name == regName[i])
            return true;
    }
    for (int i = 0; i < maxRegNum; ++i) {
        if (name == floatregName[i])
            return true;
    }
    return false;
}