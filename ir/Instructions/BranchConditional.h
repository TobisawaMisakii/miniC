#pragma once
#include "Instruction.h"
#include "LabelInstruction.h"
#include "Types/VoidType.h"

class BranchCondInstruction : public Instruction {
public:
    // 构造函数
    /// @param func 所属函数
    /// @param cond 条件值
    /// @param target 跳转目标
    BranchCondInstruction(Function * _func, Value * _cond, Instruction * _target_1, Instruction * _target_0);

    /// @brief 转换成字符串
    void toString(std::string & str) override;

    /// @brief 获取条件值
    /// @return 条件值
    [[nodiscard]] Value * getCond();

    /// @brief 获取目标Label指令
    /// @return 目标Label指令
    [[nodiscard]] LabelInstruction * getTarget(int no) const;

private:
    /// @brief 条件值
    Value * cond;

    /// @brief cond成立时跳转的目标Label指令
    /// @details 这个指令的目标是一个LabelInstruction
    LabelInstruction * target_1;

    /// @brief cond不成立时跳转的目标Label指令
    /// @details 这个指令的目标是一个LabelInstruction
    LabelInstruction * target_0;
};
