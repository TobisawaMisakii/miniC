#pragma once

#include <cstdint>
#include <string>

#include "Type.h"

class FloatType final : public Type {

public:
    ///
    /// @brief 获取单精度浮点类型，全局只有一份
    /// @return FloatType*
    ///
    static FloatType * getTypeFloat();

    ///
    /// @brief 获取类型的IR标识符
    /// @return std::string IR标识符
    ///
    [[nodiscard]] std::string toString() const override
    {
        return "float";
    }

    ///
    /// @brief 获取浮点数的位宽
    /// @return int32_t
    ///
    [[nodiscard]] int32_t getBitWidth() const
    {
        return this->bitWidth;
    }

    ///
    /// @brief 获得类型所占内存空间大小
    /// @return int32_t
    ///
    [[nodiscard]] int32_t getSize() const override
    {
        return bitWidth / 8; // 位宽除以8得到字节大小
    }

private:
    ///
    /// @brief 构造函数
    ///
    explicit FloatType(int32_t _bitWidth) : Type(Type::FloatTyID), bitWidth(_bitWidth)
    {}

    ///
    /// @brief 唯一的单精度浮点类型实例
    ///
    static FloatType * oneInstanceFloat;

    ///
    /// @brief 位宽
    ///
    int32_t bitWidth;
};