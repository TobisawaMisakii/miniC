///
/// @file CodeGeneratorArm32.h
/// @brief ARM64�ĺ�˴���ͷ�ļ�
/// @author zenglj (zenglj@live.com)
/// @version 1.0
/// @date 2024-11-21
///
/// @copyright Copyright (c) 2024
///
/// @par �޸���־:
/// <table>
/// <tr><th>Date       <th>Version <th>Author  <th>Description
/// <tr><td>2024-11-21 <td>1.0     <td>zenglj  <td>����
/// </table>
///
#include "CodeGeneratorAsm.h"
#include "SimpleRegisterAllocator.h"

class CodeGeneratorArm64 : public CodeGeneratorAsm {
public:
    /// @brief ���캯��
    /// @param tab ���ű�
    CodeGeneratorArm64(Module * module);

    /// @brief ��������
    ~CodeGeneratorArm64();

protected:
    /// @brief �������ͷ����
    void genHeader() override;

    /// @brief ȫ�ֱ���Section����Ҫ������ʼ���ĺ�δ��ʼ������
    void genDataSection() override;

    /// @brief ��Ժ������л��ָ�����ɣ��ŵ�.text�������
    /// @param func Ҫ����ĺ���
    void genCodeSection(Function * func) override;

    /// @brief �Ĵ�������
    /// @param func Ҫ����ĺ���
    void registerAllocation(Function * func) override;

    /// @brief ջ�ռ����
    /// @param func Ҫ����ĺ���
    void stackAlloc(Function * func);

    /// @brief �Ĵ�������ǰ�Ժ����ڵ�ָ����е������Ա㷽��Ĵ�������
    /// @param func Ҫ����ĺ���
    void adjustFuncCallInsts(Function * func);

    /// @brief �Ĵ�������ǰ���β�ָ�����������ջ�ڿռ�����Լ��Ĵ�������
    /// @param func Ҫ����ĺ���
    void adjustFormalParamInsts(Function * func);

    ///
    /// @brief ��ȡIR���������Ϣ�ַ���
    /// @param str
    ///
    void getIRValueStr(Value * val, std::string & str);

private:
    ///
    /// @brief ����ɨ��Ĵ������䷽��
    ///
    SimpleRegisterAllocator simpleRegisterAllocator;
};
