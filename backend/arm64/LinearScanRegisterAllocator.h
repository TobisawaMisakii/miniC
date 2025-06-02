// File: LinearScanRegisterAllocator.h

#pragma once

#include <vector>
#include "BitMap.h"
#include "Value.h"
#include "PlatformArm64.h"

class LinearScanRegisterAllocator {

public:
    /// @brief ���캯��
    LinearScanRegisterAllocator();

    /// @brief �������� (Changed from protected to public)
    ~LinearScanRegisterAllocator();

    /// @param var ����ָ��
    /// @param no ָ���ļĴ������
    /// @return ���ط���ļĴ������
    int Allocate(Value * var = nullptr, int32_t no = -1);

    /// @brief ǿ��ռ��һ��ָ���ļĴ���
    /// @param no Ҫ����ļĴ������
    void Allocate(int32_t no);

    /// @brief ��������Ӧ��load�Ĵ������Ϊ����״̬
    /// @param var ����
    void free(Value * var);

    /// @brief ���Ĵ���no���Ϊ����״̬
    /// @param no �Ĵ������
    void free(int32_t no);

protected:
    /// @brief �Ĵ�������λ��ʹ�ù��ļĴ�������λ
    /// @param no �Ĵ������
    void bitmapSet(int32_t no);

    /// @brief �Ĵ���������Ϊ����״̬
    /// @param no �Ĵ������
    void bitmapReset(int32_t no);

protected:
    /// @brief �Ĵ���λͼ��1�ѱ�ռ�ã�0δ��ʹ��
    BitMap<PlatformArm64::maxUsableRegNum> regBitmap;

    /// @brief ��ʹ�üĴ���λͼ
    BitMap<PlatformArm64::maxUsableRegNum> usedBitmap;

    /// @brief ��Ծ����ṹ��
    struct Interval {
        Value * var;
        int start;
        int end;
        int regId;
    };

    /// @brief ��Ծ�����б�
    std::vector<Interval> intervals;

    /// @brief ��ǰ����ı����б�
    std::vector<Value *> regValues;

    /// @brief �������б����Ļ�Ծ����
    void computeIntervals();

    /// @brief ���ջ�Ծ�������ʼλ������
    void sortIntervals();

    /// @brief ���ݻ�Ծ�������Ĵ���
    void allocateRegisters();

    /// @brief ������������ļĴ���
    int findSpillRegister();
};