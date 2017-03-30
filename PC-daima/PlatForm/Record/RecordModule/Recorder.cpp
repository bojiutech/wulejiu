#include "StdAfx.h"
#include "Recorder.h"
#include "MD5.h"

CRecorder::CRecorder(void)
{
	m_arryMsgList.reserve(50);
	//m_arryMsgList.resize(100);
	m_bEnable = true;
	InitAll();  //��ʼ�����б���

	m_uMsgRecTime = GetTickCount();
//	m_pMsgBuffer = NULL;
	
}

CRecorder::~CRecorder(void)
{
	ClearAllMsg();
}
//*********************************************************
//ƽ̨�ӿ�
void CRecorder::AddUserInfo(RecordUserItemStruct* pUsrIterInfo)
{
	//����Ҹ�ֵ
	if (pUsrIterInfo == NULL)
	{
		return;
	}
	if (pUsrIterInfo->GameUserInfo.bDeskStation >= MAX_PLAYER_COUNT)
	{
		return;
	}
	if (m_FileHead.UsrInfoStruct[pUsrIterInfo->GameUserInfo.bDeskStation].GameUserInfo.dwUserID != pUsrIterInfo->GameUserInfo.dwUserID)
	{
		m_FileHead.uPlayerCount++;  //�����������
	}
	memcpy(&m_FileHead.UsrInfoStruct[pUsrIterInfo->GameUserInfo.bDeskStation],pUsrIterInfo,sizeof(RecordUserItemStruct));
	


}
void CRecorder::AddMeDeskStation(BYTE bDeskStation)
{
	if (bDeskStation >= MAX_PLAYER_COUNT)
	{
		return;
	}
	//m_bMyDeskStation = bDeskStation;
	m_FileHead.bMyDeskStation = bDeskStation;
	m_FileHead.RoomGameInfo.bMeDeskStation = bDeskStation;

}
/**
* �����Ϸ������Ϣ
*/
void CRecorder::AddRoomGameInfo(RecordGameInfoStruct* pGameInfo)
{
	if (pGameInfo == NULL)
	{
		return;
	}
	memcpy(&m_FileHead.RoomGameInfo,pGameInfo,sizeof(RecordGameInfoStruct));
}
/**
* ����������Ϣ���������Ϸ��Ϣ����û��ò����������������Щ��Ϣ�����������Ǵ����˶�������Ϊ������Ϣ����ʼ��
* ���ô���socket������������Ӧ���ǲ�֧�����������Ϣ��
*/
bool CRecorder::AddMsg2Record(void* pNetHead,UINT uHeadSize,void * pNetData, UINT uDataSize)
{
	//����Ϣ�������뱾�������Ӧ��ֻ������
	if (uHeadSize > MAX_MSG_HEAD_LEN || uDataSize > MAX_MSG_DATA_LEN)
	{
		m_bEnable = false;
		ClearAllMsg();
		return false;
	}
	//���ܹ�̫�����Ϣ�������ٽ����ˣ������ļ�Ҳ��������
	if (!m_bEnable)
	{
		return false;
	}
	UINT uNowTime = 0;
	RecordNetMsgStruct netMsg;// = new RecordNetMsgStruct();
	//���벻���ڴ��ˣ�
	//if (netMsg == NULL)
	//{
	//	m_bEnable = false;
	//	ClearAllMsg();
	//	return false;

	//}
	if (m_iMsgCount == 0)  
	{
		//��һ���յ���Ϣ
		//m_arryMsgList[m_iMsgCount].uTimeSlot = 10;
		netMsg.uTimeSlot = 10;
		uNowTime = GetTickCount();		
	}
	else
	{
		 uNowTime = GetTickCount();
		 netMsg.uTimeSlot = uNowTime - m_uMsgRecTime;		
	}
	m_uMsgRecTime = uNowTime; //�õ���ǰ��ʱ��
	netMsg.uDataSize = uDataSize;
	netMsg.uHeadSize = uHeadSize;
	memcpy(netMsg.NetMsgHead,pNetHead,uHeadSize);
	memcpy(netMsg.NetMsgData,pNetData,uDataSize);
	m_arryMsgList.push_back(netMsg);
	m_iMsgCount++;

	return true;

}
/**
*  �����б������г�ʼ������������������Ϣ����Ϸ������Ϣ������Ϸ��Ϣ,�൱�ڵ���ClearAllMsg ClearAllUerInfo��ClearRoomGameInfo
*/
void CRecorder::InitAll()
{

	m_bEnable = true;
	memset(m_FileHead.arrcFileHeadMd5,0,sizeof(m_FileHead.arrcFileHeadMd5));
	memset(m_FileHead.arrcFileMsgMd5,0,sizeof(m_FileHead.arrcFileMsgMd5));

	//m_arryMsgList.resize(50);
	//int szi = m_arryMsgList.capacity();
	
	ClearAllMsg();
	ClearAllUserInfo();
	ClearRoomGameInfo();
}
/**
* ������е���Ϸ��Ϣ��Ϣ
*/
void CRecorder::ClearAllMsg()
{
	//m_bFirstReceiveMsg = true;
	m_iMsgCount = 0;
	
	m_arryMsgList.clear();
	
}
/**
* ������е��û���Ϣ
*/
void CRecorder::ClearAllUserInfo()
{
	memset(m_FileHead.UsrInfoStruct,0,sizeof(m_FileHead.UsrInfoStruct));
	m_FileHead.bMyDeskStation = 255;
	m_FileHead.uPlayerCount = 0;
	m_FileHead.RoomGameInfo.bMeDeskStation = 255;
}
/**
* ��� ��Ϸ������Ϣ  
*/
void CRecorder::ClearRoomGameInfo()
{
	memset(&m_FileHead.RoomGameInfo,0,sizeof(m_FileHead.RoomGameInfo));
}
/**
*   ѹ���������ļ�  ��Ҫ���ڷ���������,�����ܣ���ʡ�ռ�
*/
bool CRecorder::SaveFileWithZip(const TCHAR* pFileName)
{
	if (pFileName == NULL)
	{
		return false;
	}
	//��ʼ��md5ֵ
	m_FileHead.uFileType = FILE_TYPE_ZIP;
	m_FileHead.uTotalMsgCount = m_iMsgCount;
	memset(m_FileHead.arrcFileHeadMd5,0,sizeof(m_FileHead.arrcFileHeadMd5));
	memset(m_FileHead.arrcFileMsgMd5,0,sizeof(m_FileHead.arrcFileMsgMd5));
	
	UINT uHeadComBufferLen = compressBound(sizeof(FileHeadBase));  //�õ���Ҫѹ���ĳ���
	UINT uMsgComBufferLen  = compressBound(sizeof(RecordNetMsgStruct) * m_iMsgCount);
	uLongf uComHeadRealBufferLen = uHeadComBufferLen;
	uLongf uComMsgRealBufferLen = uMsgComBufferLen;

	//UINT test = sizeof(uLongf);

	unsigned char* buffer = new unsigned char[uHeadComBufferLen + uMsgComBufferLen + 2 * sizeof(uLongf)];

	//unsigned char* buffer = new unsigned char[uHeadComBufferLen + uMsgComBufferLen + 10000];
	
	if (buffer == NULL)
	{
		return false;
	}
	memset(buffer,0,uHeadComBufferLen + uMsgComBufferLen);
	//ѹ���ļ�ͷ��

	unsigned char* pFile = (unsigned char*)(&m_FileHead);

//	FileHeadStruct test;
//	memcpy(&test,pFile,sizeof(test));



	int iRet = compress(buffer + sizeof(uLongf) * 2,&uComHeadRealBufferLen,pFile,sizeof(FileHeadBase));
	if (iRet != Z_OK)  //ѹ��ʧ��
	{
		//ɾ������
		delete buffer;
		return false;
	}
    pFile = (unsigned char*) (&m_arryMsgList[0]);
	iRet = compress((buffer + sizeof(uLongf) * 2 + uComHeadRealBufferLen),&uComMsgRealBufferLen,pFile,sizeof(RecordNetMsgStruct) * m_iMsgCount);
	if (iRet != Z_OK)
	{
		//ɾ������
		delete buffer;
		return false;
	}
	//д��ѹ�����ļ�ͷ�Ĵ�С��ѹ������Ϣ�Ĵ�С
	memcpy(buffer,&uComHeadRealBufferLen,sizeof(uLongf));
	memcpy(buffer + sizeof(uLongf),&uComMsgRealBufferLen,sizeof(uLongf));
	
	//�ַ������л����,��ʼд�ļ�
	if (Write2File(pFileName,buffer,(uHeadComBufferLen + uMsgComBufferLen)))
	{
		delete buffer ;
		return true;
	}	
	delete buffer ;
	return false;

}
/**
*   ѹ������md5У�鱣���ļ������ڿͻ��˱��棬��ֹ�ļ����ƻ�
*/
bool CRecorder::SaveFileWithPassZip(const TCHAR* pFileName)
{
	if (pFileName == NULL)
	{
		::OutputDebugString(pFileName);

		return false;
	}
	if (m_iMsgCount < 5)  //���ֻ��һ����Ϣ����û�б�Ҫ��¼
	{
		return true;
	}
	m_FileHead.uTotalMsgCount = m_iMsgCount;
	//����
	Md5Data(FILE_TYPE_PASS_ZIP);	
	//��ʼ��md5ֵ
	

	UINT uHeadComBufferLen = compressBound(sizeof(FileHeadStruct));  //�õ���Ҫѹ���ĳ���
	UINT uMsgComBufferLen  = compressBound(sizeof(RecordNetMsgStruct) * m_iMsgCount);
	uLongf uComHeadRealBufferLen = uHeadComBufferLen;
	uLongf uComMsgRealBufferLen = uMsgComBufferLen;
	unsigned char* buffer = new unsigned char[uHeadComBufferLen + uMsgComBufferLen + 2 * sizeof(uLongf)];

	if (buffer == NULL)
	{
		return false;
	}
	memset(buffer,0,uHeadComBufferLen + uMsgComBufferLen);
	//ѹ���ļ�ͷ��
	unsigned char* pFile = (unsigned char*)(&m_FileHead);
	int iRet = compress(buffer + 2 * sizeof(uLongf),&uComHeadRealBufferLen,pFile,sizeof(FileHeadStruct));
	if (iRet != Z_OK)  //ѹ��ʧ��
	{
		//ɾ������
		delete buffer;
		return false;
	}
	pFile = (unsigned char*) (&m_arryMsgList[0]);
	iRet = compress((buffer + 2 * sizeof(uLongf) + uComHeadRealBufferLen),&uComMsgRealBufferLen,pFile,sizeof(RecordNetMsgStruct) * m_iMsgCount);
	if (iRet != Z_OK)
	{
		//ɾ������
		delete buffer;
		return false;
	}
	//д��ѹ�����ļ�ͷ�Ĵ�С��ѹ������Ϣ�Ĵ�С
	memcpy(buffer,&uComHeadRealBufferLen,sizeof(uLongf));
	memcpy(buffer + sizeof(uLongf),&uComMsgRealBufferLen,sizeof(uLongf));
	//�ַ������л����,��ʼд�ļ�
	if (Write2File(pFileName,buffer,(uHeadComBufferLen + uMsgComBufferLen)))
	{
		delete buffer ;
		return true;
	}	
	delete buffer ;
	return false;
   
	
}
/**
* ���ı����ļ�����Ҫ�ڲ���ʱ��
*/
bool CRecorder::SaveFileWithNone(const TCHAR* pFileName)
{
	//Md5Data(1);
	if (pFileName == NULL)
	{
		return false;
	}
	m_FileHead.uFileType = FILE_TYPE_NONE;
	m_FileHead.uTotalMsgCount = m_iMsgCount;
    return Write2File(pFileName);

}

/**
*  �����ַ��������û�������ô��ʹ����Щ��Ϣ
*/
UINT CRecorder::GetParDataSize()
{
	UINT uHeadComBufferLen = compressBound(sizeof(FileHeadStruct));  //�õ���Ҫѹ���ĳ���
	UINT uMsgComBufferLen  = compressBound(sizeof(RecordNetMsgStruct) * m_iMsgCount);
	
	return (uHeadComBufferLen + uMsgComBufferLen + 2 * sizeof(uLongf));

}
void CRecorder::GetParsedData( unsigned char* szStr,UINT uInSize,UINT& uOutSize)
{
	uOutSize = 0;
	if (szStr == NULL || uInSize <= 0)
	{
		return;
	}
	memset(szStr,0,uInSize);
	//UINT uMsgLen = sizeof(RecordNetMsgStruct) * m_iMsgCount;
	//UINT uTotalLen = sizeof(FileHeadStruct) + uMsgLen;
	//if (uInSize < uTotalLen)
	//{
	//	return;
	//}
	//Md5Data(FILE_TYPE_NONE);
	//memcpy(szStr,&m_FileHead,sizeof(FileHeadStruct));
	//uOutSize += sizeof(FileHeadStruct);
	//memcpy(szStr + uOutSize,&m_arryMsgList[0],uMsgLen);
	//uOutSize += uMsgLen;

	m_FileHead.uTotalMsgCount = m_iMsgCount;
	//����
	Md5Data(FILE_TYPE_PASS_ZIP);	
	//��ʼ��md5ֵ


	UINT uHeadComBufferLen = compressBound(sizeof(FileHeadStruct));  //�õ���Ҫѹ���ĳ���
	UINT uMsgComBufferLen  = compressBound(sizeof(RecordNetMsgStruct) * m_iMsgCount);
	uLongf uComHeadRealBufferLen = uHeadComBufferLen;
	uLongf uComMsgRealBufferLen = uMsgComBufferLen;
	unsigned char* buffer = new unsigned char[uHeadComBufferLen + uMsgComBufferLen + 2 * sizeof(uLongf)];

	if (buffer == NULL)
	{
		return ;
	}
	memset(buffer,0,uHeadComBufferLen + uMsgComBufferLen);
	//ѹ���ļ�ͷ��
	unsigned char* pFile = (unsigned char*)(&m_FileHead);
	int iRet = compress(buffer + 2 * sizeof(uLongf),&uComHeadRealBufferLen,pFile,sizeof(FileHeadStruct));
	if (iRet != Z_OK)  //ѹ��ʧ��
	{
		//ɾ������
		delete buffer;
		return;
	}
	pFile = (unsigned char*) (&m_arryMsgList[0]);
	iRet = compress((buffer + 2 * sizeof(uLongf) + uComHeadRealBufferLen),&uComMsgRealBufferLen,pFile,sizeof(RecordNetMsgStruct) * m_iMsgCount);
	if (iRet != Z_OK)
	{
		//ɾ������
		delete buffer;
		return;
	}
	//д��ѹ�����ļ�ͷ�Ĵ�С��ѹ������Ϣ�Ĵ�С
	memcpy(buffer,&uComHeadRealBufferLen,sizeof(uLongf));
	memcpy(buffer + sizeof(uLongf),&uComMsgRealBufferLen,sizeof(uLongf));
	//�ַ������л����,��ʼд�ļ�
	uOutSize = uComHeadRealBufferLen + uComMsgRealBufferLen + 2 * sizeof(uLongf);
	if (uInSize < uOutSize)
	{
		uOutSize = 0;
		delete buffer;
		return;
	}
	memcpy(szStr,buffer,uOutSize);
	delete buffer;
	return ;
}

//************************************************************
//�������õ��Ľӿ�

RecordUserItemStruct* CRecorder::GetMeUserInfo()
{
	if (m_FileHead.bMyDeskStation >= MAX_PLAYER_COUNT)
	{
		return NULL;
	}
	return &m_FileHead.UsrInfoStruct[m_FileHead.bMyDeskStation];

}
/**
* ��ȡĳ��λ�õ������Ϣ  
*/
RecordUserItemStruct* CRecorder::GetUserInfo(BYTE bDeskStation)
{
	if (bDeskStation >= MAX_PLAYER_COUNT)
	{
		return NULL;
	}
	return &m_FileHead.UsrInfoStruct[bDeskStation];

}
/**
*  ��ȡ��ҵ�����
*/
UINT CRecorder::GetGamePlayerNum() const
{
	if (m_FileHead.uPlayerCount >= MAX_PLAYER_COUNT)
	{
		return 0;
	}
	return m_FileHead.uPlayerCount;

}
/**
*  �õ���Ϸ�����������Ϣ
*/
RecordGameInfoStruct* CRecorder::GetRoomGameInfo()
{
	return &m_FileHead.RoomGameInfo;
}
/**
*  �õ���Ϣ����
*/
int CRecorder::GetTotalMsgCount() const
{
	return m_iMsgCount;
}
/**
*  �õ���Ϣ������
*/
void CRecorder::GetMsgInfo(int iIndex,void* ppMsgHead,void* ppMsgData,UINT& uHeadSize,UINT& uDataSize,UINT& iTimeSlot)
{
	//�������voidָ��copy��ֵ��������ֱ�Ӵ���ָ��ģ���Ϊ�˰�ȫ��������Ƕ�copyһ�ΰ�
	memset(ppMsgHead,0,uHeadSize);
	memset(ppMsgData,0,uDataSize);
    //��ֵǰ����
	if (uHeadSize < MAX_MSG_HEAD_LEN)
	{
		uDataSize = 0;
		uHeadSize = 0;
		iTimeSlot = 0;
		return;
	}
	if (uDataSize < MAX_MSG_DATA_LEN)
	{
		uDataSize = 0;
		uHeadSize = 0;
		iTimeSlot = 0;
		return;
	}
	if (iIndex < 0 || iIndex > m_iMsgCount)
	{
		return;
	}
	RecordNetMsgStruct& msg = m_arryMsgList[iIndex];
	memcpy(ppMsgHead,msg.NetMsgHead,sizeof(msg.NetMsgHead));
	memcpy(ppMsgData,msg.NetMsgData,sizeof(msg.NetMsgData));
	uHeadSize = msg.uHeadSize;
	uDataSize = msg.uDataSize;
	iTimeSlot = msg.uTimeSlot;

}
/**
*  װ��ѹ�������ļ�
*/
bool CRecorder::LoadFileWithZip(const TCHAR* filename)
{
	return LoadZip(filename,FILE_TYPE_ZIP);
	
}
/**
*  װ��ѹ�����ܹ����ļ�
*/
bool CRecorder::LoadFileWithPassZip(const TCHAR* filename)
{
	if (!LoadZip(filename,FILE_TYPE_PASS_ZIP))
	{
		
		return false;
	}
	if (!CheckMd5())
	{
		InitAll();
	}
	return true;	
}
/**
*  װ��û�н��й��κδ�����ļ������ģ�
*/
bool CRecorder::LoadFileWithNone(const TCHAR* filename)
{
	if (filename == NULL)
	{
		return false;
	}
	InitAll();
	CFile file;
	if (file.Open(filename,CFile::modeRead | CFile::shareDenyNone) == FALSE)
	{
		return false;
	}
	
	UINT uReadLen = file.Read(&m_FileHead,sizeof(FileHeadBase));
	if (uReadLen != sizeof(FileHeadBase))
	{
		return false;
	}
	m_iMsgCount = m_FileHead.uTotalMsgCount;
	if (m_iMsgCount < 0)
	{
		return false;
	}
	m_arryMsgList.reserve(m_iMsgCount);
	UINT uMsgLen = sizeof(RecordNetMsgStruct) * m_iMsgCount;
	RecordNetMsgStruct* pBuffer = new RecordNetMsgStruct[m_iMsgCount];
	if (pBuffer == NULL)
	{
		return false;
	}
	uReadLen = file.Read(pBuffer,uMsgLen);
	if (uReadLen != uMsgLen)
	{
		delete pBuffer;
		return false;
	}
	for (int i=0; i<m_iMsgCount; i++)
	{
		m_arryMsgList.push_back(pBuffer[i]);
	}
	//memcpy(&m_arryMsgList[0],pBuffer,uReadLen);
	delete pBuffer;

	return true;
}

bool CRecorder::LoadStringBuffer(unsigned char * pBuffer,UINT uSize)
{
	if(pBuffer == NULL || uSize < 2 * sizeof(uLongf))
	{
		return false;
	}

	uLongf uReadHeadLen = *(uLongf*)pBuffer;

	UINT uReadLen = sizeof(uLongf);


	

	uLongf uReadMsgLen = *(uLongf*)(pBuffer + uReadLen);
	uReadLen += sizeof(uLongf);

	if (uSize < (uReadLen + 2 * sizeof(uLongf)))
	{
		return false;
	}

	//unsigned char* bufferHead = new unsigned char[uReadHeadLen];
	//if (bufferHead == NULL)
	//{
	//	return false;
	//}
	////��ȡѹ����ͷ�ļ�
	////uReadLen = file.Read(bufferHead,uReadHeadLen);

	//if (uReadLen != uReadHeadLen)
	//{
	//	delete bufferHead;
	//	return false;
	//}

	uLongf uHeadLen = sizeof(FileHeadStruct);

	//��ѹͷ
	unsigned char* pTemPointer = (unsigned char*)(&m_FileHead);
	int iRet = uncompress(pTemPointer,&uHeadLen,pBuffer + uReadLen,uReadHeadLen);
	if (iRet != Z_OK)
	{
		//delete bufferHead;
		return false;
	}
	uReadLen += uReadHeadLen;

	//delete bufferHead;
	//bufferHead = new unsigned char[uReadMsgLen];
	//if (bufferHead == NULL)
	//{
	//	return false;
	//}
	//uReadLen = file.Read(bufferHead,uReadMsgLen);
	//if (uReadLen != uReadMsgLen)
	//{
	//	delete bufferHead;
	//	return false;
	//}
	m_iMsgCount = m_FileHead.uTotalMsgCount;  //�ܹ��ж�������Ϣ
	if (m_iMsgCount < 0)
	{
		return false;
	}
	m_arryMsgList.reserve(m_iMsgCount);

	RecordNetMsgStruct* pTemMsgBuffer = new RecordNetMsgStruct[m_iMsgCount];
	if (pTemMsgBuffer == NULL)
	{
		return false;
	}


	pTemPointer = (unsigned char*)pTemMsgBuffer;



	uLongf uMsgLen = m_iMsgCount * sizeof(RecordNetMsgStruct);
	iRet = uncompress(pTemPointer,&uMsgLen,pBuffer + uReadLen,uReadMsgLen);
	if (iRet != Z_OK)
	{
		delete pTemMsgBuffer;
		//delete bufferHead;
		return false;
	}
	for (int i=0; i<m_iMsgCount; i++)
	{
		m_arryMsgList.push_back(pTemMsgBuffer[i]);
	}
	delete pTemMsgBuffer;
	//delete bufferHead;
	if (!CheckMd5())
	{
		InitAll();
		return false;
	}
	return true;


}

//************************************************************
//�Լ��õ��Ľӿ�
//�Եõ������ݽ���md5����
void CRecorder::Md5Data(UINT uFileType)
{
	MD5_CTX Md5;
	if (uFileType > 10)
	{
		return;
	}
	m_FileHead.uFileType = uFileType;
	Md5.MD5Update((unsigned char *)(&m_FileHead),sizeof(FileHeadBase));
	Md5.MD5Final(m_FileHead.arrcFileHeadMd5);
	Md5.MD5Init();
	Md5.MD5Update((unsigned char*)(&m_arryMsgList[0]),sizeof(RecordNetMsgStruct) * m_iMsgCount);
	Md5.MD5Final(m_FileHead.arrcFileMsgMd5);
}
bool CRecorder::CheckMd5()
{
	MD5_CTX Md5;
	unsigned char arrcMd5Check[17];
	Md5.MD5Update((unsigned char *)(&m_FileHead),sizeof(FileHeadBase));
	Md5.MD5Final(arrcMd5Check);
	arrcMd5Check[16] = 0;
	unsigned char tempMd5[17];
	memcpy(tempMd5,m_FileHead.arrcFileHeadMd5,sizeof(m_FileHead.arrcFileHeadMd5));
	tempMd5[16] = 0;
	//int test = strcmp((char*)arrcMd5Check,(char*)tempMd5);
	if (strcmp((char*)arrcMd5Check,(char*)tempMd5) != 0)
	{
		//InitAll();
		return false;
	}
	Md5.MD5Init();
	Md5.MD5Update((unsigned char*)(&m_arryMsgList[0]),sizeof(RecordNetMsgStruct) * m_iMsgCount);
	Md5.MD5Final(arrcMd5Check);

	memcpy(tempMd5,m_FileHead.arrcFileMsgMd5,sizeof(m_FileHead.arrcFileMsgMd5));

	if (strcmp((char*)arrcMd5Check,(char*)tempMd5) != 0)
	{
		//InitAll();
		return false;
	}
	return true;

}

bool CRecorder::Write2File(const TCHAR* pFileName,const unsigned char* pBuffer,UINT uBufferLen)
{
	if (pFileName == NULL || pBuffer == NULL || uBufferLen < 0)
	{
		return false;
	}	
	//��CFileд�ļ������Ҫ��ƽ̨�����޸���
	CFile file;
	if (file.Open(pFileName,CFile::modeCreate|CFile::modeWrite|CFile::shareDenyNone) == FALSE)
	{
		return false;
	}
	file.Write(pBuffer,uBufferLen);
	file.Close();
	return true;

}
bool CRecorder::Write2File(const TCHAR* pFileName)
{
	//д�ļ����
	CFile file;
	if (file.Open(pFileName,CFile::modeCreate|CFile::modeWrite|CFile::shareDenyNone|CFile::modeNoTruncate) == FALSE)
	{
		return false;
	}
	file.Write(&m_FileHead,sizeof(FileHeadBase));
	file.SeekToEnd();
	file.Write(&m_arryMsgList[0],m_iMsgCount * sizeof(RecordNetMsgStruct));
	file.Close();
	return true;
}
bool CRecorder::LoadZip(const TCHAR* filename,UINT uFileType)
{
	if (filename == NULL)
	{
		OutputDebugString("load fail 11");
		return false;
	}
	InitAll();
	CFile file;
	OutputDebugString(filename);
	if (file.Open(filename,CFile::modeRead | CFile::shareDenyNone) == FALSE)
	{
		OutputDebugString("load fail 22");
		return false;
	}
	uLongf uReadHeadLen = 0;
	UINT uReadLen = file.Read(&uReadHeadLen,sizeof(uLongf));
	if (uReadLen != sizeof(uLongf))
	{
		OutputDebugString("load fail 33");
		return false;
	}
	uLongf uReadMsgLen = 0;
	uReadLen = file.Read(&uReadMsgLen,sizeof(uLongf));
	if (uReadLen  != sizeof(uLongf))
	{
		OutputDebugString("load fail 44");
		return false;
	}
	unsigned char* bufferHead = new unsigned char[uReadHeadLen];
	if (bufferHead == NULL)
	{
		OutputDebugString("load fail 55");
		return false;
	}
	//��ȡѹ����ͷ�ļ�
	uReadLen = file.Read(bufferHead,uReadHeadLen);
	if (uReadLen != uReadHeadLen)
	{
		OutputDebugString("load fail 66");
		delete bufferHead;
		return false;
	}

	uLongf uHeadLen = sizeof(FileHeadStruct);

	//��ѹͷ
	unsigned char* pTemPointer = (unsigned char*)(&m_FileHead);
	int iRet = uncompress(pTemPointer,&uHeadLen,bufferHead,uReadHeadLen);
	if (iRet != Z_OK)
	{
		OutputDebugString("load fail 77");
		delete bufferHead;
		return false;
	}

	delete bufferHead;
	bufferHead = new unsigned char[uReadMsgLen];
	if (bufferHead == NULL)
	{
		OutputDebugString("load fail 88");
		return false;
	}
	uReadLen = file.Read(bufferHead,uReadMsgLen);
	if (uReadLen != uReadMsgLen)
	{
		OutputDebugString("load fail 99");
		delete bufferHead;
		return false;
	}
	m_iMsgCount = m_FileHead.uTotalMsgCount;  //�ܹ��ж�������Ϣ
	if (m_iMsgCount < 0)
	{
		OutputDebugString("load fail aa");
		return false;
	}
	m_arryMsgList.reserve(m_iMsgCount);

	RecordNetMsgStruct* pTemMsgBuffer = new RecordNetMsgStruct[m_iMsgCount];
	if (pTemMsgBuffer == NULL)
	{
		OutputDebugString("load fail bb");
		return false;
	}
	
    
	pTemPointer = (unsigned char*)pTemMsgBuffer;

	

	uLongf uMsgLen = m_iMsgCount * sizeof(RecordNetMsgStruct);
	iRet = uncompress(pTemPointer,&uMsgLen,bufferHead,uReadMsgLen);
	if (iRet != Z_OK)
	{
		OutputDebugString("load fail cc");
		delete pTemMsgBuffer;
		delete bufferHead;
		return false;
	}
	for (int i=0; i<m_iMsgCount; i++)
	{
		m_arryMsgList.push_back(pTemMsgBuffer[i]);
	}
	delete pTemMsgBuffer;
	delete bufferHead;
	return true;

}