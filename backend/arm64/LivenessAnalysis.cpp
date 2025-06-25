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
    // ��ʼ������ֵ�Ļ�Ծ����
    for (auto localVar: function->getVarValues()) {
        localVar->setLiveRange(-1, -1);
    }

    auto & instructions = function->getInterCode().getInsts();
    for (auto inst: instructions) {
        if (inst->hasResultValue()) {
            inst->setLiveRange(-1, -1);
        }
    }

    // �������ָ������Ծ����λ��
    for (auto it = instructions.rbegin(); it != instructions.rend(); ++it) {
        Instruction * inst = *it;
        int pos = instPositions[inst];

        // ����ָ��Ĳ�������ʹ�õ㣩
        for (int i = 0; i < inst->getOperandsNum(); i++) {
            Value * operand = inst->getOperand(i);

            // �����û�����ý���λ�ã�����Ϊ��ǰλ��
            if (operand->getLiveEnd() < pos) {
                operand->setLiveEnd(pos);
            }

            // ���¿�ʼλ��Ϊ����������λ��
            if (operand->getLiveStart() == -1 || operand->getLiveStart() > pos) {
                operand->setLiveStart(pos);
            }
        }

        // ����ָ����������㣩
        if (inst->hasResultValue()) {
            Value * result = inst;

            // �����û�����ý���λ�ã�����Ϊ��ǰλ�ã����弴������
            if (result->getLiveEnd() == -1) {
                result->setLiveEnd(pos);
            }

            // ���ÿ�ʼλ��Ϊ�����
            if (result->getLiveStart() == -1 || result->getLiveStart() > pos) {
                result->setLiveStart(pos);
            }
        }
    }

    // ������������������
    int entryPos = 0; // �������λ����Ϊ0
    for (auto param: function->getParams()) {
        // �������û�л�Ծ��Ϣ������Ϊ���λ�ö���
        if (param->getLiveStart() == -1) {
            param->setLiveStart(entryPos);
        }
        if (param->getLiveEnd() == -1) {
            param->setLiveEnd(entryPos);
        }
    }
}