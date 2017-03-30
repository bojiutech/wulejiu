// SmsTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "../sdk/SmsIf.h"

//dllģ���
std::map<UINT,HMODULE> g_MuduleMap;

//��dllģ����ѯģ����
HMODULE ModuleGetFromMap(UINT);

//��ģ����ȡ������ӿ�
HRESULT ModuleCreateInstance(UINT,char*,LPVOID FAR**);
HRESULT ModuleCreateInstance(UINT,REFCLSID,char*,LPVOID FAR**);


int _tmain(int argc, _TCHAR* argv[])
{
//�������ģ��------------------------------------------------------------------------

	HMODULE hModual = NULL;
	g_MuduleMap.clear();

	//�������������ļ�����ģ��
	hModual = ::LoadLibrary(_TEXT("Sms.dll"));
	g_MuduleMap.insert(std::pair<UINT,HMODULE>(MODUAL_PLUGIN_Z_SMS,hModual));

//end--------------------------------------------------------------------------------

	HRESULT hr = NULL;

	IMobile* pIMobile = NULL;
	//�ֻ���ѯ�ӿ�
	hr = ::ModuleCreateInstance(MODUAL_PLUGIN_Z_SMS,_T("CreateMobileObject"),(LPVOID FAR**)&pIMobile);

	if (hr != S_OK)
	{
		cout<<"Load Sms.dll fail."<<endl;
	}

	ISms* pISms = NULL;
	//SMSģ��ӿ�
	hr = ::ModuleCreateInstance(MODUAL_PLUGIN_Z_SMS,CLSID_ZServ_Sms,\
		_T("CreateSmsObject"),(LPVOID FAR**)&pISms);

	if (hr != S_OK)
	{
		cout<<"Load Sms.dll fail."<<endl;
	}
	
	

	while(true)
	{
		char szPhoneNo[20] = {0};
		char szUserID[32] = {0};
		char szMessage[128] = {0};
		cout<<"Phone No: ";
		cin>>szPhoneNo;

		if (::strcmp(szPhoneNo,_T("exit")) == 0)
		{
			break;
		}

		if (pIMobile)
		{
			char szResult[128] = {0};
			hr = pIMobile->GetCodeInfo(szPhoneNo,_T(""),szResult);
			if (S_OK == hr)
			{
				cout<<"===================================================================\n";
				cout<<szResult<<endl;
				cout<<"===================================================================\n";
			}
		}

		cout<<"Message: ";
		cin>>szMessage;

		if (!pISms)
		{
			cout<<"Create SMS object fail."<<endl;
			return 0;
		}

		if (!pIMobile)
		{
			cout<<"Create Mobile object fail."<<endl;
		}

		hr = pISms->SendMessage(szPhoneNo,szMessage);

		if (hr == S_OK)
		{
			cout<<"SMS Sent success!"<<endl<<endl;
		}
		else
		{
			cout<<"Send SMS fail."<<endl;
		}
	}

	if (pIMobile)
	{
		pIMobile->ReleaseObject();
	}

	if (pISms)
	{
		pISms->ReleaseObject();
	}

//�ͷ����ģ��------------------------------------------------------------------------

	std::map<UINT,HMODULE>::iterator itMMap = g_MuduleMap.begin();
	for (;itMMap != g_MuduleMap.end(); itMMap++)
	{
		if (itMMap->second)
		{
			::FreeLibrary(itMMap->second);
		}
	}

//end--------------------------------------------------------------------------------

	return 0;
}

//��dllģ����ѯģ����
HMODULE ModuleGetFromMap(UINT uModualID)
{
	std::map<UINT,HMODULE>::iterator itMMap = g_MuduleMap.find(uModualID);
	return (HMODULE)itMMap->second;
}

//��ģ����ȡ������ӿ�

HRESULT ModuleCreateInstance(UINT uModualID,char* szCreateFunName,LPVOID FAR** ppv)
{
	typedef HRESULT (*func_ptr)(LPVOID FAR**);
	HMODULE hModule = ModuleGetFromMap(uModualID);
	if (hModule)
	{
		func_ptr lpFunc = (func_ptr)::GetProcAddress(hModule,szCreateFunName);
		if (lpFunc)
		{
			return lpFunc(ppv);
		}
	}

	return S_FALSE;
}

HRESULT ModuleCreateInstance(UINT uModualID,REFCLSID rclsid,char* szCreateFunName,LPVOID FAR** ppv)
{
	typedef HRESULT (*func_ptr)(REFCLSID,LPVOID FAR**);
	HMODULE hModule = ModuleGetFromMap(uModualID);
	if (hModule)
	{
		func_ptr lpFunc = (func_ptr)::GetProcAddress(hModule,szCreateFunName);
		if (lpFunc)
		{
			return lpFunc(rclsid,ppv);
		}
	}

	return S_FALSE;
}