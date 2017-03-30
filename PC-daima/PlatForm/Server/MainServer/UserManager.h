#pragma once

#include <vector>
#include <map>
#include <list>
using namespace std;

typedef struct user
{
	int iSocketIndex;		///< Socket�˿����
	int UserID;				///< ���ID
	int iAddFriendType;
	bool bIsGameManager;	///< �Ƿ���Ϸ����Ա
	bool bIsValid;
	char UserName[50];
	int	 iVipTime;			///vip��Чʱ��
	user() {ZeroMemory(this, sizeof(user));}
}USERS, *LPUSER;


class CUserManager
{
public:
	CUserManager(void);
public:
	~CUserManager(void);
public:
	vector<USERS>	m_dataPloor;		//�൱���ڴ��һ��
	map<int, LPUSER> m_Users;			//�洢�û�����
	int				m_iSize;
public:
	void Add(int index, LPUSER data);
	void Del(int index);
	int Find(int index);
};
