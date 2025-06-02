#include <algorithm>
#include <vector>
#include "LinearScanRegisterAllocator.h"

LinearScanRegisterAllocator::LinearScanRegisterAllocator()
{}

LinearScanRegisterAllocator::~LinearScanRegisterAllocator()
{}

int LinearScanRegisterAllocator::Allocate(Value * var, int32_t no)
{
    if (var && (var->getLoadRegId() != -1)) {
        return var->getLoadRegId();
    }

    if (no != -1 && !regBitmap.test(no)) {
        bitmapSet(no);
        var->setLoadRegId(no);
        regValues.push_back(var);
        return no;
    }

    computeIntervals();
    sortIntervals();
    allocateRegisters();

    return var ? var->getLoadRegId() : -1;
}

void LinearScanRegisterAllocator::Allocate(int32_t no)
{
    if (regBitmap.test(no)) {
        free(no);
    }
    bitmapSet(no);
}

void LinearScanRegisterAllocator::free(Value * var)
{
    if (var && (var->getLoadRegId() != -1)) {
        regBitmap.reset(var->getLoadRegId());
        auto it = std::find(regValues.begin(), regValues.end(), var);
        if (it != regValues.end()) {
            regValues.erase(it);
        }
        var->setLoadRegId(-1);
    }
}

void LinearScanRegisterAllocator::free(int32_t no)
{
    if (no == -1)
        return;
    regBitmap.reset(no);
    auto it = std::find_if(regValues.begin(), regValues.end(), [no](Value * val) { return val->getLoadRegId() == no; });
    if (it != regValues.end()) {
        (*it)->setLoadRegId(-1);
        regValues.erase(it);
    }
}

void LinearScanRegisterAllocator::bitmapSet(int32_t no)
{
    regBitmap.set(no);
    usedBitmap.set(no);
}

void LinearScanRegisterAllocator::bitmapReset(int32_t no)
{
    regBitmap.reset(no);
    usedBitmap.reset(no);
}

void LinearScanRegisterAllocator::computeIntervals()
{
    // 计算每个变量的活跃区间
    // 假设 Value 类有 getFirstUse() 和 getLastUse() 方法
    for (Value * var: regValues) {
        int var_first_use = 0;
        int var_last_use = 0; // 判断变量最早使用和最晚使用的范围，可能后续需要补充方法
                              // getFirstUse()和getLastUse()
        Interval interval = {var, var_first_use, var_last_use, -1};
        intervals.push_back(interval);
    }
}

void LinearScanRegisterAllocator::sortIntervals()
{
    std::sort(intervals.begin(), intervals.end(), [](const Interval & a, const Interval & b) {
        return a.start < b.start;
    });
}

void LinearScanRegisterAllocator::allocateRegisters()
{
    for (auto & interval: intervals) {
        int regId = -1;

        // 查找空闲寄存器
        for (int i = 0; i < PlatformArm64::maxUsableRegNum; ++i) {
            if (!regBitmap.test(i)) {
                regId = i;
                break;
            }
        }

        if (regId == -1) {
            // 如果没有空闲寄存器，溢出一个寄存器
            regId = findSpillRegister();
            if (regId != -1) {
                free(regId);
                bitmapSet(regId);
            }
        }

        if (regId != -1) {
            interval.regId = regId;
            interval.var->setLoadRegId(regId);
            bitmapSet(regId);
        }
    }
}

int LinearScanRegisterAllocator::findSpillRegister()
{
    int spillRegId = -1;
    int earliestEnd = -1;

    for (auto & interval: intervals) {
        if (interval.regId != -1 && (earliestEnd == -1 || interval.end < earliestEnd)) {
            earliestEnd = interval.end;
            spillRegId = interval.regId;
        }
    }

    return spillRegId;
}