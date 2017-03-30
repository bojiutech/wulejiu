/*if exists (select * from dbo.sysobjects where id = object_id(N'[dbo].[RecommendTable]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [dbo].[RecommendTable]
GO

CREATE TABLE [dbo].[RecommendTable] (
	[id] [int] NULL ,
	[UserID] [int] NULL ,
	[RecommendID] [int] NULL 
) ON [PRIMARY]
GO*/

#include "StdAfx.h"
#include "UserCustomLogo.h"
#include "GameLogonManage.h"
#include "MD5.h"

CUserCustomLogo::~CUserCustomLogo(void)
{
}

/*
Function	:OnNetMessage
Notes		:������Ϣ
Author		:Fred Huang
Date		:2008-03-18
Parameter	:
	NetMessageHead	:������Ϣͷ
	void *			:����ָ��
	UINT			:���ݰ��Ĵ�С
	UING			:δʹ�ã�ԭָIP��ַ
	UINT			:�ͻ��ڷ�������SOCKET����
return		:void
*/
void CUserCustomLogo::OnNetMessage(NetMessageHead * pNetHead, void * pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	if(pNetHead->bMainID!=MDM_GR_USER_LOGO)
		return;
	switch(pNetHead->bAssistantID)
	{
	case ASS_ULC_UPLOAD:			//�ϴ��ļ������յ�������Ҳ����������
		OnUploadFace(pData,uSize,uIndex,dwHandleID);
		break;
	case ASS_ULC_INFOREQUEST:		//�ͻ��������û���ͷ����Ϣ
		OnRequestLogoInformation(pData,uSize,uIndex,dwHandleID);
		break;
	case ASS_ULC_DOWNREQUEST:		//��������ĳ���û���ͷ���ļ�
		OnDownloadRequest(pData,uSize,uIndex,dwHandleID);
		break;	
	case ASS_ULC_DOWNRESULT:		//�������صĽṹ����ʵ��ֻ����������һ�����ݿ�
		OnDownloadResult(pData,uSize,uIndex,dwHandleID);
		break;
	}
}

/*
Function	:OnUploadFace
Notes		:���յ��ϴ��ļ����ݰ����ֿ��ϴ�
Author		:Fred Huang
Date		:2008-03-18
Parameter	:
	void *			:����ָ��
	UINT			:���ݰ��Ĵ�С
	UINT			:�ͻ��ڷ�������SOCKET����
	UINT			:δ֪
return		:void
*/
void CUserCustomLogo::OnUploadFace(void *pData,UINT uSize,UINT uIndex,DWORD dwHandleID)
{
	//������С
	if(sizeof(MSG_UL_C_UPLOAD)!=uSize)
		return;
	//ȡ������
	CGameLogonManage *pWnd=(CGameLogonManage*)pParentWnd;
	
	MSG_UL_C_UPLOAD *msg=(MSG_UL_C_UPLOAD*)pData;
	long dwUserID=msg->dwUserID;
	
	//�����û�ID������Ŀ¼��ÿ���û���һ��Ŀ¼
	CString savePath;
	savePath.Format("%s\\%d",pWnd->m_CustomFacePath,dwUserID/1000);
	::CreateDirectory(savePath,NULL);
	savePath.Format("%s\\%d",pWnd->m_CustomFacePathUpload,dwUserID/1000);
	::CreateDirectory(savePath,NULL);

	//Ҫ������ļ���
	savePath.Format("%s\\%d\\%d.png",pWnd->m_CustomFacePathUpload,dwUserID/1000,dwUserID);
	//����ǵ�һ�����ݰ���Ҫ�����ļ�������ֻд
	UINT dwFlag=CFile::modeWrite;
	if(msg->nBlockIndex==0)
		dwFlag|=CFile::modeCreate;

	//Ҫ���ص���Ϣ��ֻ�������ݿ�������Ϳ���
	MSG_UL_S_UPLOADRESULT resultMsg;
	ZeroMemory(&resultMsg,sizeof(MSG_UL_S_UPLOADRESULT));
	resultMsg.dwUserID=dwUserID;
	resultMsg.nBlockCount=msg->nBlockCount;
	resultMsg.nBlockIndex=msg->nBlockIndex;
	resultMsg.bNeedCheck=pWnd->m_bCustomFaceNeedCheck;
	try
	{
		//д���ļ�
		CFile fw(savePath,dwFlag);
		fw.Seek(msg->nBlockIndex*512,CFile::begin);
		fw.Write(msg->szData,msg->nPackageSize);
		fw.Close();
	}
	catch (...) 
	{//д�ļ�ʧ��
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
		pWnd->m_TCPSocket.SendData(uIndex,&resultMsg,sizeof(MSG_UL_S_UPLOADRESULT),MDM_GR_USER_LOGO,ASS_ULS_UPLOADFAILED,dwHandleID,0);
		return;
		
	}

	//������Ϣ
	pWnd->m_TCPSocket.SendData(uIndex,&resultMsg,sizeof(MSG_UL_S_UPLOADRESULT),MDM_GR_USER_LOGO,ASS_ULS_UPLOADSUCCEED,dwHandleID,0);
	TRACE("Receive Custom Logo File %d of %d at %s\n",msg->nBlockIndex,msg->nBlockCount,savePath);

	//�ļ��ϴ���ɵĲ�����ע�⣬nBlockIndex�Ǵӿ�ʼ�ģ�����nBlockCount-1�������һ������
	if(msg->nBlockIndex==msg->nBlockCount-1)
	{
		//�����ļ���MD5ֵ
		MD5_CTX md5;
		CFile fr(savePath,CFile::modeRead);
		int len=fr.GetLength();
		byte *buf=new byte[len+1];
		ZeroMemory(buf,len+1);
		fr.Read(buf,len);
		fr.Close();
		md5.MD5Update(buf,len);
		byte *md5buf=new byte[16];
		ZeroMemory(md5buf,16);

		md5.MD5Final(md5buf);
		CString strmd5="",szChar;
		for(int i=0;i<16;i++)
		{
			szChar.Format("%2x",md5buf[i]);
			strmd5+=szChar;
		}
		delete md5buf;
		delete buf;

		//�������ݿ�
		UL_GP_I_UpdateUserLogo UL_Update;
		ZeroMemory(&UL_Update,sizeof(UL_GP_I_UpdateUserLogo));
		UL_Update.dwUserID=dwUserID;
		if(pWnd->m_bCustomFaceNeedCheck)
			UL_Update.nIconIndex=0x200+msg->dwUserSourceLogo;
		else
			UL_Update.nIconIndex=0x100+msg->dwUserSourceLogo;
		memcpy(UL_Update.szLogoMD5,strmd5,32);
		pWnd->m_SQLDataManage.PushLine(&UL_Update.DataBaseHead,sizeof(UL_GP_I_UpdateUserLogo),DTK_GP_USERLOGO_UPDATE,uIndex,0);
		TRACE("Receive Custom Logo Completed\n");
		//���������
	}
}

/*
Function	:OnRequestLogoInformation
Notes		:����ĳ���û���ͷ���ļ���Ϣ
Author		:Fred Huang
Date		:2008-03-18
Parameter	:
	void *			:����ָ��
	UINT			:���ݰ��Ĵ�С
	UINT			:�ͻ��ڷ�������SOCKET����
	UINT			:δ֪
return		:void
*/
void CUserCustomLogo::OnRequestLogoInformation(void * pData, UINT uSize, UINT uIndex, DWORD dwHandleID)
{

	if(sizeof(MSG_UL_C_INFORREQUEST)!=uSize)
		return;
	MSG_UL_C_INFORREQUEST * msg=(MSG_UL_C_INFORREQUEST*)pData;

	//��Ҫ�����ݿ��ѯ���������´����ǽ���һ�����ݿ��ѯ�����󣬲����������
	UL_GP_I_RequestInformationLogoMD5 UL_LogoMD5;
	ZeroMemory(&UL_LogoMD5,sizeof(UL_GP_I_RequestInformationLogoMD5));
	UL_LogoMD5.dwUserID=msg->dwUserID;
	UL_LogoMD5.dwRequestUserID=msg->dwRequestUserID;
	CGameLogonManage *pWnd=(CGameLogonManage*)pParentWnd;
	pWnd->m_SQLDataManage.PushLine(&UL_LogoMD5.DataBaseHead,sizeof(UL_GP_I_RequestInformationLogoMD5),DTK_GP_USERLOGO_GETMD5,uIndex,0);
}

/*
Function	:OnDownloadRequest
Notes		:��������ͷ���ļ�
Author		:Fred Huang
Date		:2008-03-18
Parameter	:
	void *		:����ָ��
	UINT		:���ݰ��Ĵ�С
	UINT		:�ͻ��ڷ�������SOCKET����
	UINT		:δ֪
return		:void
*/
void CUserCustomLogo::OnDownloadRequest(void* pData, UINT uSize, UINT uIndex, DWORD dwHandleID)
{
	if(sizeof(MSG_UL_C_DOWNREQUEST)!=uSize)
		return;
	MSG_UL_C_DOWNREQUEST *msg=(MSG_UL_C_DOWNREQUEST *)pData;
	//��ʼ���ص�һ������
	downloadCustomFace(msg->dwRequestUserID,0,uIndex,dwHandleID);
}

/*
Function	:downloadCustomFace
Notes		:��ȡͷ���ļ�����������Ŀͻ���
Author		:Fred Huang
Date		:2008-03-18
Parameter	:
	long		:�û���ID�ţ��Ǳ��������ص��û�ID��
	long		:���ݿ������
	UINT		:�ͻ��ڷ�������SOCKET����
	DWORD		:δ֪
return		:void
*/
void CUserCustomLogo::downloadCustomFace(long dwUserID, long nBlockIndex, UINT uIndex, DWORD dwHandleID)
{
	//ȡ������ָ��
	CGameLogonManage *pWnd=(CGameLogonManage*)pParentWnd;
	//����ͷ���ļ���
	CString logoFile;
	logoFile.Format("%s\\%d\\%d.png",pWnd->m_CustomFacePath,dwUserID/1000,dwUserID);
	//��ѯ�ļ��Ƿ����
	CFileFind ff;
	BOOL bFoundFile=ff.FindFile(logoFile);
	ff.Close();
	if(!bFoundFile)
		return;
	//��ȡ�ļ��飬ÿ�����СΪ
	char buf[513]={0};					//��һ���ֽ�
	CFile fr(logoFile,CFile::modeRead);
	int filelen=fr.GetLength();			//�ļ���С
	int packagesize=512;				//���ݿ��С
	if(nBlockIndex*512>filelen)			//�Ƿ񳬳����ļ��Ľ�β
	{
		fr.Close();
		return;
	}
	if(nBlockIndex*512+packagesize>filelen)		//���һ���С�Ƿ񳬳����ļ��Ľ�β
		packagesize=filelen-nBlockIndex*512;	//�����С������

	fr.Seek(nBlockIndex*512,CFile::begin);		//�ļ���λ
	fr.Read(buf,packagesize);					//������
	fr.Close();									//�ر��ļ�

	//������ݽṹ
	MSG_UL_S_DOWN msg;
	ZeroMemory(&msg,sizeof(MSG_UL_S_DOWN));
	msg.dwUserID=dwUserID;							//�û�ID
	msg.nBlockIndex=nBlockIndex;					//���ݿ�����
	msg.nBlockSize=512;								//���ݿ��С
	msg.nPackageSize=packagesize;					//���ݰ��Ĵ�С
	msg.nFileSize=filelen;							//�ļ���С
	msg.nBlockCount=(filelen-1)/512+1;				//���ݿ�����
	memcpy(msg.szData,buf,packagesize);				//����

	//��������
	pWnd->m_TCPSocket.SendData(uIndex,&msg,sizeof(MSG_UL_S_DOWN),MDM_GR_USER_LOGO,ASS_ULS_DOWN,dwHandleID,0);

}
/*
Function	:OnDownloadResult
Notes		:�ͻ��˷����˽������ݰ��Ľ������ʵ�ϣ��ͻ���ֻ���ڽ��ճɹ��˲Żᷢ����
Author		:Fred Huang
Date		:2008-03-18
Parameter	:
	void *		:����ָ��
	UINT		:���ݰ��Ĵ�С
	UINT		:�ͻ��ڷ�������SOCKET����
	UINT		:δ֪
return		:void
*/
void CUserCustomLogo::OnDownloadResult(void * pData, UINT uSize, UINT uIndex, DWORD dwHandleID)
{
	if(sizeof(MSG_UL_C_DOWNRESULT)!=uSize)
		return;
	MSG_UL_C_DOWNRESULT *msg=(MSG_UL_C_DOWNRESULT *)pData;
	//msg->nBlockIndex������ݿ��ѳɹ����ͣ����Է�����һ�����ݿ�
	msg->nBlockIndex++;
	downloadCustomFace(msg->dwUserID,msg->nBlockIndex,uIndex,dwHandleID);// msg->dwRequestUserID,0,uIndex,dwHandleID);
}

