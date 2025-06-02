///
/// @file GlobalVariable.h
/// @brief 全局变量描述类
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

#include "GlobalValue.h"
#include "IRConstant.h"
#include "ArrayType.h"
#include "Constant.h"

///
/// @brief 全局变量，寻址时通过符号名或变量名来寻址
///
class GlobalVariable : public GlobalValue {

public:
    ///
    /// @brief 构建全局变量，默认对齐为4字节
    /// @param _type 类型
    /// @param _name 名字
    ///
    explicit GlobalVariable(Type * _type, std::string _name) : GlobalValue(_type, _name)
    {
        // 设置对齐大小
        setAlignment(4);
    }

    ///
    /// @brief  检查是否是函数
    /// @return true 是函数
    /// @return false 不是函数
    ///
    [[nodiscard]] bool isGlobalVarible() const override
    {
        return true;
    }

    ///
    /// @brief 是否属于BSS段的变量，即未初始化过的变量，或者初值都为0的变量
    /// @return true
    /// @return false
    ///
    [[nodiscard]] bool isInBSSSection() const
    {
        if (initialValue)
            return false;
        else
            return true;
    }

    ///
    /// @brief 取得变量所在的作用域层级
    /// @return int32_t 层级
    ///
    int32_t getScopeLevel() override
    {
        return 0;
    }

    ///
    /// @brief 对该Value进行Load用的寄存器编号
    /// @return int32_t 寄存器编号
    ///
    int32_t getLoadRegId() override
    {
        return this->loadRegNo;
    }

    ///
    /// @brief 对该Value进行Load用的寄存器编号
    /// @return int32_t 寄存器编号
    ///
    void setLoadRegId(int32_t regId) override
    {
        this->loadRegNo = regId;
    }

    void setInitialValue(Value * value)
    {
        initialValue = value;
    }

    Value * getInitialValue() const
    {
        return initialValue;
    }

    int GetintValue() const
    {
        if (IntValue) {
            return IntValue->getVal();
        }
        return 0;
    }
    void setIntValue(ConstInt * value)
    {
        IntValue = value;
    }
    float GetfloatValue() const
    {
        if (FloatValue) {
            return FloatValue->getVal();
        }
        return 0;
    }
    void setFloatValue(ConstFloat * value)
    {
        FloatValue = value;
    }

    ///
    /// @brief 设置是否在BSS段
    /// @param inBSSSection 是否在BSS段
    ///
    void setInBSSSection(bool inBSSSection)
    {
        this->inBSSSection = inBSSSection;
    }

    ///
    /// @brief 获取变量的寄存器编号
    /// @return int32_t 寄存器编号
    ///
    int32_t getRegId() override
    {
        return loadRegNo;
    }
    ///
    /// @brief Declare指令IR显示
    /// @param str
    ///
    void toDeclareString(std::string & str)
    {
        if (getType()->isArrayType()) {
            str = getIRName() + " = global " + getType()->toString() + " zeroinitializer, align 16";
        } else {
            // 非数组类型的处理
            if (getInitialValue()) {
                str = getIRName() + " = global " + getType()->toString() + " " + getInitialValue()->getIRName() +
                      ", align " + std::to_string(getAlignment());
                ;
            } else {
                // 全局变量的自动初始值
                std::string autoInitValue;
                if (getType()->isIntegerType()) {
                    autoInitValue = "0";
                } else if (getType()->isFloatType()) {
                    autoInitValue = "0x0";
                } else {
                    autoInitValue = nullptr;
                }
                str = getIRName() + " = global " + getType()->toString() + " " + autoInitValue + ", align " +
                      std::to_string(getAlignment());
            }
        }
    }

private:
    /// @brief 初始值
    Value * initialValue = nullptr;
    ConstInt * IntValue = nullptr;
    ConstFloat * FloatValue = nullptr;

    ///
    /// @brief 变量加载到寄存器中时对应的寄存器编号
    ///
    int32_t loadRegNo = -1;

    ///
    /// @brief 默认全局变量在BSS段，没有初始化，或者即使初始化过，但都值都为0
    ///
    bool inBSSSection = true;
};
