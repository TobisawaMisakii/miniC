#include "ArrayType.h"
#include <numeric> // 用于 std::accumulate

/// @brief 构造函数
ArrayType::ArrayType(Type * baseType, const std::vector<int32_t> & dimensions)
    : Type(Type::ArrayTyID), baseType(baseType), dimensions(dimensions)
{}

/// @brief 获取数组的基础类型
Type * ArrayType::getBaseType() const
{
    return baseType;
}

/// @brief 获取数组的维度信息
const std::vector<int32_t> & ArrayType::getDimensions() const
{
    return dimensions;
}

/// @brief 获取数组的总大小（元素个数）
int32_t ArrayType::getTotalSize() const
{
    return std::accumulate(dimensions.begin(), dimensions.end(), 1, std::multiplies<int32_t>());
}

/// @brief 获取数组类型的字符串表示
std::string ArrayType::toString() const
{
    std::string result = baseType->toString();
    for (int32_t dim: dimensions) {
        result += "[" + std::to_string(dim) + "]";
    }
    return result;
}

/// @brief 获取数组类型的大小（内存占用）
int32_t ArrayType::getSize() const
{
    return baseType->getSize() * getTotalSize();
}
