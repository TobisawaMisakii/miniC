// Values/ConstFloat.h
#ifndef CONSTFLOAT_H
#define CONSTFLOAT_H

#pragma once
#include "Constant.h"
#include "FloatType.h"

class ConstFloat : public Constant {
public:
    explicit ConstFloat(float val) : Constant(FloatType::getTypeFloat())
    {
        name = std::to_string(val);
        floatVal = val;
    }

    [[nodiscard]] std::string getIRName() const override
    {
        return name;
    }

    float getVal()
    {
        return floatVal;
    }

    int32_t getLoadRegId() override
    {
        return this->loadRegNo;
    }

    void setLoadRegId(int32_t regId) override
    {
        this->loadRegNo = regId;
    }
    std::string floatStr;

private:
    float floatVal;
    int32_t loadRegNo = -1;
};

#endif // CONSTFLOAT_H