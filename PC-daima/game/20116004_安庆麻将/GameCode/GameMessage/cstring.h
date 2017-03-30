/****************************************************************************
Copyright (c) 2014-2016 Beijing TianRuiDiAn Network Technology Co.,Ltd.
Copyright (c) 2014-2016 ShenZhen Redbird Network Polytron Technologies Inc.
 
http://www.hotniao.com

All of the content of the software, including code, pictures, 
resources, are original. For unauthorized users, the company 
reserves the right to pursue its legal liability.
****************************************************************************/
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               #pragma once

#define SafeDeleteArray( p )\
    if (NULL!=p)	\
    {				\
    delete []p;	\
    p = NULL;	\
    }

/// �Զ����ַ�����
class CStringEx
{
public:
    /// Ĭ�Ϲ��캯��
    CStringEx() : m_nLen(1)
    {
        m_pBuf = new char[1];
        m_pBuf[0] = TEXT('\0');
    }

    /// �����ַ���ָ��Ĺ��캯��
    CStringEx(const char *p)
    {
        if (p==NULL)
        {
            m_pBuf = new char[1];
            m_pBuf[0] = TEXT('\0');
            m_nLen = 1;
            return;
        }
        m_nLen = (int)strlen(p) + 1;
        m_pBuf = new char[m_nLen];
        strcpy(m_pBuf, p);
    }
    /// ��������
    ~CStringEx(){SafeDeleteArray(m_pBuf);m_nLen = 0;}

    /// �������캯��
    CStringEx(const CStringEx &rhs)
    {
        m_nLen = (int)strlen(rhs.m_pBuf) + 1;
        m_pBuf = new char[m_nLen];
        strcpy(m_pBuf, rhs.m_pBuf);
    }
    /// ��ֵ������
    CStringEx &operator=(const CStringEx &rhs)
    {
        int nLen = (int)strlen(rhs.m_pBuf)+1;
        if (m_nLen<nLen)
        {
            SafeDeleteArray(m_pBuf);
            m_pBuf = new char[nLen];
            strcpy(m_pBuf, rhs.m_pBuf);
            m_nLen = nLen;
        }
        else
        {
            strcpy(m_pBuf, rhs.m_pBuf);
        }
        return *this;
    }

    bool operator<(const CStringEx &rhs) const
    {
        return strcmp(m_pBuf, rhs.m_pBuf)<0;
    }
    bool operator==(const CStringEx &rhs) const
    {
        return strcmp(m_pBuf, rhs.m_pBuf)==0;
    }
    bool operator>(const CStringEx &rhs) const
    {
        return strcmp(m_pBuf, rhs.m_pBuf)>0;
    }
    /// ���ַ���ĩβ�����һ�ַ���, +������
    CStringEx operator+(const char *szParam) const
    {
        CStringEx ret(*this);
        if (szParam == NULL)
        {
            return ret;
        }
        int nLen = (int)strlen(m_pBuf) + (int)strlen(szParam) + 1;
        if (ret.m_nLen<nLen)
        {
            char *p = ret.m_pBuf;
            ret.m_pBuf = new char[nLen];
            strcpy(ret.m_pBuf, p);
            SafeDeleteArray(p);
            strcat(ret.m_pBuf, szParam);
            ret.m_nLen = nLen;
        }
        else
        {
            strcat(ret.m_pBuf, szParam);
        }
        return ret;
    }
    /// ���ַ���ĩβ�����һ�ַ���, +=������
    CStringEx &operator+=(const char *szParam)
    {
        if (szParam == NULL)
        {
            return *this;
        }
        int nLen = (int)strlen(m_pBuf) +(int) strlen(szParam) + 1;
        if (m_nLen<nLen)
        {
            char *p = m_pBuf;
            m_pBuf = new char[nLen];
            strcpy(m_pBuf, p);
            SafeDeleteArray(p);
            strcat(m_pBuf, szParam);
            m_nLen = nLen;
        }
        else
        {
            strcat(m_pBuf, szParam);
        }
        return *this;
    }
    /// �Ӻ���ǰ��һ���ַ�
    int ReverseFind(char ch) const
    {
        int nLen = (int)strlen(m_pBuf);
        for (int i=nLen-1; i>=0; --i)
        {
            if (m_pBuf[i] == ch)
            {
                return i;
            }
        }
        return -1;
    }
    /// ���س���
    int GetLength(){return (int)strlen(m_pBuf);}
    /// ��ȡ���ָ�����ȵ��ַ���
    CStringEx Left(int nPos) const
    {
        CStringEx ret(*this);
        ret.m_pBuf[nPos] = TEXT('\0');
        return ret;
    }
    /// ����const charָ��
    operator const char *() const
    {
        return m_pBuf;
    }
    /// ��ʽ���ַ���
    CStringEx &Format(const char *szFormat, ...)
    {
        va_list arg;
        va_start( arg, szFormat );

        char szBuf[512];
        sprintf( szBuf, szFormat, arg );
        int nLen = (int)strlen(szBuf)+1;
        if (m_nLen<nLen)
        {
            SafeDeleteArray(m_pBuf);
            m_pBuf = new char[nLen];
            strcpy(m_pBuf, szBuf);
            m_nLen = nLen;
        }
        else
        {
            strcpy(m_pBuf, szBuf);
        }
        return *this;
    }
    const char *GetBuffer()
    {
        return m_pBuf;
    }

private:
    char *m_pBuf;	///< ������
    int m_nLen;		///< ����������
};