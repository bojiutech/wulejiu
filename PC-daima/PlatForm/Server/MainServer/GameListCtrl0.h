#pragma once

/*******************************************************************************************************/

//��Ϸ�б�����
class CAFCGameListItem
{
	//���ݱ���
public:
	CPtrArray									m_ItemPtrArray;					//��������

	//��������
public:
	//��������
	CAFCGameListItem();
	CAFCGameListItem(CAFCGameListItem&);
	CAFCGameListItem& operator=(CAFCGameListItem&); 

	//��������
	virtual ~CAFCGameListItem();

	//���ܺ���
public:
	//������Ϸ����
	bool AddGameKind(ComKindInfo * pGameKind);
	//������Ϸ����
	bool AddGameName(ComNameInfo * pGameName);
	//������Ϸ����
	bool AddGameRoom(ComRoomInfo * pGameRoom);
};

/*******************************************************************************************************/

//��Ϸ��������
class CAFCKindItem : public CAFCGameListItem
{
	//��������
public:
	ComKindInfo								m_KindInfo;						//��������

	//��������
public:
	//���캯��
	CAFCKindItem() 
	{ 
		memset(&m_KindInfo,0,sizeof(m_KindInfo)); 
		m_KindInfo.Head.uSize=sizeof(m_KindInfo);
		m_KindInfo.Head.bDataType=GLK_GAME_KIND;
	};
	//��������
	virtual ~CAFCKindItem() {};
};

/*******************************************************************************************************/

//��Ϸ��������
class CAFCNameItem : public CAFCGameListItem
{
	//��������
public:
	///UINT										m_uOnLineCount;					//��������
	ComNameInfo								m_NameInfo;						//��������

	//��������
public:
	//���캯��
	CAFCNameItem() 
	{ 
//		m_uOnLineCount=0L;
		memset(&m_NameInfo,0,sizeof(m_NameInfo)); 
		m_NameInfo.Head.uSize=sizeof(m_NameInfo);
		m_NameInfo.Head.bDataType=GLK_GAME_NAME;
	};
	//��������
	virtual ~CAFCNameItem() {};
};

/*******************************************************************************************************/

//��Ϸ��������
class CAFCRoomItem : public CAFCGameListItem
{
	//��������
public:
	ComRoomInfo								m_RoomInfo;						//��������

	//��������
public:
	//���캯��
	CAFCRoomItem() 
	{ 
		memset(&m_RoomInfo,0,sizeof(m_RoomInfo)); 
		m_RoomInfo.Head.uSize=sizeof(m_RoomInfo);
		m_RoomInfo.Head.bDataType=GLK_GAME_ROOM;
	};
	CAFCRoomItem(CAFCRoomItem&);
	CAFCRoomItem& operator = (CAFCRoomItem &);
	//��������
	virtual ~CAFCRoomItem() {};
};

/*******************************************************************************************************/

//��Ϸ�ڲ�����
class CAFCInsideItem : public CAFCGameListItem
{
	//��������
public:
	GameInsideInfo								m_InsideInfo;					//�ڲ�����

	//��������
public:
	//���캯��
	CAFCInsideItem()
	{
		memset(&m_InsideInfo,0,sizeof(m_InsideInfo)); 
		m_InsideInfo.Head.uSize=sizeof(m_InsideInfo);
		m_InsideInfo.Head.bDataType=GLK_GAME_USE;
	}
	//��������
	virtual ~CAFCInsideItem() {};
};

/*******************************************************************************************************/

//��Ϸ�б������
class CServerGameListManage0
{
	//��������
protected:
	//���ݿ��߳�ʹ��
	DWORD										m_dwRoomCount;					//������Ŀ
	DWORD										m_dwNameCount;					//������Ŀ
	DWORD										m_dwKindCount;					//������Ŀ
	ComRoomInfo								* m_pRoomPtr;					//����ָ��
	ComNameInfo								* m_pNamePtr;					//����ָ��
	ComKindInfo								* m_pKindPtr;					//����ָ��
	
	//���ݹ����߳�ʹ��
	CPtrArray									m_NameArray;					//��Ϸ����
	CPtrArray									m_KindArray;					//��Ϸ����

	//��������
public:
	//���캯��
	CServerGameListManage0();
	CServerGameListManage0(CServerGameListManage0&);
	CServerGameListManage0 & operator =(CServerGameListManage0&);

	//��������
	virtual ~CServerGameListManage0();

	//���ܺ���
public:
	//��ȡ��Ϸ������Ŀ
	INT_PTR GetGameKindCount() { return m_KindArray.GetCount(); }
	//��ȡ�������� 
	INT_PTR FillOnLineCount(char * pOnLineBuffer, INT_PTR uBufferSize, INT_PTR uBeginPos, bool & bFinish);
	//��ȡ��Ϸ����
	INT_PTR FillGameKind(char * pKindBuffer, INT_PTR uBufferSize, INT_PTR uBeginPos, bool & bFinish);
	//��ȡ��Ϸ����
	INT_PTR FillGameName(char * pNamdBuffer, INT_PTR uBufferSize, INT_PTR uBeginPos, bool & bFinish);
	//��ȡ��������
	INT_PTR FillGameRoom(char * pRoomBuffer, INT_PTR uBufferSize, UINT uKindID, UINT uNameID, INT_PTR uBeginPos, bool & bFinish);

	//���º���
public:
	//������Ϸ�б����ݹ����̵߳��ã�
	bool UpdateGameList();
	//������Ϸ�б����ݿ��̵߳��ã�
	bool UpdateGameListBuffer(HANDLE hDatabase);

	//��������
public:
	//���������б�
	bool UpdateGameName(CAFCKindItem * pKindItem);
	//���·����б�
	bool UpdateGameRoom(CAFCNameItem * pNameItem);
	//Ѱ������
	CAFCKindItem * FindKindItem(UINT uKindID);
	//Ѱ������
	CAFCNameItem * FindNameItem(CAFCKindItem * pKindItem, UINT uNameID);
	//Ѱ�ҷ���
	CAFCRoomItem * FindRoomItem(CAFCNameItem * pNameItem, UINT uRoomID);
	ComRoomInfo *FindRoomInfo(int uRoomID);
};

/*******************************************************************************************************/
