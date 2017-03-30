/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #pragma once

//#include "mj.h"
//#include "../ChangeFile/UpgradeMessageEx.h"

//�����߼����߼��� 
//�������ݻ�������������ɾ������ѯ��
class CLogicBase
{
public:
	CLogicBase(void);
	~CLogicBase(void);

public:

	///���������һ������
	///@param  arr[] ����, data Ҫ��ӵ�����, ArrLen ����ĳ���
	///@return true ��ӳɹ���false �������ˣ���Ӳ��ɹ�
	static bool AddOneDataToArr(BYTE arr[],BYTE data,BYTE ArrLen)
	{
		for(int i=0;i<ArrLen;i++)
		{
			if(arr[i]==255)
			{
				arr[i] = data;
				return true;
			}
		}
		return false;
	}

	///��������ɾ��һ������
	///@param  arr[] ����, data Ҫɾ��������, ArrLen ����ĳ���
	///@return true ��ӳɹ���false �������ˣ���Ӳ��ɹ�
	static bool DeleteOneDataFromArr(BYTE arr[],BYTE data,BYTE ArrLen)
	{
		for(int i=0;i<ArrLen;i++)
		{
			if(arr[i]==data)
			{
				arr[i] = 255;
				return true;
			}
		}
		return false;
	}

	///��ȡ��ɫ�ӵ��������
	///@param  data0 ɫ��1, data1 ɫ��2, data2 ɫ��3
	static void GetSeziData(BYTE *data0 = NULL, BYTE *data1 = NULL, BYTE *data2 = NULL)
	{
		srand((unsigned)time(NULL));
		if(data0 != NULL)
		{
			*data0 = rand()%6+1;
		}
		if(data1 != NULL)
		{
			Sleep(50);
			*data1 = rand()%6+1;
		}
		if(data2 != NULL)
		{
			Sleep(50);
			*data2 = rand()%6+1;
		}
	}
	
	///��ȡ�������ЧԪ�ظ���
	///@param  arr[] Ŀ������,data ��Чֵ, ArrLen ���鳤��
	///@return ��ЧԪ�ظ���
	static int GetArrInvalidNum(BYTE arr[],BYTE data,BYTE ArrLen)
	{
		int num = 0;
		for(int i=0;i<ArrLen;i++)
		{
			if(arr[i] != data)
			{
				num++;
			}
		}
		return num;
	}

	///�ж��������Ƿ����ĳ��Ԫ��
	///@param  arr[] Ŀ������,data ��Чֵ, ArrLen ���鳤��
	///@return ��ЧԪ�ظ���
	static bool IsHaveInArr(BYTE arr[],BYTE data,BYTE ArrLen)
	{
		for(int i=0;i<ArrLen;i++)
		{
			if(arr[i] == data)
			{
				return true;
			}
		}
		return false;
	}
	///�ж��������Ƿ����ĳ��Ԫ��
	///@param  arr[] Ŀ������,data Ҫ���ҵ�Ԫ��, ArrLen ���鳤��
	///@return ��ЧԪ�ظ���
	static int GetNumInArr(BYTE arr[],BYTE data,BYTE ArrLen)
	{
		int num =0;
		for(int i=0;i<ArrLen;i++)
		{
			if(arr[i] == data)
			{
				num++ ;
			}
		}
		return num;
	}


};
