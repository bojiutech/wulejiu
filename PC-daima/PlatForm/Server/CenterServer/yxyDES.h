/*----------------------------------------------------------------
            // Copyright (C) 2007 ��ѧԨ
            // ��Ȩ���С�
            //
            // �ļ�����yxyDES.cpp
            // �ļ�����������DES������ ͷ�ļ�
            //
            //
            // �����ˣ���ѧԨ
            //
            // �޸��ˣ�
            // �޸�������
            //
            // �޸��ˣ�
            // �޸�������
//----------------------------------------------------------------*/
//---------------------------------------------------------------------------

#ifndef yxyDESH
#define yxyDESH

#include <string>
#include <cmath>
#include <stdio.h>
#include <windows.h>
using namespace std;
class yxyDES
{
public:
         yxyDES(); //�๹�캯��
        ~yxyDES(); //����������
        //--------------------------------------------------------------
        void InitializeKey(string);
        //����:����16��28λ��key
        //����:Դ8λ���ַ���(key)
        //���:����������private CreateSubKey���������char SubKeys[16][48]
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        void EncryptData(string);
        //����:����8λ�ַ���
        //����:8λ�ַ���
        //���:���������ܺ��������private szCiphertext[16]
        //      �û�ͨ������Ciphertext�õ�
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        void DecryptData(string );
        //����:����16λʮ�������ַ���
        //����:16λʮ�������ַ���
        //���:���������ܺ��������private szPlaintext[8]
        //      �û�ͨ������Plaintext�õ�
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        void EncryptAnyLength(string);
        //����:�������ⳤ���ַ���
        //����:���ⳤ���ַ���
        //���:���������ܺ��������private szFCiphertextAnyLength[8192]
        //      �û�ͨ������CiphertextAnyLength�õ�
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        void DecryptAnyLength(string);
        //����:�������ⳤ��ʮ�������ַ���
        //����:���ⳤ���ַ���
        //���:���������ܺ��������private szFPlaintextAnyLength[4096]
        //      �û�ͨ������PlaintextAnyLength�õ�
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        void SetCiphertext(char* value);
        //Ciphertext��set����
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        char* GetCiphertext();
        //Ciphertext��get����
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        void SetPlaintext(char* value);
        //Plaintext��set����
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        char* GetPlaintext();
        //Plaintext��get����
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        char* GetCiphertextAnyLength();
        //CiphertextAnyLength��get����
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        char* GetPlaintextAnyLength();
        //PlaintextAnyLength��get����
        //--------------------------------------------------------------
private:
        //--------------------------------------------------------------
        char SubKeys[16][48];//����16��48λ��Կ
        char szCiphertext[16];//����16λ����(ʮ�������ַ���)
        char szPlaintext[8];//����8λ�����ַ���
        char szFCiphertextAnyLength[8192];//���ⳤ������(ʮ�������ַ���)
        char szFPlaintextAnyLength[4096];//���ⳤ�������ַ���
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        void CreateSubKey(char*);
        //����:��������Կ
        //����:����PC1�任��56λ�������ַ���
        //���:��������char SubKeys[16][48]
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        void FunctionF(char*,char*,int);
        //����:DES�е�F����,
        //����:��32λ,��32λ,key���(0-15)
        //���:���ڱ任����32λ
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        void InitialPermuteData(string,char*,bool);
        //����:IP�任
        //����:�������ַ���,�����������ָ��,����/����(true����,false����)
        //���:�����ı�ڶ�������������
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        void ExpansionR(char* ,char*);
        //����:����32λ������չλ48λ,
        //����:ԭ32λ�ַ���,��չ�������ָ��
        //���:�����ı�ڶ�������������
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        void XOR(char* ,char* ,int ,char*);
        //����:�����,
        //����:�����Ĳ����ַ���1,�ַ���2,����������,�����������ָ��
        //���: �����ı���ĸ�����������
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        string CompressFuncS(char* );
        //����:S-BOX , ����ѹ��,
        //����:48λ�������ַ���,
        //���:���ؽ��:32λ�ַ���
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        void PermutationP(string ,char*);
        //����:IP��任,
        //����:���任�ַ���,�����������ָ��
        //���:�����ı�ڶ�������������
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        string FillToEightBits(string);
        //����:�����Ĳ���8λ,ʹ��'$'�������,
        //����:ԭʼ�ַ���,
        //���:����8λ�ַ���
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        void CleanPlaintextMark(int);
        //������8λ����������Ĵ�����ԭ
        //����������szFPlaintextAnyLength
        //���: ����123$$$$$ �����󽫱�Ϊ 123'\0'
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        string HexCharToBinary(char);
        //����:16�����ַ�('0'-'F')��2�����ַ�����ת��
        //����:ʮ�������ַ�('0'-'F')
        //���:���ض������ַ���("0000"-"1111")
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        string HexIntToBinary(int );
        //����:16��������(0-15)��2�����ַ�����ת��
        //����:ʮ����������(0-15)
        //���:���ض������ַ���("0000"-"1111")
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        string BinaryToString(char*,int,bool);
        //����:�����ƴ����ַ�����ת��,
        //����:Դ�������ַ���,�������ַ�������,����(trueΪ�����Ƶ�hex,falseΪ�����Ƶ�ANSCII char),
        //���:���ش�������
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        int SingleCharToBinary(char);
        //����:����char '0'��'1' ��int 0��1�ı任
        //����: '0'��'1'
        //���:0��1
        //--------------------------------------------------------------

        //--------------------------------------------------------------
        char SingleBinaryToChar(int);
        //����:��int���͵�0��1ת��Ϊchar���͵�0��1
        //����:0��1
        //����:'0'��'1'
        //--------------------------------------------------------------
};

//---------------------------------------------------------------------------
#endif
 