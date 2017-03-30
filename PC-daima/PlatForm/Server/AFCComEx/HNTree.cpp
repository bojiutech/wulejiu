#include "stdafx.h"
#include "HNTree.h"
#include<iostream>

#define PACE 2    //�����Ҫ����Ӣ�Ļ���Ӣ�Ľ�ϵ��������PACE��Ϊ1�����������Ҫ�������޸�

string endchar = "@";

HNTreeNode* HNTree::insert(string& keyword) 
{
	return insert(&m_emptyRoot, keyword);
}

HNTreeNode* HNTree::insert(const char* keyword)
{
	string wordstr(keyword);
	return insert(wordstr);
}


HNTreeNode* HNTree::insert(HNTreeNode* parent, string& keyword)
{
	if(keyword.size()==0)
		return NULL;

	int ipace;
	const char *a = keyword.c_str();
	if((a[0]>='a'&&a[0]<='z')||
		(a[0]>='A'&&a[0]<='Z')||
		(a[0]>='0'&&a[0]<='9')||
		a[0]=='\''||a[0]=='-'||a[0]=='*'||a[0]=='&'||a[0]==' '||a[0]=='.'||a[0]=='~'||a[0]=='('||a[0]==')'||a[0]=='?'||a[0]=='/'||a[0]=='_'||a[0]=='@')
	{
		ipace=1;
	}
	else
	{
		ipace=2;
	}

	string firstChar=keyword.substr(0,ipace);
	HNTreeNode* firstNode = parent->findChild(firstChar);
	if(firstNode==NULL)
		return insertBranch(parent,keyword);
	string restChar=keyword.substr(ipace,keyword.size());
	return insert(firstNode,restChar);
}

HNTreeNode* HNTree::insertBranch(HNTreeNode* parent,string& keyword)
{
	int ipace;
	const char *a = keyword.c_str();
	if((a[0]>='a'&&a[0]<='z')||
		(a[0]>='A'&&a[0]<='Z')||
		(a[0]>='0'&&a[0]<='9')||
		a[0]=='\''||a[0]=='-'||a[0]=='*'||a[0]=='&'||a[0]==' '||a[0]=='.'||a[0]=='~'||a[0]=='('||a[0]==')'||a[0]=='?'||a[0]=='/'||a[0]=='_'||a[0]=='@')
	{
		ipace=1;
	}
	else
	{
		ipace=2;
	}

	string firstChar=keyword.substr(0,ipace);
	HNTreeNode* firstNode = parent->insertChild(firstChar,ipace);
	if(firstNode!=NULL && firstChar!="@")
	{
		string restChar=keyword.substr(ipace,keyword.size());
		if(!restChar.empty())
			return insertBranch(firstNode,restChar);
		else 
			return insertBranch(firstNode,endchar);
	}
	return NULL;
}

HNTreeNode* HNTree::find(string& keyword)
{
	return find(&m_emptyRoot,keyword);
}


HNTreeNode* HNTree::find(HNTreeNode* parent,string& keyword)
{
	const char *a = keyword.c_str();
	int ipace;
	if((a[0]>='a'&&a[0]<='z')||
		(a[0]>='A'&&a[0]<='Z')||
		(a[0]>='0'&&a[0]<='9')||
		a[0]=='\''||a[0]=='-'||a[0]=='*'||a[0]=='&'||a[0]==' '||a[0]=='.'||a[0]=='~'||a[0]=='('||a[0]==')'||a[0]=='?'||a[0]=='/'||a[0]=='_'||a[0]=='@')
	{
		ipace=1;
	}
	else
	{
		ipace=2;
	}

	string firstChar=keyword.substr(0,ipace);
	HNTreeNode* firstNode = parent->findChild(firstChar);
	if(firstNode==NULL)            //δ�ҵ�
	{
		count=0;
		return NULL;        
	}
	string restChar=keyword.substr(ipace,keyword.size());
	if(firstNode->findChild(endchar) || firstNode->m_map.empty() )        //��Ӧ������������жϸô�Ϊ���д�
	{
		//std::cout<<count+1<<endl;
		count+=ipace;
		return firstNode;
	}
	if(keyword.size()==ipace)    //���һ����
		return NULL;
	count+=ipace;
	return find(firstNode,restChar);
}

