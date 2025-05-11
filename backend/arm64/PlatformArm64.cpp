///
/// @file PlatformArm64.cpp
/// @brief  ARM64ƽ̨���ʵ��
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
#include "PlatformArm64.h"

#include "IntegerType.h"

const std::string PlatformArm64::regName[PlatformArm64::maxRegNum] = {
    "x0",  "x1",  "x2",  "x3",  "x4",  "x5",  "x6",  "x7",  "x8",  "x9",  "x10", "x11", "x12", "x13", "x14", "x15",
    "x16", "x17", "x18", "x19", "x20", "x21", "x22", "x23", "x24", "x25", "x26", "x27", "x28", "fp",  "lr",  "sp",
};

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
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[29], 29),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[30], 30),
    new RegVariable(IntegerType::getTypeInt(), PlatformArm64::regName[31], 31),
};

/// @brief �ж��Ƿ��ǳ������ʽ��ARM64֧�ָ����ӵ�����������
/// @param num
/// @return
bool PlatformArm64::constExpr(int num)
{
    // ARM64֧�ָ����ӵ� immediate �����߼�
    // ����򻯴���ʵ��ʵ����Ҫ�����ӵ��߼�
    return true;
}

/// @brief �ж��Ƿ��ǺϷ���ƫ�ƣ�ARM64֧�ָ����ƫ�Ʒ�Χ
/// @param num
/// @return
bool PlatformArm64::isDisp(int num)
{
    return num < 0x80000 && num > -0x80000;
}

/// @brief �ж��Ƿ��ǺϷ��ļĴ�����
/// @param s �Ĵ�������
/// @return �Ƿ���
bool PlatformArm64::isReg(std::string name)
{
    return name == "x0" || name == "x1" || name == "x2" || name == "x3" || name == "x4" || name == "x5" ||
           name == "x6" || name == "x7" || name == "x8" || name == "x9" || name == "x10" || name == "x11" ||
           name == "x12" || name == "x13" || name == "x14" || name == "x15" || name == "x16" || name == "x17" ||
           name == "x18" || name == "x19" || name == "x20" || name == "x21" || name == "x22" || name == "x23" ||
           name == "x24" || name == "x25" || name == "x26" || name == "x27" || name == "x28" || name == "x29" ||
           name == "x30" || name == "x31";
}