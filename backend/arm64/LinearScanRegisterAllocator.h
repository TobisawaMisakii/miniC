// File: LinearScanRegisterAllocator.h

#pragma once

#include <vector>
#include "BitMap.h"
#include "Value.h"
#include "PlatformArm64.h"

class LinearScanRegisterAllocator {

public:
    /// @brief 构造函数
    LinearScanRegisterAllocator();

    /// @brief 析构函数 (Changed from protected to public)
    ~LinearScanRegisterAllocator();

    /// @param var 变量指针
    /// @param no 指定的寄存器编号
    /// @return 返回分配的寄存器编号
    int Allocate(Value * var = nullptr, int32_t no = -1);

    /// @brief 强制占用一个指定的寄存器
    /// @param no 要分配的寄存器编号
    void Allocate(int32_t no);

    /// @brief 将变量对应的load寄存器标记为空闲状态
    /// @param var 变量
    void free(Value * var);

    /// @brief 将寄存器no标记为空闲状态
    /// @param no 寄存器编号
    void free(int32_t no);

protected:
    /// @brief 寄存器被置位，使用过的寄存器被置位
    /// @param no 寄存器编号
    void bitmapSet(int32_t no);

    /// @brief 寄存器被重置为空闲状态
    /// @param no 寄存器编号
    void bitmapReset(int32_t no);

protected:
    /// @brief 寄存器位图：1已被占用，0未被使用
    BitMap<PlatformArm64::maxUsableRegNum> regBitmap;

    /// @brief 已使用寄存器位图
    BitMap<PlatformArm64::maxUsableRegNum> usedBitmap;

    /// @brief 活跃区间结构体
    struct Interval {
        Value * var;
        int start;
        int end;
        int regId;
    };

    /// @brief 活跃区间列表
    std::vector<Interval> intervals;

    /// @brief 当前分配的变量列表
    std::vector<Value *> regValues;

    /// @brief 计算所有变量的活跃区间
    void computeIntervals();

    /// @brief 按照活跃区间的起始位置排序
    void sortIntervals();

    /// @brief 根据活跃区间分配寄存器
    void allocateRegisters();

    /// @brief 查找用于溢出的寄存器
    int findSpillRegister();
};