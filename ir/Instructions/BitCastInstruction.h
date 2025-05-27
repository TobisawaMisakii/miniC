#pragma once

#include <string>
#include "Instruction.h"
#include "Value.h"
#include "Type.h"

class BitCastInstruction : public Instruction {
public:
    BitCastInstruction(Function * func, Value * srcVal, Type * destType);

    void toString(std::string & str) override;

    Value * getSrcVal() const
    {
        return srcVal;
    }
    Type * getDestType() const
    {
        return destType;
    }

private:
    Value * srcVal;
    Type * destType;
};