#pragma once
#include "Instruction.h"

class UnaryInstruction : public Instruction {
public:
    /// @brief 构造函数
    /// @param _func 所属函数
    /// @param op 操作符
    /// @param srcVal1 源操作数
    /// @param result 结果值
    explicit UnaryInstruction(Function * _func, IRInstOperator op, Value * srcVal1);

    /// @brief 转换成字符串
    /// @param str 转换后的字符串
    void toString(std::string & str) override;

    /// @brief 获取操作数
    /// @return 操作数
    [[nodiscard]] Value * getSrcVal1() const;


protected:
    /// @brief 源操作数
    Value * srcVal1 = nullptr;

    /// @brief 操作符
    IRInstOperator op = IRInstOperator::IRINST_OP_MAX;
};
