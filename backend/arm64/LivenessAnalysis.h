#pragma once

#include <vector>
#include <map>
#include "Value.h"
#include "Function.h"

class LivenessAnalysis {
public:
    explicit LivenessAnalysis(Function * func);

    /// @brief 执行活性分析
    void analyze();

    /// @brief 设置指令位置映射
    /// @param instPositions 指令到位置的映射
    void setInstructionPositions(const std::map<Instruction *, int> & positions)
    {
        instPositions = positions;
    }

private:
    /// @brief 计算活跃区间
    void computeLiveRanges();

    Function * function;
    std::map<Instruction *, int> instPositions; // 指令到位置的映射
};