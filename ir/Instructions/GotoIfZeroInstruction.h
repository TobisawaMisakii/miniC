#pragma once
#include "Instruction.h"
#include "LabelInstruction.h"

class GotoIfZeroInstruction : public Instruction {
public:
    // 构造函数
    /// @param func 所属函数
    /// @param cond 条件值
    /// @param target 跳转目标
    GotoIfZeroInstruction(Function * func, Value * cond, Instruction * target);

    /// @brief 转换成字符串
    void toString(std::string & str) override;

    /// @brief 获取条件值
    /// @return 条件值
    [[nodiscard]] Value * getCond() const;

    /// @brief 获取目标Label指令
    /// @return 目标Label指令
    [[nodiscard]] LabelInstruction * getTarget() const;

private:
    /// @brief 条件值
    Value * cond;

    /// @brief 跳转到的目标Label指令
    /// @details 这个指令的目标是一个LabelInstruction
    LabelInstruction * target;
};
