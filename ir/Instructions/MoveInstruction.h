///
/// @file MoveInstruction.h
/// @brief Move指令，也就是DragonIR的Asssign指令
///
/// @author zenglj (zenglj@live.com)
/// @version 1.0
/// @date 2024-09-29
///
/// @copyright Copyright (c) 2024
///
/// @par 修改日志:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-09-29 <td>1.0     <td>zenglj  <td>新建
/// </table>
///
#pragma once

#include <string>

#include "Value.h"
#include "Instruction.h"

class Function;

///
/// @brief 复制指令
///
class MoveInstruction : public Instruction {
private:
    bool dereference; // 是否需要解引用
    bool isLoad;      // 是否是加载操作
public:
    ///
    /// @brief 构造函数
    /// @param _func 所属的函数
    /// @param result 结构操作数
    /// @param srcVal1 源操作数
    /// @param deref 是否需要解引用
    /// @param load 是否是加载操作
    ///
    MoveInstruction(Function * _func, Value * result, Value * srcVal1, bool deref = false, bool load = false);

    /// @brief 转换成字符串
    void toString(std::string & str) override;
};
