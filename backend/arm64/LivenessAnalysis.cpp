#include "LivenessAnalysis.h"
#include <algorithm>

LivenessAnalysis::LivenessAnalysis(Function * func) : function(func)
{}

void LivenessAnalysis::analyze()
{
    computeLiveRanges();
}

void LivenessAnalysis::computeLiveRanges()
{
    // 初始化所有值的活跃区间
    for (auto localVar: function->getVarValues()) {
        localVar->setLiveRange(-1, -1);
    }

    auto & instructions = function->getInterCode().getInsts();
    for (auto inst: instructions) {
        if (inst->hasResultValue()) {
            inst->setLiveRange(-1, -1);
        }
    }

    // 反向遍历指令，计算活跃结束位置
    for (auto it = instructions.rbegin(); it != instructions.rend(); ++it) {
        Instruction * inst = *it;
        int pos = instPositions[inst];

        // 处理指令的操作数（使用点）
        for (int i = 0; i < inst->getOperandsNum(); i++) {
            Value * operand = inst->getOperand(i);

            // 如果还没有设置结束位置，设置为当前位置
            if (operand->getLiveEnd() < pos) {
                operand->setLiveEnd(pos);
            }

            // 更新开始位置为最早遇到的位置
            if (operand->getLiveStart() == -1 || operand->getLiveStart() > pos) {
                operand->setLiveStart(pos);
            }
        }

        // 处理指令结果（定义点）
        if (inst->hasResultValue()) {
            Value * result = inst;

            // 如果还没有设置结束位置，设置为当前位置（定义即死亡）
            if (result->getLiveEnd() == -1) {
                result->setLiveEnd(pos);
            }

            // 设置开始位置为定义点
            if (result->getLiveStart() == -1 || result->getLiveStart() > pos) {
                result->setLiveStart(pos);
            }
        }
    }

    // 第三步：处理函数参数
    int entryPos = 0; // 函数入口位置设为0
    for (auto param: function->getParams()) {
        // 如果参数没有活跃信息，设置为入口位置定义
        if (param->getLiveStart() == -1) {
            param->setLiveStart(entryPos);
        }
        if (param->getLiveEnd() == -1) {
            param->setLiveEnd(entryPos);
        }
    }
}