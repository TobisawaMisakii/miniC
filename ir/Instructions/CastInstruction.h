// CastInstruction.h

#include "Instruction.h"
#include "Type.h"
#include "Value.h"

#include <string>

class CastInstruction final : public Instruction {
public:
    enum class CastType { ZEXT, SEXT, SITOFP, FPTOSI };

    /// @brief 构造函数
    /// @param _func 所属函数
    /// @param _value 被扩展的value
    /// @param _resultType 目标类型
    CastInstruction(Function * _func, Value * _value, Type * _resultType);

    ~CastInstruction() override = default;

    /// @brief 转换成IR指令文本
    /// @param str IR指令
    void toString(std::string & str) override;

    /// @brief 获取被扩展的值
    /// @return 被扩展的值
    Value * getValue() const;

    /// @brief 获取扩展类型
    /// @return 扩展类型
    CastType getCastType() const;

    /// @brief 获取扩展目标类型
    /// @return 扩展目标类型
    Type * getResultType() const;

private:
    /// @brief 扩展类型
    CastType castType;

    /// @brief 被扩展的值
    Value * value;

    /// @brief 目标类型
    Type * resultType;
};
