#pragma once

#include <vector>
#include <string>
#include "Instruction.h"
#include "Value.h"
#include "Type.h"

class GetElementPtrInstruction : public Instruction {
public:
    GetElementPtrInstruction(Function * func, Value * basePtr, const std::vector<Value *> & indices, Type * resultType);

    void toString(std::string & str) override;

    Value * getBasePtr() const
    {
        return basePtr;
    }
    const std::vector<Value *> & getIndices() const
    {
        return indices;
    }

private:
    Value * basePtr;
    std::vector<Value *> indices;
};