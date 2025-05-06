#pragma once

#include <vector>
#include <string>
#include "Type.h"

///
/// @brief 数组类型类
///
class ArrayType : public Type {
private:
    Type * baseType;                 // 数组的基础类型（如 int、float）
    std::vector<int32_t> dimensions; // 数组的维度信息

public:
    /// @brief 构造函数
    /// @param baseType 数组的基础类型
    /// @param dimensions 数组的维度信息
    ArrayType(Type * baseType, const std::vector<int32_t> & dimensions);

    /// @brief 获取数组的基础类型
    /// @return 基础类型
    Type * getBaseType() const override;

    /// @brief 获取数组的维度信息
    /// @return 维度信息
    const std::vector<int32_t> & getDimensions() const;

    /// @brief 获取数组的总大小（元素个数）
    /// @return 数组的总大小
    int32_t getTotalSize() const;

    /// @brief 获取数组类型的字符串表示
    /// @return 数组类型的字符串
    std::string toString() const override;

    /// @brief 获取数组类型的大小（内存占用）
    /// @return 数组类型的大小
    int32_t getSize() const override;
};