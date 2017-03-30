#pragma once

#ifndef AFCDATABASE_H_FILE_2003_07
#define AFCDATABASE_H_FILE_2003_07

#include "StdAfx.h"
#include <afx.h>
#include <afxdisp.h>
#include <Icrsint.h>
#include "ComStruct.h"
#include "AFCInterFace.h"
#include "AFCLock.h"
#include "DataLine.h"
#include "AFCException.h"

#pragma warning (disable: 4146)
#import "MsAdo15.dll" rename_namespace("ADOCG") rename("EOF","EndOfFile")
using namespace ADOCG;

//���Ͷ���
typedef	_com_error CComError;

//��˵��
class CDataLine;
class CAFCRecord;
class CAFCDataBase;
class CAFCDataBaseManage;

//���ݿ�����
const TCHAR		szCenterDataBaseName[]=TEXT("AFCDataCenter");	//�����������ݿ�����
const TCHAR		szLogonDataBaseName[]=TEXT("AFCUsers");			//��½�������ݿ�����
const TCHAR		szNativeDataBaseName[]=TEXT("AFCLocal");		//���ػ������ݿ�����

//�������ݱ�
//const TCHAR		szBufferPoint[]=TEXT("BufferPoint");				//���������
//const TCHAR		szBufferExperience[]=TEXT("BufferExperience");		//���黺���

//����ʹ�ñ�
const TCHAR		szLogonTable[]=TEXT("Users");					//��½�û���
const TCHAR		szIPRuleTable[]=TEXT("GameIPRule");					//IP �������Ʊ�
const TCHAR		szLogonMoney[]=TEXT("ComLogonMoney");				//�������Ϸ״̬��Ϣ��
const TCHAR		szMatchUserInfo[]=TEXT("MatchUserInfo");			//������Ϣ��


//static CString stc_sCenterDataConnect="Data Source=TML";
//static CString stc_sLogonDataConnect="Data Source=TML";
//static CString stc_sNativeConnect="Data Source=TML";////"Data Source=AFCLocal";
static CString stc_sCenterDataConnect="FILE NAME=bzgame.udl";
static CString stc_sLogonDataConnect="FILE NAME=bzgame.udl";
static CString stc_sNativeConnect="FILE NAME=bzgame.udl";////"Data Source=AFCLocal";

const bool stc_bUseACCESSDb=true;
const bool stc_bUseODBCConnect=true;

//***********************************************************************************************//


//���ݿ���
class EXT_CLASS CAFCDataBase
{
	friend class CAFCRecord;

	//��������
private:
	//bool								m_bShowError;				//�Ƿ���ʾ����
	///_ConnectionPtr						m_pConnection;				//���ݿ�ʵ��
	
	//��������
public:
	//���캯��
	CAFCDataBase(void);
	//��������
	virtual ~CAFCDataBase(void);

	//���ܺ���
public:
	//����ģʽ
	bool ShowError(bool bShowError);
	//�Ƿ��
	bool IsOpen();
	//������
	bool Open(const TCHAR * pszConnection);
	//�ر�����
	bool Close();
	//ִ�����
	bool Execute(const TCHAR * szSQL);
	//ִ�����
	bool Execute(const TCHAR * szSQL, HRESULT & hResult);

	//�ڲ�����
private:
	//�������
	void ShowErrorMessage(CComError & ADOError);
};

//***********************************************************************************************//

//���ݼ���
class EXT_CLASS CAFCRecord
{
	//��������
private:
	bool						m_bShowError;				//�Ƿ���ʾ����
	_RecordsetPtr				m_pRecordset;				//��¼ʵ��
	CAFCDataBase				* m_pDataConnect;			//��������

	//��������
public:
	//���캯��
	CAFCRecord(CAFCDataBase * ADODataBase);
	//��������
	virtual ~CAFCRecord(void);

	//��������
protected:
	//�������
	void ShowErrorMessage(CComError &ADOError);

	//���ܺ���
public:
	//����ģʽ
	bool ShowError(bool bShowError);
	//��ȡ��¼����Ŀ
	DWORD GetRecordCount();
	//ִ�в�ѯ
	bool Open(const TCHAR * szSQL);
	//ִ�в�ѯ
	bool Open(const TCHAR * szSQL, HRESULT & hResult);
	//�ر����ݼ�
	bool Close();
	//�Ƿ��¼��δ
	bool IsEnd() { return (m_pRecordset->EndOfFile==VARIANT_TRUE); };
	//�ƶ�����һ��
	void MoveNext() { m_pRecordset->MoveNext(); }
	//��ȡ����
	bool GetFieldValue(LPCTSTR lpFieldName, BYTE & bValue);
	//��ȡ����
	bool GetFieldValue(LPCTSTR lpFieldName, int & nValue);
	//��ȡ����
	bool GetFieldValue(LPCTSTR lpFieldName, long & lValue);
	//��ȡ����
	bool GetFieldValue(LPCTSTR lpFieldName, unsigned long & ulValue);
	//��ȡ����
	bool GetFieldValue(LPCTSTR lpFieldName, UINT & ulValue);
	//��ȡ����
	bool GetFieldValue(LPCTSTR lpFieldName, __int64 & llValue);
	//��ȡ����
	bool GetFieldValue(LPCTSTR lpFieldName, double & dbValue);
	//��ȡ����
	bool GetFieldValue(LPCTSTR lpFieldName, TCHAR szBuffer[], UINT uSize);
	//��ȡ����
	bool GetFieldValue(LPCTSTR lpFieldName, COleDateTime & Time);
	//��ȡ����
	bool GetFieldValue(LPCTSTR lpFieldName, bool & bValue);
};

//***********************************************************************************************//

//���ݿ����ݰ�ͷ�ṹ
struct DataBaseLineHead
{
	DataLineHead					DataLineHead;							//����ͷ
	UINT							uHandleKind;							//��������
	UINT							uIndex;									//��������
	DWORD							dwHandleID;								//�����ʶ
};

//���ݿ⴦����
class EXT_CLASS CAFCDataBaseManage
{
	//��������
protected:
	bool							m_bInit;								//��ʼ����־
	bool							m_bRun;									//���б�־
	IDataBaseHandleService			* m_pHandleService;						//���ݴ���ӿ�

	//��������
public:
	CAFCDataBase					m_DataBaseCenter;						//�������ݿ�
	CAFCDataBase					m_DataBaseLogon;						//��½���ݿ�
	CAFCDataBase					m_DataBaseNative;						//�������ݿ�

	//��Ϣ����
public:
	KernelInfoStruct				* m_pKernelInfo;						//�ں�����
	ManageInfoStruct				* m_pInitInfo;							//��ʼ������ָ��

	//��Ϣ����
protected:
	CString							m_strLogonDataConnect;					//��½�ַ���
	CString							m_strNativeDataConnect;					//�����ַ���
	CString							m_strCenterDataConnect;					//�����ַ���

	//�ں˱���
protected:
	HANDLE							m_hThread;								//�߳̾��
	HANDLE							m_hCompletePort;						//��ɶ˿�
	CDataLine						m_DataLine;								//���ݶ���

	//��������
public:
	//���캯��
	CAFCDataBaseManage();
	//��������
	virtual ~CAFCDataBaseManage(void);

	//������
public:
	//��ʼ������
	bool Init(ManageInfoStruct * pInitInfo, KernelInfoStruct * pKernelInfo, IDataBaseHandleService * pHandleService,IDataBaseResultService * pResultService);
	//ȡ����ʼ��
	bool UnInit();
	//��ʼ����
	bool Start();
	//ֹͣ����
	bool Stop();
	//���봦�����
	bool PushLine(DataBaseLineHead * pData, UINT uSize, UINT uHandleKind, UINT uIndex,DWORD dwHandleID);

	//���ܺ���
public:
	//�����������
	bool CheckSQLConnect();

	//�ڲ�����
private:
	//���ݿ⴦���߳�
	static unsigned __stdcall DataServiceThread(LPVOID pThreadData);
	//��־���ݿ⴦���߳�
	static unsigned __stdcall DataLogThread(LPVOID pThreadData);
};

//***********************************************************************************************//

//���ݿ⴦��ӿ���
class EXT_CLASS CDataBaseHandle : public IDataBaseHandleService
{
	//��������
protected:
	KernelInfoStruct						* m_pKernelInfo;				//�ں�����
	ManageInfoStruct						* m_pInitInfo;					//��ʼ������ָ��
	IDataBaseResultService					* m_pRusultService;				//�������ӿ�
	CAFCDataBaseManage						* m_pDataBaseManage;			//���ݿ����

	//��������
public:
	//���캯��
	CDataBaseHandle(void);
	//��������
	virtual ~CDataBaseHandle(void);

	//�ӿں���
public:
	//���ò���
	virtual bool SetParameter(IDataBaseResultService * pRusultService, CAFCDataBaseManage * pDataBaseManage, ManageInfoStruct * pInitData, KernelInfoStruct * pKernelData);

	//���ܺ���
public:
	//�Ƿ��ֻ�����
	bool IsMobileNum(TCHAR * szChar);
};

//***********************************************************************************************//

#endif