#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <windows.h>
#include "HNFilter.h"

HNFilter::HNFilter()
{
	load("keywords.txt");
}

void HNFilter::load(const char* filePath)
{
	ifstream keywordsFile(filePath, ios::in);
	if (keywordsFile.is_open())
	{
		char buffer[256];
		int count = 0;
		int offset = 0;
		while((buffer[offset]=keywordsFile.get())!=EOF)
		{       
			if (buffer[offset]>='A'&&buffer[offset]<='Z')
			{
				buffer[offset]+=32;
			}

			string word1;
			word1.assign(buffer,offset);
			if(buffer[offset]==',')
			{
				string word;
				if(offset)
				{
					word.assign(buffer,offset);
					m_tree.insert(word);
				}
				offset = 0;
			}
			else
				offset++;
		}
	}
	keywordsFile.close();
	m_initialized = true;
}


bool HNFilter::censor(string& source,bool bStop/*=true*/)
{

	int length = source.size();

	string src_temp;
	char srcchar[2000];
	memset(srcchar,0,sizeof(srcchar));
	strcpy(srcchar,source.c_str());
	srcchar[length+1]=0;

	for (int i = 0; i < length;i++)
	{
		if (srcchar[i]>='A'&&srcchar[i]<='Z')
		{
			srcchar[i]+=32;
		}
	}

	src_temp.assign(srcchar,length+1);
	
	for (int i = 0; i < length;)
	{
		string substring = src_temp.substr(i, length - i);

		const char *a = substring.c_str();
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
		
		if (m_tree.find(substring) != NULL)    //·¢ÏÖÃô¸Ð´Ê
		{
			if (bStop) return true;
			source.replace(i,m_tree.count,"**");
			m_tree.count =0;
			length = source.size();
			ipace=2;
		}
		i+=ipace;
	}
	return false;
}
