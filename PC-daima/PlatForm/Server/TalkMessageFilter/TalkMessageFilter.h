#pragma once
#include <list>
using namespace std;
/********************************************************************
	created:	2009/03/16
	created:	16:3:2009   18:05
	filename: 	\�ͻ������\TalkMessageFilter\TalkMessageFilter.h
	file path:	\�ͻ������\TalkMessageFilter
	file base:	TalkMessageFilter
	file ext:	h
	author:		Administrator
	
	purpose:  ���������˹���	
    TalkMessageFilter   version:  1.0   ��  date: 03/16/2009  
    Copyright (C) 2009 - All Rights Reserved

*********************************************************************/



class CTalkMessageFilter
{
public:
	CTalkMessageFilter(void);
	~CTalkMessageFilter(void);
	//���ز���Ҫ���˵�����
    void LoadFilterMessage(TCHAR* pstrAppPath);
	//�ж��Ƿ������Ҫ���˵�����
	bool IsAllowableTalk(TCHAR* pTalkContent,UINT uSize);
	const CHAR* GetReplaceContent() const {return m_strReplaceContent;}
private:
	list<TCHAR*> m_lsUnAllowableWord;
	DWORD m_dwFileHandle;

	CHAR   m_strReplaceContent[1024];

};
