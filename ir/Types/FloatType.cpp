#include "FloatType.h"

///
/// @brief 唯一的VOID类型实例
///
FloatType * FloatType::oneInstanceFloat = new FloatType(32);

///
/// @brief 获取类型float
/// @return VoidType*
///
FloatType * FloatType::getTypeFloat()
{
    return oneInstanceFloat;
}