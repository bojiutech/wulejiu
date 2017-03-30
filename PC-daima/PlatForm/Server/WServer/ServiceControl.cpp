#include "Stdafx.h"
#include "Resource.h"
#include "MainFrm.h"
#include "ServiceManage.h"
#include "ServiceControl.h"
#include "SetupDialog.h"
#include <SYS/Stat.h>
//�궨��
#define BT_WIDTH						80							//��ť���
#define BT_HEIGHT						23							//��ť�߶�

BEGIN_MESSAGE_MAP(CBaseDialog, CDialog)
END_MESSAGE_MAP()

BEGIN_MESSAGE_MAP(CServiceControl, CBaseDialog)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_START, OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, OnBnClickedStop)
	ON_BN_CLICKED(IDC_SET_COM, OnBnClickedSetCom)
/*	ON_BN_CLICKED(IDC_INSTANCELL, OnBnClickedInstancell)
	ON_BN_CLICKED(IDC_UNINSTANLL, OnBnClickedUninstanll)
	ON_BN_CLICKED(IDC_DELETE, OnBnClickedDelete)*/
	ON_BN_CLICKED(IDC_RE_LOAD, &CServiceControl::OnBnClickedReLoad)
	ON_BN_CLICKED(IDC_UPDATE_COM, &CServiceControl::OnBnClickedUpdateCom)
	ON_BN_CLICKED(IDC_SETUP, &CServiceControl::OnBnClickedSetup)
	ON_BN_CLICKED(IDC_MOTIF, &CServiceControl::OnBnClickedMotif)
	ON_BN_CLICKED(IDC_REMOVE, &CServiceControl::OnBnClickedRemove)
	ON_BN_CLICKED(IDC_START_ALL, &CServiceControl::OnBnClickedStartAll)
	ON_BN_CLICKED(IDC_STOP_ALL, &CServiceControl::OnBnClickedStopAll)
	ON_BN_CLICKED(IDC_DELETE, &CServiceControl::OnBnClickedDelete)
	ON_BN_CLICKED(IDC_CHANGE, &CServiceControl::OnBnClickedChange)
	ON_BN_CLICKED(IDC_INFO, &CServiceControl::OnBnClickedInfo)
	ON_BN_CLICKED(IDC_MANAGE, &CServiceControl::OnBnClickedManage)
	ON_BN_CLICKED(IDC_RELOAD_ROOMLIST, &CServiceControl::OnBnClickedReloadRoomlist)
	ON_WM_TIMER()
END_MESSAGE_MAP()

/********************************************************************************************************/

//���캯��
CBaseDialog::CBaseDialog(UINT uTemplate, CWnd * pParent) : CDialog(uTemplate,pParent)
{
}

//��������
CBaseDialog::~CBaseDialog()
{
}

//��ȡ����
bool CBaseDialog::SafeGetClientRect(UINT uID, CRect & ClientRect)
{
	CWnd * pControlWnd=GetDlgItem(uID);
	if ((pControlWnd!=NULL)&&(pControlWnd->GetSafeHwnd())) 
	{
		pControlWnd->GetClientRect(&ClientRect);
		return true;
	}
	ClientRect.SetRectEmpty();
	return false;
}

//��ȡ����
bool CBaseDialog::SafeGetClientRect(CWnd * pControlWnd, CRect & ClientRect)
{
	if ((pControlWnd!=NULL)&&(pControlWnd->GetSafeHwnd())) 
	{
		pControlWnd->GetClientRect(&ClientRect);
		return true;
	}
	ClientRect.SetRectEmpty();
	return false;
}

//�ƶ�����
bool CBaseDialog::SafeMoveWindow(UINT uID, int x, int y, int iWidth, int iHeight)
{
	CWnd * pControlWnd=GetDlgItem(uID);
	if ((pControlWnd!=NULL)&&(pControlWnd->GetSafeHwnd())) 
	{
		if ((iWidth<=0)||(iHeight<=0)) iWidth=0,iHeight=0;
		pControlWnd->MoveWindow(x,y,iWidth,iHeight);
		return true;
	}
	return false;
}

//�ƶ�����
bool CBaseDialog::SafeMoveWindow(CWnd * pControlWnd, int x, int y, int iWidth, int iHeight)
{
	if ((pControlWnd!=NULL)&&(pControlWnd->GetSafeHwnd())) 
	{
		if ((iWidth<=0)||(iHeight<=0)) iWidth=0,iHeight=0;
		pControlWnd->MoveWindow(x,y,iWidth,iHeight);
		return true;
	}
	return false;
}

/********************************************************************************************************/

//���캯��
CServiceControl::CServiceControl() : CBaseDialog(IDD_SERVICE_CONTROL)
{
}

//��������
CServiceControl::~CServiceControl()
{
}

//DDX/DDV ֧��
void CServiceControl::DoDataExchange(CDataExchange * pDX)
{
	__super::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_START_LIST, m_StartList);
	DDX_Control(pDX, IDC_INSTANLL_LIST, m_InstallList);
}

//��ʼ������
BOOL CServiceControl::OnInitDialog()
{
	__super::OnInitDialog();
//�����б�
//GetDlgItem(IDC_INSTANLL_LIST)->ShowWindow(FALSE);
//GetDlgItem(IDC_START_LIST)->ShowWindow(FALSE);
	 //////��Ȩ��Ȩ��Ȩ��Ȩ��Ȩ��Ȩ��Ȩ��Ȩ
//CStatic* pStatic1=new CStatic();
//pStatic1->Create(TMLcopyright,WS_CHILD|WS_VISIBLE,CRect(100,0,450,10),this,10101);
//SetWindowTitle(TMLcopyright);

	//��ʼ������б�
	CListCtrl * pList=(CListCtrl *)GetDlgItem(IDC_INSTANLL_LIST);
	pList->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);
	pList->InsertColumn(0,TEXT("��� ID"),LVCFMT_LEFT,60);
	pList->InsertColumn(1,TEXT("�������"),LVCFMT_LEFT,100);
	pList->InsertColumn(2,TEXT("���״̬"),LVCFMT_LEFT,80);
	pList->InsertColumn(3,TEXT("�汾����"),LVCFMT_LEFT,60);
	pList->InsertColumn(4,TEXT("��Ϸ����"),LVCFMT_LEFT,60);
	pList->InsertColumn(5,TEXT("Ĭ����Ϣ��"),LVCFMT_LEFT,100);
	pList->InsertColumn(6,TEXT("ģ������"),LVCFMT_LEFT,150);
//	pList->InsertColumn(7,TEXT("��ע��Ϣ"),LVCFMT_LEFT,300);
//	pList->InsertColumn(7,TEXT("��������"),LVCFMT_LEFT,300);

	//��ʼ�������б�
	pList=(CListCtrl *)GetDlgItem(IDC_START_LIST);
	pList->SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE,LVS_EX_FULLROWSELECT,LVS_EX_FULLROWSELECT);
	pList->InsertColumn(0,TEXT("�������ʵ��ID"),LVCFMT_LEFT,60);
	pList->InsertColumn(1,TEXT("�������ʵ������"),LVCFMT_LEFT,120);
	pList->InsertColumn(2,TEXT("�������"),LVCFMT_LEFT,100);
	pList->InsertColumn(3,TEXT("����״̬"),LVCFMT_LEFT,60);
	pList->InsertColumn(4,TEXT("�������"),LVCFMT_LEFT,60);
	pList->InsertColumn(5,TEXT("�Ƿ�����"),LVCFMT_LEFT,60);
	pList->InsertColumn(6,TEXT("�����ַ"),LVCFMT_LEFT,100);
	pList->InsertColumn(7,TEXT("�����˿�"),LVCFMT_LEFT,60);
	pList->InsertColumn(8,TEXT("ʵ������ҵ����Ŀ"),LVCFMT_LEFT,60);
	pList->InsertColumn(9,TEXT("��������"),LVCFMT_LEFT,60);
	pList->InsertColumn(10,TEXT("�������"),LVCFMT_LEFT,60);
	pList->InsertColumn(11,TEXT("���ٷ���"),LVCFMT_LEFT,60);
	pList->InsertColumn(12,TEXT("��������"),LVCFMT_LEFT,60);
	pList->InsertColumn(13,TEXT("������"),LVCFMT_LEFT,60);
	pList->InsertColumn(14,TEXT("�������"),LVCFMT_LEFT,60);
	pList->InsertColumn(15,TEXT("����Ȩ��"),LVCFMT_LEFT,60);
	pList->InsertColumn(16,TEXT("�������ݿ� IP"),LVCFMT_LEFT,0);
	pList->InsertColumn(17,TEXT("��½���ݿ� IP"),LVCFMT_LEFT,0);
	pList->InsertColumn(18,TEXT("�������ݿ� IP"),LVCFMT_LEFT,0);
	pList->InsertColumn(19,TEXT("���� ID"),LVCFMT_LEFT,60);
	pList->InsertColumn(20,TEXT("���� ID"),LVCFMT_LEFT,60);
	pList->InsertColumn(21,TEXT("���� ID"),LVCFMT_LEFT,60);
	pList->InsertColumn(22,TEXT("��Ϸ��Ϣ��"),LVCFMT_LEFT,100);
	pList->InsertColumn(23,TEXT("ͬ����������"),LVCFMT_LEFT,100);
	pList->InsertColumn(24,TEXT("���Ƶ�ַ����"),LVCFMT_LEFT,100);
	pList->InsertColumn(25,TEXT("�����û���½����"),LVCFMT_LEFT,100);
	pList->InsertColumn(26,TEXT("���� ID"),LVCFMT_LEFT,60);
	pList->InsertColumn(27,TEXT("��� ID"),LVCFMT_LEFT,60);
	pList->InsertColumn(28,TEXT("ģ������"),LVCFMT_LEFT,0);
	pList->InsertColumn(29,TEXT("��ע��Ϣ"),LVCFMT_LEFT,0);
	pList->InsertColumn(30,TEXT("��Ϸ����"),LVCFMT_LEFT,60);
	pList->InsertColumn(31,TEXT("ֹͣ��½"),LVCFMT_LEFT,60);
	pList->InsertColumn(32,TEXT("ֹͣ����ʱ��"),LVCFMT_LEFT,100);
	pList->InsertColumn(33,TEXT("˰�ձ���/100"),LVCFMT_LEFT,60);
	pList->InsertColumn(34,TEXT("����"),LVCFMT_LEFT,60);


	//(CButton *)GetDlgItem(IDC_START)->EnableWindow(false);
	//(CButton *)GetDlgItem(IDC_STOP)->EnableWindow(false);
	//(CButton *)GetDlgItem(IDC_SET_COM)->EnableWindow(false);


	///"��������",IDC_SET_COM

	//"��������",IDC_START,359,119,56,16
   // PUSHBUTTON      "ֹͣ����",IDC_STOP
    SetTimer(1,1000*60*30,NULL);
	SetTimer(10,1000*60*60*3,NULL);
	return TRUE;
}

//λ�ñ仯����
void CServiceControl::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);
	
	//�ƶ��ؼ�
	SafeMoveWindow(IDC_INSTANLLED_FRAME,5,2,cx-10,cy/3-7);
	SafeMoveWindow(IDC_START_FRAME,5,cy/3,cx-10,cy*2/3-5);
	SafeMoveWindow(IDC_INSTANLL_LIST,15,18,cx-120,cy/3-30);
	SafeMoveWindow(IDC_START_LIST,15,cy/3+18,cx-120,cy*2/3-30);
	
	//�ƶ���ť
	SafeMoveWindow(IDC_SET_COM,cx-95,18,BT_WIDTH,BT_HEIGHT);
	SafeMoveWindow(IDC_UPDATE_COM,cx-95,18+BT_HEIGHT+5,BT_WIDTH,BT_HEIGHT);
	SafeMoveWindow(IDC_SETUP,cx-95,18+BT_HEIGHT*2+10,BT_WIDTH,BT_HEIGHT);
	SafeMoveWindow(IDC_RE_LOAD,cx-95,18+BT_HEIGHT*3+15,BT_WIDTH,BT_HEIGHT);
	SafeMoveWindow(IDC_MOTIF,cx-95,18+BT_HEIGHT*4+20,BT_WIDTH,BT_HEIGHT);
	SafeMoveWindow(IDC_DELDLL,cx-95,18+BT_HEIGHT*5+25,BT_WIDTH,BT_HEIGHT);
	SafeMoveWindow(IDC_REMOVE,cx-95,18+BT_HEIGHT*6+30,BT_WIDTH,BT_HEIGHT);

	SafeMoveWindow(IDC_START,cx-95,cy/3+88,BT_WIDTH,BT_HEIGHT);
	SafeMoveWindow(IDC_STOP,cx-95,cy/3+88+BT_HEIGHT+5,BT_WIDTH,BT_HEIGHT);
	SafeMoveWindow(IDC_START_ALL,cx-95,cy/3+88+BT_HEIGHT*2+10,BT_WIDTH,BT_HEIGHT);
	SafeMoveWindow(IDC_STOP_ALL,cx-95,cy/3+88+BT_HEIGHT*3+15,BT_WIDTH,BT_HEIGHT);
	SafeMoveWindow(IDC_DELETE,cx-95,cy/3+88+BT_HEIGHT*4+20,BT_WIDTH,BT_HEIGHT);
	SafeMoveWindow(IDC_CHANGE,cx-95,cy/3+88+BT_HEIGHT*5+25,BT_WIDTH,BT_HEIGHT);
	SafeMoveWindow(IDC_INFO,cx-95,cy/3+88+BT_HEIGHT*6+30,BT_WIDTH,BT_HEIGHT);
	SafeMoveWindow(IDC_MANAGE,cx-95,cy/3+88+BT_HEIGHT*7+35,BT_WIDTH,BT_HEIGHT);
	SafeMoveWindow(IDC_RELOAD_ROOMLIST,cx-95,cy/3+88+BT_HEIGHT*8+40,BT_WIDTH,BT_HEIGHT);

	return;
}

//ֹͣ��Ϸ����
void CServiceControl::OnBnClickedStop()
{
	//Ч������
	POSITION SelectPos;
	SelectPos=m_StartList.GetFirstSelectedItemPosition();
	if (SelectPos==NULL)
	{
		AfxMessageBox(TEXT("�������ұߵ��������ʵ���б���ѡ��Ҫֹͣ���������ʵ�������"),MB_ICONQUESTION);
		return;
	}
	int iItem=m_StartList.GetNextSelectedItem(SelectPos);
	SC_GameRoomInitStruct * pComRoomInfo=(SC_GameRoomInitStruct *)m_StartList.GetItemData(iItem);
	if (pComRoomInfo==NULL)
	{
		AfxMessageBox(TEXT("�������ʵ����Ϣ��ȡ�����������ʵ��ֹͣʧ�ܣ�"),MB_ICONQUESTION);
		return;
	}

	//ֹͣ��Ϸ����
	if (g_Service.StopGameRoom(pComRoomInfo)==false)
	{
		CString strMessage;
		strMessage.Format(TEXT("ֹͣʧ�ܣ�%s"),g_Service.GetLastErrorMsg());
		AfxMessageBox(strMessage,MB_ICONSTOP);
		return;
	}

	//�޸���ʾ
	//g_Service.UpdateRoomListInfo(&m_StartList);
	m_StartList.SetFocus();
	m_StartList.SetItemText(iItem,3,TEXT("ֹͣ"));

	return;
}

//������Ϸ����
void CServiceControl::OnBnClickedStart()
{
	//Ч������
	POSITION SelectPos;
	SelectPos=m_StartList.GetFirstSelectedItemPosition();
	if (SelectPos==NULL)
	{
		AfxMessageBox(TEXT("�������ұߵ��������ʵ���б���ѡ��Ҫ�������������ʵ�������"),MB_ICONQUESTION);
		return;
	}
	int iItem=m_StartList.GetNextSelectedItem(SelectPos);
	SC_GameRoomInitStruct * pComRoomInfo=(SC_GameRoomInitStruct *)m_StartList.GetItemData(iItem);
	if (pComRoomInfo==NULL)
	{
		AfxMessageBox(TEXT("�������ʵ����Ϣ��ȡ�����������ʵ������ʧ�ܣ�"),MB_ICONQUESTION);
		return;
	}

#ifdef BZ_LICENSE
	if(coreGetGameLicense(pComRoomInfo->ServiceInfo.uNameID)==pComRoomInfo->ServiceInfo.uNameID)
#else
	if (true)
#endif // BZ_LICENSE
	{
	//��������
	if(!g_Service.bGetServiceInfo(pComRoomInfo))
	{
		CString strMessage;
		strMessage.Format(TEXT("�����Ӧ�Ŀ�%s�����ڣ�%s"),pComRoomInfo->ServiceInfo.szDLLFileName,g_Service.GetLastErrorMsg());
		AfxMessageBox(strMessage,MB_ICONSTOP);
		return;
	}
	if (!g_Service.StartGameRoom(pComRoomInfo))
	{
		CString strMessage;
		strMessage.Format(TEXT("�������������ʧ�ܣ�%s"),g_Service.GetLastErrorMsg());
		AfxMessageBox(strMessage,MB_ICONSTOP);
		return;
	}
	//�޸���ʾ
	m_StartList.SetFocus();
	m_StartList.SetItemText(iItem,3,TEXT("����"));
	}
	else
	{
		CString s=pComRoomInfo->ServiceInfo.szGameName;
		if(s.Left(7)!="δ��֤_")
		{
			s="δ��֤_"+s;
			if(s.GetLength()>60)
				s=s.Left(60);
		}	
		strcpy(pComRoomInfo->ServiceInfo.szGameName,s);
		m_StartList.SetItemText(iItem,3,TEXT("����֤"));
	}

	

	return;
}

//������Ϸ���
void CServiceControl::OnBnClickedSetCom()
{

	//��������Ի��� 
	CSetupDialog sd;
	if(sd.DoModal()==IDOK)
	{
		SC_ServiceInfoStruct p;
		lstrcpy(p.ServiceInfo.szDLLFileName,sd.dllFileName);
		lstrcpy(p.ServiceInfo.szDllNote,sd.dllNote);
		lstrcpy(p.ServiceInfo.szGameName,sd.gameName);
		lstrcpy(p.ServiceInfo.szGameTable, sd.tableDbName);
		lstrcpy(p.ServiceInfo.szWriter,sd.writer);

		p.ServiceInfo.uDeskPeople=sd.deskPeople;
		p.ServiceInfo.uNameID = sd.nameID;
		p.ServiceInfo.uServiceVer = sd.sver;
		p.ServiceInfo.uSupportType = sd.supportType;
		p.uServiceID = sd.serInfoID;
		p.uServiceStation = 0;
		
		/*����
		wsprintf(a,"%d,%d,%d,%d,%d,%d,%s,%s,%s,%s",p.ServiceInfo.uDeskPeople,p.
		ServiceInfo.uNameID,p.ServiceInfo.uServiceVer,p.ServiceInfo.uSupportType ,p.uServiceID,	p.uServiceStation,p.ServiceInfo.szDLLFileName,p.ServiceInfo.szDllNote,p.ServiceInfo.szGameName,p.ServiceInfo.szGameTable);
		AfxMessageBox(a);
		*/

		if(!g_Service.SetupCom(&m_InstallList,p))
			AfxMessageBox(TEXT("д���ݿ�ʧ�ܣ���������д�����ݣ�"),MB_ICONQUESTION);
	}
	return;
}

/********************************************************************************************************/

//ˢ������б�
void CServiceControl::OnBnClickedReLoad()
{
	// TODO: Add your control notification handler code here
	g_Service.UpdateComDLLList(&m_InstallList);
	return;
}

//���µ���Ϸ���
void CServiceControl::OnBnClickedUpdateCom()
{
	// TODO: Add your control notification handler code here
	//ѡ��Ҫ���µ���Ϸ���
	POSITION SelectPos;
	SelectPos=m_InstallList.GetFirstSelectedItemPosition();
	if (SelectPos==NULL) 
	{
		AfxMessageBox(TEXT("�������ұߵ�����б���ѡ��Ҫ���µ���������"),MB_ICONQUESTION);
		return;
	}
	if(AfxMessageBox("������Ϸ������Զ�ֹͣ����Ϸ�����з��䣬�����ڸ���ǰ֪ͨ��ط��������������Ҳ�����Ҫ���µĶ�̬���ļ�\n׼�����˸�����",IDOK)==IDOK)
	{
		//�õ�Ҫ���µ���Ϸ�����Ϣ�ṹ��
		SC_ServiceInfoStruct * pServiceInfo=(SC_ServiceInfoStruct *)m_InstallList.GetItemData(m_InstallList.GetNextSelectedItem(SelectPos));
		//stop ����ķ���
		for(int i=0;i<g_Service.m_ComRoomInfo.GetSize();i++)
		{
			SC_GameRoomInitStruct * p=(SC_GameRoomInitStruct *)g_Service.m_ComRoomInfo.GetAt(i);
			if(!p)continue;
			if(p->uServiceID==pServiceInfo->uServiceID) 
			{
				if (!g_Service.StopGameRoom(p))
				{
					CString strMessage;
					strMessage.Format(TEXT("ֹͣ����ʧ�ܣ�%s"),g_Service.GetLastErrorMsg());
					AfxMessageBox(strMessage,MB_ICONSTOP);
					continue;
				}
				//�޸���ʾ
				g_Service.UpdateRoomListInfo(&m_StartList);
			}
		}

		if(!g_Service.CopyNewCom(pServiceInfo))//��װ���
		{
			AfxMessageBox("��������Ӧ�ķ��䣡");
			return;
		}
		OnBnClickedReLoad();	
		
		//start ���������
		for(int i=0;i<g_Service.m_ComRoomInfo.GetSize();i++)
		{
			SC_GameRoomInitStruct * p=(SC_GameRoomInitStruct *)g_Service.m_ComRoomInfo.GetAt(i);
			if(!p)continue;
			if(p->uServiceID==pServiceInfo->uServiceID) 
			{
				if(!g_Service.bGetServiceInfo(p))
				{
					CString strMessage;
					strMessage.Format(TEXT("�����Ӧ�Ŀ�%s�����ڣ�%s"),p->ServiceInfo.szDLLFileName,g_Service.GetLastErrorMsg());
					AfxMessageBox(strMessage,MB_ICONSTOP);
					continue;
				}
				if (!g_Service.StartGameRoom(p))
				{
					CString strMessage;
					strMessage.Format(TEXT("�������������ʧ�ܣ�%s"),g_Service.GetLastErrorMsg());
					AfxMessageBox(strMessage,MB_ICONSTOP);
					continue;
				}
				//�޸���ʾ
				g_Service.UpdateRoomListInfo(&m_StartList);
			}
		}
	};
	return;
}

//��װδ��װ���
void CServiceControl::OnBnClickedSetup()
{
	POSITION SelectPos;
	SelectPos=m_InstallList.GetFirstSelectedItemPosition();
	if (SelectPos==NULL) 
	{
		AfxMessageBox(TEXT("�������ұߵ�����б���ѡ��Ҫ���µ���������"),MB_ICONQUESTION);
		return;
	}
	SC_ServiceInfoStruct * pServiceInfo=(SC_ServiceInfoStruct *)m_InstallList.GetItemData(m_InstallList.GetNextSelectedItem(SelectPos));
	if(pServiceInfo->uServiceStation!=0)//��װ
	{
		AfxMessageBox("ֻ�ܰ�װδ��װ�����������ѡ��");
		return;
	}
	if(g_Service.CopyNewCom(pServiceInfo))//����Ҫ��װ���������Ŀ¼
	{
			AfxMessageBox("��װ���ʧ��");
			OnBnClickedReLoad();
	}
	return;
	// TODO: Add your control notification handler code here
}

//�޸������Ϣ
void CServiceControl::OnBnClickedMotif()
{
	// TODO: Add your control notification handler code here
	POSITION SelectPos;
	SelectPos=m_InstallList.GetFirstSelectedItemPosition();
	if (SelectPos==NULL) 
	{
		AfxMessageBox(TEXT("�������ұߵ�����б���ѡ��Ҫ���µ���������"),MB_ICONQUESTION);
		return;
	}
	SC_ServiceInfoStruct * avantp=(SC_ServiceInfoStruct *)m_InstallList.GetItemData(m_InstallList.GetNextSelectedItem(SelectPos));
	//������Ϣ,������д
	CSetupDialog sd;
	sd.serInfoID = avantp->uServiceID;
	sd.supportType =avantp->ServiceInfo.uSupportType;
	sd.sver = avantp->ServiceInfo.uServiceVer;
	sd.deskPeople = avantp->ServiceInfo.uDeskPeople;
	sd.dllFileName=avantp->ServiceInfo.szDLLFileName;
	sd.dllNote=avantp->ServiceInfo.szDllNote;
	sd.gameName=avantp->ServiceInfo.szGameName;
	sd.tableDbName=avantp->ServiceInfo.szGameTable;
	sd.writer="szbzw";

	AfxMessageBox("���ȷ���������޸ĶԻ���,,ע��serInfoID�������޸�.ǿ���޸���Ч!");
	if(sd.DoModal()==IDOK)
	{
		if(AfxMessageBox("��ȷ��Ҫ�޸���?",IDOK)!=IDOK)
			return;
		//TCHAR a[111];
		SC_ServiceInfoStruct p;
		lstrcpy(p.ServiceInfo.szDLLFileName,sd.dllFileName);
		lstrcpy(p.ServiceInfo.szDllNote,sd.dllNote);
		lstrcpy(p.ServiceInfo.szGameName,sd.gameName);
		lstrcpy(p.ServiceInfo.szGameTable, sd.tableDbName);
		lstrcpy(p.ServiceInfo.szWriter,sd.writer);

		p.ServiceInfo.uDeskPeople=sd.deskPeople;
		p.ServiceInfo.uNameID = sd.nameID;
		p.ServiceInfo.uServiceVer = sd.sver;
		p.ServiceInfo.uSupportType = sd.supportType;
		p.uServiceStation = 0;
		
		/*����
		wsprintf(a,"%d,%d,%d,%d,%d,%d,%s,%s,%s,%s",p.ServiceInfo.uDeskPeople,p.ServiceInfo.uNameID,
		p.ServiceInfo.uServiceVer,p.ServiceInfo.uSupportType ,p.uServiceID,	p.uServiceStation,
		p.ServiceInfo.szDLLFileName,p.ServiceInfo.szDllNote,p.ServiceInfo.szGameName,p.ServiceInfo.szGameTable);
		AfxMessageBox(a);
		*/
		if(!g_Service.ModifCom(&m_InstallList,avantp,p))//avantp���޸�ǰ������,p���޸ĺ������
			AfxMessageBox(TEXT("д���ݿ�ʧ�ܣ���������д�����ݣ�"),MB_ICONQUESTION);
	}
	return;
}

void CServiceControl::OnBnClickedRemove()
{
	// TODO: Add your control notification handler code here
	POSITION SelectPos;
	SelectPos=m_InstallList.GetFirstSelectedItemPosition();
	if (SelectPos==NULL) 
	{
		AfxMessageBox(TEXT("�������ұߵ�����б���ѡ��Ҫ���µ���������"),MB_ICONQUESTION);
		return;
	}
	SC_ServiceInfoStruct * pServiceInfo=(SC_ServiceInfoStruct *)m_InstallList.GetItemData(m_InstallList.GetNextSelectedItem(SelectPos));
	if(AfxMessageBox("ȷ��Ҫ�����ǰ��¼��?��ͬʱɾ�������ݿ�ServerDllInfo����Ķ�Ӧ��!\nע:�˲�����ɾ���κ�*Srv.DLL�ļ�,Ҫɾ��ĳ��*Srv.DLL�밴<ɾ����̬��>��ť",IDOK)==IDOK)
		g_Service.RemoveDLLCom(&m_InstallList,pServiceInfo);
}

//�������з���
void CServiceControl::OnBnClickedStartAll()
{
	// TODO: Add your control notification handler code here
	//��������
	for(int i=0;i<g_Service.m_ComRoomInfo.GetSize();i++)
	{
		SC_GameRoomInitStruct *p;
		p = (SC_GameRoomInitStruct*) g_Service.m_ComRoomInfo.GetAt(i);
		if(p->hDllInstance!=NULL||p->pIManageService!=NULL)
			continue;
	#ifdef BZ_LICENSE
		if(coreGetGameLicense(p->ServiceInfo.uNameID)==p->ServiceInfo.uNameID)
	#else
		if (true)
	#endif // BZ_LICENSE
		{
		if(!g_Service.bGetServiceInfo(p))
		{
			CString strMessage;
			strMessage.Format(TEXT("�����Ӧ�Ŀ�%s�����ڣ�%s"),p->ServiceInfo.szDLLFileName,g_Service.GetLastErrorMsg());
			AfxMessageBox(strMessage,MB_ICONSTOP);
			continue;
		}
		if (!g_Service.StartGameRoom(p))
		{
			CString strMessage;
			strMessage.Format(TEXT("�����������ʧ�ܣ�%s"),g_Service.GetLastErrorMsg());
			AfxMessageBox(strMessage,MB_ICONSTOP);
			}
		}
		else
		{
			CString s=p->ServiceInfo.szGameName;
			if(s.Left(7)!="δ��֤_")
			{
				s="δ��֤_"+s;
				if(s.GetLength()>60)
					s=s.Left(60);
			}	
			strcpy(p->ServiceInfo.szGameName,s);
		}
	}
	
	//�޸���ʾ
	g_Service.UpdateRoomListInfo(&m_StartList);
	
	return;
}


//ֹͣ���з���
void CServiceControl::OnBnClickedStopAll()
{
	// TODO: Add your control notification handler code here
	if(AfxMessageBox("�Ƿ�ֹͣ������Ϸ��",IDOK)==IDOK)
	{
		for(int i=0;i<=g_Service.m_ComRoomInfo.GetUpperBound();i++)
		{
			SC_GameRoomInitStruct *p;
			p = (SC_GameRoomInitStruct*) g_Service.m_ComRoomInfo.GetAt(i);
			if(p->hDllInstance==NULL||p->pIManageService==NULL)
				continue;
			if (!g_Service.StopGameRoom(p))
			{
				CString strMessage;
				strMessage.Format(TEXT("ֹͣ�������ʧ�ܣ�%s"),g_Service.GetLastErrorMsg());
				AfxMessageBox(strMessage,MB_ICONSTOP);
			}
		}
		//�޸���ʾ
		g_Service.UpdateRoomListInfo(&m_StartList);
	}
}

void CServiceControl::OnBnClickedDelete()
{
	// TODO: Add your control notification handler code here
	POSITION SelectPos;
	SelectPos=m_StartList.GetFirstSelectedItemPosition();
	if (SelectPos==NULL) 
	{
		AfxMessageBox(TEXT("�������ұߵ�����б���ѡ��Ҫ���µ���������"),MB_ICONQUESTION);
		return;
	}
	SC_GameRoomInitStruct  * p=(SC_GameRoomInitStruct *)m_StartList.GetItemData(m_StartList.GetNextSelectedItem(SelectPos));
	if(p->hDllInstance!=NULL||p->pIManageService!=NULL)
	{
		AfxMessageBox("��ֹͣ����");
		return;
	}
	if(AfxMessageBox("ȷ��Ҫɾ����",IDOK)==IDOK)
	{
		g_Service.DeleteGameRoomInfo(p);
		g_Service.UpdateRoomListInfo(&m_StartList);
	}
}

//���ӷ���
void CServiceControl::OnBnClickedChange()
{

}

//�޸ķ�����Ϣ
void CServiceControl::OnBnClickedInfo()
{
	// TODO: Add your control notification handler code here
}


//������
void CServiceControl::OnBnClickedManage()
{
	// TODO: Add your control notification handler code here
}

//ˢ�·����б�
void CServiceControl::OnBnClickedReloadRoomlist()
{
	g_Service.GetRoomListInfo();
	g_Service.UpdateRoomListInfo(&m_StartList);
	// TODO: Add your control notification handler code here
}

void CServiceControl::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	//AfxMessageBox("ok");
    if(nIDEvent == 1)
		g_Service.CountOnLinePeople(&m_InstallList,&m_StartList);

	CBaseDialog::OnTimer(nIDEvent);
}

BOOL CServiceControl::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message==WM_KEYDOWN)
	{
		if(pMsg->wParam==VK_RETURN || pMsg->wParam==VK_ESCAPE)
			return TRUE;
	}

	return CBaseDialog::PreTranslateMessage(pMsg);
}
