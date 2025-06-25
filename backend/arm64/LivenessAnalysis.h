#pragma once

#include <vector>
#include <map>
#include "Value.h"
#include "Function.h"

class LivenessAnalysis {
public:
    explicit LivenessAnalysis(Function * func);

    /// @brief ִ�л��Է���
    void analyze();

    /// @brief ����ָ��λ��ӳ��
    /// @param instPositions ָ�λ�õ�ӳ��
    void setInstructionPositions(const std::map<Instruction *, int> & positions)
    {
        instPositions = positions;
    }

private:
    /// @brief �����Ծ����
    void computeLiveRanges();

    Function * function;
    std::map<Instruction *, int> instPositions; // ָ�λ�õ�ӳ��
};