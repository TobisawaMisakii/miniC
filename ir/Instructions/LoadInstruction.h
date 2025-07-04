#pragma once

#include <string>

#include "Value.h"
#include "Instruction.h"

/// @brief Load指令，用于从内存加载值到寄存器
class LoadInstruction : public Instruction {
private:
    Value * source; // 源操作数，表示内存地址
    bool notstore;

public:
    /// @brief 构造函数
    /// @param _func 所属的函数
    /// @param _result 结果操作数
    /// @param _sourcePtr 源操作数(指针，表示内存地址)
    LoadInstruction(Function * _func, Value * _sourcePtr, bool _notstore = false);

    /// @brief 转换成字符串
    /// @param str 转换后的字符串
    void toString(std::string & str) override;
};
