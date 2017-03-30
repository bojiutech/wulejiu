// RecordPlayer.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "RecordPlayer.h"
#include "RecordPlayerDlg.h"

#include "BzCrashRpt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRecordPlayerApp

BEGIN_MESSAGE_MAP(CRecordPlayerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CRecordPlayerApp ����

CRecordPlayerApp::CRecordPlayerApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CRecordPlayerApp ����

CRecordPlayerApp theApp;


// CRecordPlayerApp ��ʼ��

BOOL CRecordPlayerApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	// ��ʼBzCrashRpt
	BzCrash_Initiation();
	BzCrash_DisableSetUnhandledExceptionFilter();
	BzCrash_SetProjectName("Dƽ̨¼���");
	BzCrash_SetEmailSender("bzbugrev@sina.com");
	BzCrash_SetEmailReceiver("bzbugrev@sina.com");
	BzCrash_SetSmtpServer("smtp.sina.com");
	BzCrash_SetSmtpUser("bzbugrev");
	BzCrash_SetSmtpPassword("1122334455");
	BzCrash_DeleteSended(false);


	//yjj Ҫ����������ܳ���
	AfxOleInit( );
	AfxInitRichEdit(); 


	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));


	//LPWSTR str = GetCommandLineArgs();
	TCHAR filename[1000];
	memset(filename,0,sizeof(filename));
	int iLen = 1000;
	GetFileName(filename,iLen);

	
	

	//����ļ���������	
    TCHAR* szFilen = NULL;
	if (iLen > 0)
	{
		szFilen = filename;
	}

	CRecordPlayerDlg dlg(szFilen,NULL);
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
		//  �Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//  �Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

void CRecordPlayerApp::GetFileName(TCHAR* filename,int& iLen)
{

	TCHAR  strFileName[1000]   ;   
	memset(strFileName,0,sizeof(strFileName));   
	GetModuleFileName(NULL,strFileName,1000);
	RegisterFile(strFileName);

	
	
	if (filename == NULL)
	{
		return;
	}
	LPCSTR str = GetCommandLine();	
	int istrLen = strlen(str);
    int iAppStrlen = strlen(strFileName);

	if (istrLen <= iAppStrlen + 3)
	{
		iLen = 0;
		return;
	}


	//memset(filename,0,iLen)


	LPCSTR strname = str + iAppStrlen + sizeof(TCHAR) + 2;// * 2;


	if (strname == NULL)
	{
		return;
	}
	strcpy(filename,strname);
	iLen = strlen(filename);

	
	//for (int i=0; i<iLen; i++)
	//{
	//	if (str[i] == TEXT("\""))
	//	{
	//		str += i;
	//		break;
	//	}
	//}

	//ParamStr(1)



}

//���ļ��Ϳ�ִ�г����������
void   CRecordPlayerApp::RegisterFile(CString   strFileName)   
{   

	CString   strKey,   strKeyValue   ;   
	HKEY   hKey   ;   

	strKey   =   CString(".zxh")   ;   
	strKeyValue   =   CString("ZXHFILE")   ;   

	RegCreateKey(HKEY_CLASSES_ROOT,strKey,&hKey)   ;   
	RegSetValue(HKEY_CLASSES_ROOT,strKey,REG_SZ,strKeyValue,strKeyValue.GetLength())   ;   


	strKey   =   CString("ZXHFILE")   ;   
	strKeyValue   =   CString("ZXHPLAYFILE")   ;   

	RegCreateKey(HKEY_CLASSES_ROOT,strKey,&hKey)   ;   
	RegSetValue(HKEY_CLASSES_ROOT,strKey,REG_SZ,strKeyValue,strKeyValue.GetLength())   ;   


	HKEY   hSubKey  ;   
	strKeyValue   =   strFileName   ;   
	RegCreateKey(hKey,TEXT("Shell\\Open\\Command"),&hSubKey)   ;   
	RegSetValue(hKey,TEXT("Shell\\Open\\Command"),REG_SZ,strKeyValue + TEXT(" %1"),strKeyValue.GetLength())   ;   


 //   //���������  
	//string   keyName;   
	//string   keyValue;   
	////This   creates   a   Root   entry   called   "MyApp".   
	//keyName   =   "MyApp";   
	//keyValue   =   "My   Application";   

	//RegistryKey   key;   
	//key   =   Registry.ClassesRoot.CreateSubKey(keyName);   
	//key.SetValue("",keyValue);   
	//key   =   key.CreateSubKey("shell");   
	//key   =   key.CreateSubKey("open");   
	//key   =   key.CreateSubKey("command");   
	//key.SetValue("","c:\\temp\\my.exe   %1");   

	//keyName   =   ".bar";   
	//keyValue   =   "MyApp";   
	//key   =   Registry.ClassesRoot.CreateSubKey(keyName);   
	//key.SetValue("",   keyValue);   
}   



//void __fastcall RegisterFileRelation(CString ExtName, CString AppName,CString AppKey, CString Icon, CString Describe)
//{
//	try
//	{
//		TRegistry *pReg = new TRegistry();pReg->RootKey = HKEY_CLASSES_ROOT; 
//// ������// �½�/�����ļ���չ��Ϊ�������д������
//		pReg->OpenKey(ExtName, true);
//		pReg->WriteString("", AppKey);
//		pReg->CloseKey();
//		pReg->OpenKey(AppKey, true);
//		pReg->WriteString("", Describe);
//		pReg->CloseKey();
//		pReg->OpenKey(AppKey + "\DefaultIcon", true);
//		pReg->WriteString("", Icon);
//		pReg->CloseKey();
//		pReg->OpenKey(AppKey + "\Shell", true);
//		pReg->WriteString("", "Open");
//		pReg->CloseKey();
//		pReg->OpenKey(AppKey + "\Shell\Open\Command", true);
//		pReg->WriteString("", AppName + " %1");pReg->CloseKey();
//		delete pReg;
//	}
//	catch(...)
//	{
//		MessageBox(NULL, "ע���ļ�����ʱ��������", "ע��", MB_OK|MB_ICONWARNING);
//	}
//} 
