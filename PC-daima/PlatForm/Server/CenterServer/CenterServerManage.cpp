#include "StdAfx.h"
#include "CenterServerManage.h"
#include "CommonUse.h"

//�궨��
#define IDT_UPDATE_INIFILE						20					//����������Ӷ�ʱ��
#define IDT_CHECK_DATA_CONNECT					2					//����������Ӷ�ʱ��
extern void OutputFun(char* message);
/******************************************************************************************************/
//��������
bool CCenterServerManage::OnStart()
{
	//������ݿ�����
	SetTimer(IDT_UPDATE_INIFILE,15000L);

	//m_ZServerManager������B�����������ã�B�а�����Z��IP�Ͷ˿ڶ��Ǵ洢��GAMEGATE.bcf�ļ���
	m_ZServerManager.Start();

	return true;
}
//��ʱ����Ϣ
bool CCenterServerManage::OnTimerMessage(UINT uTimerID)
{
	switch (uTimerID)
	{
	case IDT_UPDATE_INIFILE:			//������Ϸ�б�ʱ��
		{
			KillTimer(IDT_UPDATE_INIFILE);
			GetINIFile();
			SetTimer(IDT_UPDATE_INIFILE,30000L);
			break;
		}
	default:
		break;
	}

	return true;
}
void CCenterServerManage::GetINIFile()
{
	DWORD cfgHandle=cfgOpenFile("BZGameGate.bcf");
	if(cfgHandle<0x10)
		return;

//	#define len(l1,l2)  ( (l1).GetLength () > (l2 ) ? (l2) : ((l1).GetLength ()))

	CString ss = cfgGetValue(cfgHandle,"GateServer","SerialNo","");//�ͻ��˵�ǰ�汾ϵ�кţ����û��˱Ƚϲ�ͬ��Ҫ�û�ȥ����
	strncpy(m_msgSendToClient.m_strGameSerialNO,ss,sizeof(m_msgSendToClient.m_strGameSerialNO)-1);
	m_msgSendToClient.m_strGameSerialNO[sizeof(m_msgSendToClient.m_strGameSerialNO)-1] = '\0';

	ss = cfgGetValue(cfgHandle,"GateServer","MainServerAddress","");//��������IP��ַ
	strncpy(m_msgSendToClient.m_strMainserverIPAddr,ss,sizeof(m_msgSendToClient.m_strMainserverIPAddr)-1);
	m_msgSendToClient.m_strMainserverIPAddr[sizeof(m_msgSendToClient.m_strMainserverIPAddr)-1] = '\0';

	m_msgSendToClient.m_iMainserverPort=cfgGetValue(cfgHandle,"GateServer","MainServerPort",6800);

	m_msgSendToClient.m_nEncryptType = cfgGetValue(cfgHandle, "GateServer","EncryType", 2); //ƽ̨�����õļ��ܷ�ʽ��1λMD5��2λSHA1��Ĭ��Ϊ2; 2009-5-30 zxj

	ss = cfgGetValue(cfgHandle,"GateServer","WebHomeURL","");//��ҳWEB��ַ
	strncpy(m_msgSendToClient.m_strHomeADDR,ss,sizeof(m_msgSendToClient.m_strHomeADDR)-1);
	m_msgSendToClient.m_strHomeADDR[sizeof(m_msgSendToClient.m_strHomeADDR)-1] = '\0';

	ss = cfgGetValue(cfgHandle,"GateServer","WebRootURL","");//��վ��·�����ڳ������漰���ļ���Ŀ¼���������ַ����չ
	strncpy(m_msgSendToClient.m_strWebRootADDR,ss,sizeof(m_msgSendToClient.m_strWebRootADDR)-1);
	m_msgSendToClient.m_strWebRootADDR[sizeof(m_msgSendToClient.m_strWebRootADDR)-1] = '\0';

	ss = cfgGetValue(cfgHandle,"GateServer","WebHelpURL","");//����ҳWEB��ַ
	strncpy(m_msgSendToClient.m_strHelpADDR,ss,sizeof(m_msgSendToClient.m_strHelpADDR)-1);
	m_msgSendToClient.m_strHelpADDR[sizeof(m_msgSendToClient.m_strHelpADDR)-1] = '\0';

	ss = cfgGetValue(cfgHandle,"GateServer","DownLoadSetupURL","");//�ͻ��˰�װ��������ҳWEB��ַ
	strncpy(m_msgSendToClient.m_strDownLoadSetupADDR,ss,sizeof(m_msgSendToClient.m_strDownLoadSetupADDR)-1);
	m_msgSendToClient.m_strDownLoadSetupADDR[sizeof(m_msgSendToClient.m_strDownLoadSetupADDR)-1] = '\0';

	ss = cfgGetValue(cfgHandle,"GateServer","DownLoadUpdatepURL","");//�ͻ��˸��³�������ҳWEB��ַ
	strncpy(m_msgSendToClient.m_strDownLoadUpdatepADDR,ss,sizeof(m_msgSendToClient.m_strDownLoadUpdatepADDR)-1);
	m_msgSendToClient.m_strDownLoadUpdatepADDR[sizeof(m_msgSendToClient.m_strDownLoadUpdatepADDR)-1] = '\0';

	ss = cfgGetValue(cfgHandle,"GateServer","RallAddvtisFlashURL","");//�ͻ��˴���FLASH�������ҳWEB��ַ
	strncpy(m_msgSendToClient.m_strRallAddvtisFlashADDR,ss,sizeof(m_msgSendToClient.m_strRallAddvtisFlashADDR)-1);
	m_msgSendToClient.m_strRallAddvtisFlashADDR[sizeof(m_msgSendToClient.m_strRallAddvtisFlashADDR)-1] = '\0';

	ss = cfgGetValue(cfgHandle,"GateServer","RoomRollWords","��ӭ��������������Ϸ���磡");//�ͻ��˹���������ַ
	
	//wushuqun 2009.6.5
	strncpy(m_msgSendToClient.m_strRoomRollADDR,ss,sizeof(m_msgSendToClient.m_strRoomRollADDR)-1);
	m_msgSendToClient.m_strRoomRollADDR[sizeof(m_msgSendToClient.m_strRoomRollADDR)-1] = '\0';

	m_msgSendToClient.m_nIsUsingIMList = cfgGetValue(cfgHandle,"GateServer","UsingIMList",1);

	//�������Ͻ�����ʾID�Ż�������ֵ
	m_msgSendToClient.m_nHallInfoShowClass=cfgGetValue(cfgHandle,"GateServer","HallInforShowClass",0);

    m_msgSendToClient.m_is_haveZhuanZhang = cfgGetValue(cfgHandle,"GateServer","IsHaveZhuanZhang",0);
	//m_MainserverList.LoadServerList(cfgHandle);

	cfgClose(cfgHandle);

	GetFunction(); ///< ��ȡ������ʹ�õĹ���

	//CString s=CINIFile::GetAppPath ();
	//CINIFile f( s + "CenterServer.ini");
	//#define len(l1,l2)  ( (l1).GetLength () > (l2 ) ? (l2) : ((l1).GetLength ()))
	//////���������˿ں�
	//s=f.GetKeyVal ("www.BZW.cn","BZW","");//����������ģʽ����ʵ���Ӧ�ôӿͻ��˻�ȡ���ͻ���Ҫʲôģʽ�Ĳ������ͷ�ʲôģʽ�Ĳ���
	//m_msgSendToClient.m_iMainserverPort=f.GetKeyVal (s,"m_iMainserverPort",6800);

	//ss=f.GetKeyVal (s,"SerialNO","");//
	//memcpy(m_msgSendToClient.m_strGameSerialNO,ss,len(ss,20)  );//ss.GetLength ());

	//ss=f.GetKeyVal (s,"m_strMainserverIPAddr","");//
	//memcpy(m_msgSendToClient.m_strMainserverIPAddr,ss,len(ss,20)  );

	//ss=f.GetKeyVal (s,"m_strHomeADDR","");//
	//memcpy(m_msgSendToClient.m_strHomeADDR,ss,len(ss,50)  );

	//ss=f.GetKeyVal (s,"m_strWebRootADDR","");//
	//memcpy(m_msgSendToClient.m_strWebRootADDR,ss,len(ss,50)  );

	//ss=f.GetKeyVal (s,"m_strHelpADDR","");//
	//memcpy(m_msgSendToClient.m_strHelpADDR,ss,len(ss,50)  );

	//ss=f.GetKeyVal (s,"m_strDownLoadSetupADDR","123");////
	//memcpy(m_msgSendToClient.m_strDownLoadSetupADDR,ss,len(ss,50)  );

	//ss=f.GetKeyVal (s,"m_strDownLoadUpdatepADDR","123");//
	//memcpy(m_msgSendToClient.m_strDownLoadUpdatepADDR,ss,len(ss,50)  );

	//ss=f.GetKeyVal (s,"m_strRallAddvtisFlashADDR","123");//
	//memcpy(m_msgSendToClient.m_strRallAddvtisFlashADDR,ss,len(ss,50)  );

	//ss=f.GetKeyVal (s,"m_strRoomRollADDR","��ӭ������������Ϸ���ģ�");////�ͻ��˹���������ַ
	//memcpy(m_msgSendToClient.m_strRoomRollADDR,ss,len(ss,100)  );
	//
	////�������Ͻ�����ʾID�Ż�������ֵ
	//m_msgSendToClient.m_nHallInfoShowClass=f.GetKeyVal(s,"HallInforShowClass",0);

	//m_MainserverList.ReadINIFile(s);

//	OutputFun("���������ļ��ɹ���");
}

void CCenterServerManage::GetURL(char *strKey)
{
	CBcfFile f(CBcfFile::GetAppPath() + "BZGameGate.bcf");
	CString strValue;

	if (NULL == strKey)
	{
		strValue = f.GetKeyVal(_T("GateServer"),_T("RoomRollWords"),_T("��ӭ��������������Ϸ���ģ�"));///< �ͻ��˹���������ַ
		strncpy(m_msgSendToClient.m_strRoomRollADDR,strValue,sizeof(m_msgSendToClient.m_strRoomRollADDR)-1);
		m_msgSendToClient.m_strRoomRollADDR[sizeof(m_msgSendToClient.m_strRoomRollADDR)-1] = '\0';

		strValue = f.GetKeyVal(_T("GateServer"),_T("WebHelpURL"),_T(""));///< ����ҳWEB��ַ
		strncpy(m_msgSendToClient.m_strHelpADDR,strValue,sizeof(m_msgSendToClient.m_strHelpADDR)-1);
		m_msgSendToClient.m_strHelpADDR[sizeof(m_msgSendToClient.m_strHelpADDR)-1] = '\0';

		strValue = f.GetKeyVal(_T("GateServer"),_T("WebHomeURL"),_T(""));///< ��ҳWEB��ַ
		strncpy(m_msgSendToClient.m_strHomeADDR,strValue,sizeof(m_msgSendToClient.m_strHomeADDR)-1);
		m_msgSendToClient.m_strHomeADDR[sizeof(m_msgSendToClient.m_strHomeADDR)-1] = '\0';

		strValue = f.GetKeyVal(_T("GateServer"),_T("WebRootURL"),_T(""));///< ��վ��·��
		strncpy(m_msgSendToClient.m_strWebRootADDR,strValue,sizeof(m_msgSendToClient.m_strWebRootADDR)-1);
		m_msgSendToClient.m_strWebRootADDR[sizeof(m_msgSendToClient.m_strWebRootADDR)-1] = '\0';
	}
	else
	{
		strValue = f.GetKeyVal(_T("WebHomeURL"),strKey,_T(""));///< ��ҳWEB��ַ
		if (strValue.IsEmpty())
		{
			GetURL(NULL);
			return;
		}
		strncpy(m_msgSendToClient.m_strHomeADDR,strValue,sizeof(m_msgSendToClient.m_strHomeADDR)-1);
		m_msgSendToClient.m_strHomeADDR[sizeof(m_msgSendToClient.m_strHomeADDR)-1] = '\0';

		strValue = f.GetKeyVal(_T("RoomRollWords"),strKey,_T(""));///< �ͻ��˹���������ַ
		strncpy(m_msgSendToClient.m_strRoomRollADDR,strValue,sizeof(m_msgSendToClient.m_strRoomRollADDR)-1);
		m_msgSendToClient.m_strRoomRollADDR[sizeof(m_msgSendToClient.m_strRoomRollADDR)-1] = '\0';

		strValue = f.GetKeyVal(_T("WebHelpURL"),strKey,_T(""));///< ����ҳWEB��ַ
		strncpy(m_msgSendToClient.m_strHelpADDR,strValue,sizeof(m_msgSendToClient.m_strHelpADDR)-1);
		m_msgSendToClient.m_strHelpADDR[sizeof(m_msgSendToClient.m_strHelpADDR)-1] = '\0';

		strValue = f.GetKeyVal(_T("WebRootURL"),strKey,_T(""));///< ��վ��·��
		strncpy(m_msgSendToClient.m_strWebRootADDR,strValue,sizeof(m_msgSendToClient.m_strWebRootADDR)-1);
		m_msgSendToClient.m_strWebRootADDR[sizeof(m_msgSendToClient.m_strWebRootADDR)-1] = '\0';
	}
	
}

/// ��Function.bcf�ж�ȡ��������
/// @param void
/// @return void
void CCenterServerManage::GetFunction()
{
	CBcfFile f(CBcfFile::GetAppPath() + "Function.bcf");
	CString strValue;

	strValue = f.GetKeyVal("SpecificID","Available","0"); ///< ���«2��ָ��ID��
	if (0 != _ttoi(strValue))
	{
		m_msgSendToClient.m_nFunction = 1;
		strValue = f.GetKeyVal("SpecificID","NormalID","60000000,69999999");
		m_msgSendToClient.m_lNomalIDFrom = atol(strValue.Left(strValue.Find(",")+1));
		m_msgSendToClient.m_lNomalIDEnd  = atol(strValue.Right(strValue.GetLength()-strValue.Find(",")-1));
	}

	strValue = f.GetKeyVal("OnlineCoin","Available","0"); ///< �����������ͽ�ҡ�
	if (0 != _ttoi(strValue))
	{
		m_msgSendToClient.m_nFunction |= 1<<1;
	}

	strValue = f.GetKeyVal("RobotExtend","Available","0"); ///< �쵱�����������ҡ�
	if (0 != _ttoi(strValue))
	{
		m_msgSendToClient.m_nFunction |= 2<<1;
	}

    // PengJiLin, 2010-8-17, �����Ƿ��ֹ˽��
    strValue = f.GetKeyVal("CommFunc","ForbidSay","0");  // 0 = û�н�ֹ
    if( 0 != _ttoi(strValue))
    {
        m_msgSendToClient.m_nFunction |= 1<<3;
    }
}

//SOCKET ���ݶ�ȡ////������Ϸȫ�ֲ���
bool CCenterServerManage::OnSocketRead(NetMessageHead * pNetHead, void * pData, UINT uSize, ULONG uAccessIP, UINT uIndex, DWORD dwHandleID)
{
	if (pNetHead->bMainID==MDM_GP_REQURE_GAME_PARA)	////������Ϸȫ�ֲ���
	{
		if (0 == uSize)
		{
			GetURL(NULL);
		}
		else
		{
			char * pBuf = (char*)pData;
			GetURL(pBuf);
		}

		//RandAServer();//ȡ�����ؾ���sdp20140624
		m_TCPSocket.SendData(uIndex,&m_msgSendToClient,sizeof(CenterServerMsg),
			MDM_GP_REQURE_GAME_PARA,0,0,0);
		return true;
	}
	return false;
}
/******************************************************************************************************/

//���캯��
CCenterServerManage::CCenterServerManage(void) : CBaseMainManage()
{
	GetINIFile();
}
//�������� 
CCenterServerManage::~CCenterServerManage(void)
{
}
//ֹͣ����
bool CCenterServerManage::OnStop()
{
	KillTimer(IDT_CHECK_DATA_CONNECT);
	m_ZServerManager.Stop();
	return true;
}

///���ݹ���ģ���ʼ��
bool CCenterServerManage::OnInit(ManageInfoStruct * pInitData, KernelInfoStruct * pKernelData)
{
	return m_ZServerManager.Init(pInitData,NULL);
}
///���ݹ���ģ��ж��
bool CCenterServerManage::OnUnInit()
{
	return m_ZServerManager.UnInit();
}

//��ȡ��Ϣ����
bool CCenterServerManage::PreInitParameter(ManageInfoStruct * pInitData, KernelInfoStruct * pKernelData)
{
	//���ð汾��Ϣ
	//pKernelData->bMaxVer=GAME_PLACE_MAX_VER;
	//pKernelData->bLessVer=GAME_PLACE_LESS_VER;

	//�������ݿ�

	//����ʹ�����ݿ�
	pKernelData->bLogonDataBase=false;//TRUE;
	pKernelData->bNativeDataBase=false;//TRUE;
	pKernelData->bStartSQLDataBase=false;//TRUE;

	//����ʹ������
	pKernelData->bStartTCPSocket=TRUE;
	pInitData->uListenPort=CENTER_SERVER_PORT;//13025
	pInitData->uMaxPeople=300;
	pInitData->iSocketSecretKey = SECRET_KEY;

	CString s;
	s.Format("���ķ��������ɹ�  Port:%d ",
		CENTER_SERVER_PORT );

	OutputFun(s.GetBuffer ());

	return true;
}
//SOCKET �ر�
bool CCenterServerManage::OnSocketClose(ULONG uAccessIP, UINT uSocketIndex, long int lConnectTime)
{
	return true;
}

void CCenterServerManage::RandAServer()
{
	m_ZServerManager.m_MainserverList.RandAServer (m_msgSendToClient.m_strMainserverIPAddr,
		m_msgSendToClient.m_iMainserverPort);
}

bool CCenterServerManage::CMainserverList::RandAServer(char* ipaddr,long& port)
{
	bool bb=false;
	static int curIndex=0;
	Lock();
	if(!m_List.IsEmpty())
	{
		//Z�����ؾ��⣬ƽ�����䷨
		static int curi=0;
		int count=m_List.GetCount ();//������IP�б��������
		long t=GetCurrentTime() + rand();//���ѡ��һ����

		int i=0;//����������ȡ�����ȳ˰ٷְ٣�Ȼ��ȡ������

		 POSITION pos=m_List.GetHeadPosition ();
		for(int j=0;j<m_List.GetCount ();j++)
		{
			Node* nd=(Node*)m_List.GetNext (pos);
			if(nd)
			{				
				if(i == curi)///�õ����������IP���͵��ͻ���
				{
					CString s=nd->IPAddr ;
					port=nd->Port ;
					memcpy(ipaddr,s.GetBuffer(s.GetLength ()),20);
					bb=true;
					break;
				}
			}
			i++;
		}
		//Z�����ؾ��⣬ƽ�����䷨

		curi++;
		if(curi>=m_List.GetCount()) 
			curi=0;
	}
	UnLock();
	return bb;
}


void CCenterServerManage::CMainserverList::clear()
{
	Lock();
	while(!m_List.IsEmpty())
	{
		Node* pdesk = (Node*)m_List.RemoveHead();
		delete pdesk;
	}
	m_List.RemoveAll();
	UnLock();
}

CCenterServerManage::CMainserverList::~CMainserverList()
{
	clear();
}

void CCenterServerManage::CMainserverList::LoadServerList(DWORD cfgHandle)
{
	clear();

	CString ss;
	for(int i=0;i<10;i++)
	{
		ss.Format("M_IPAddr%d",i+1);
		CString ip=cfgGetValue(cfgHandle,"GateServer",ss,"");
		if(ip=="")break;
		Node* nd=new Node();
		nd->IPAddr =ip;
		ss.Format("M_Port%d",i+1);
		nd->Port=cfgGetValue(cfgHandle,"GateServer",ss,0);
		ss.Format("M_id%d",i+1);
		nd->id=cfgGetValue(cfgHandle,"GateServer",ss,0);
		Lock();
		m_List.AddTail (nd);
		UnLock();
	}
}


//void CCenterServerManage::CMainserverList::ReadINIFile(CString TMLkey)
//{
//	clear();
//	CString s=CINIFile::GetAppPath ();
//	CINIFile f( s + "CenterServer.ini");
//	//int count=f.GetKeyVal ("www.TML.cn","MainserverListCount",0);//////������������
//	for(int i=0;i<10;i++)
//	{
//		CString s;
//		s.Format ("%d",i+1);
//		CString ip=f.GetKeyVal (TMLkey,"M_IPAddr"+s,"");
//		if (ip=="")break;
//		Node* nd=new Node();
//		nd->IPAddr =ip;
//		long port=f.GetKeyVal (TMLkey,"M_Port"+s,0);
//		nd->Port =port;
//		port=f.GetKeyVal (TMLkey,"M_id"+s,0);
//		nd->id  =port;
//		Lock();
//		  m_List.AddTail (nd);
//		UnLock();
//
////ԭ���㷨
//		//CString s;
//		//s.Format ("Mainserver%d",i+1);
//		//CString ip=f.GetKeyVal (s,"IPAddr","");
//		//Node* nd=new Node();
//		//nd->IPAddr =ip;
//		//long port=f.GetKeyVal (s,"Port",0);
//		//nd->Port =port;
//		//port=f.GetKeyVal (s,"id",0);
//		//nd->id  =port;
//		//Lock();
//		//  m_List.AddTail (nd);
//		//UnLock();
//
//	}
//
//}

CCenterServerManage::CMainserverList::CMainserverList()
{
	///srand( (unsigned)time( NULL ) );
	///InitializeCriticalSection(&cs);
   /// ReadINIFile();
}
/******************************************************************************************************/

//���캯��CCenterServerManage
CCenterServerModule::CCenterServerModule(void) 
{
	return;
}

//��������
CCenterServerModule::~CCenterServerModule(void)
{
	return;
}

//��ʼ������ 
bool CCenterServerModule::InitService(ManageInfoStruct * pInitData)
{
	try
	{
		return m_LogonManage.Init(pInitData,NULL);
	}
	catch (CAFCException * pException)	
	{ 
		pException->Delete();	
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	}
	catch (...)	
	{ 
		TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);
	}
	return false;
}

//ж�غ���
bool CCenterServerModule::UnInitService()
{
	try
	{
		return m_LogonManage.UnInit();
	}
	catch (CAFCException * pException)	{ pException->Delete();	TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);}
	catch (...) {TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);}
	return false;
}

//��ʼ���� 
bool CCenterServerModule::StartService(UINT &errCode)
{
	try
	{
		return m_LogonManage.Start();
	}
	catch (CAFCException * pException)	{ pException->Delete();TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);	}
	catch (...) {TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);}
	return false;
}

//ֹͣ���� 
bool CCenterServerModule::StoptService()
{
	try
	{
		return m_LogonManage.Stop();
	}
	catch (CAFCException * pException)	{ pException->Delete();TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);	}
	catch (...) {TRACE("CATCH:%s with %s\n",__FILE__,__FUNCTION__);}
	return false;
}

//ɾ������
bool CCenterServerModule::DeleteService()
{
	try	{ delete this; }
	catch (...) {}
	return true;
}

/******************************************************************************************************/
