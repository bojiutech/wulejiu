#include "Stdafx.h"
#include "GameSelect.h"

extern BYTE g_FreeGameSet[];
extern BYTE g_PayGameSet[];

// ----------------------------------------------------------------------------
//
// PengJiLin, 2011-4-2, ָ����Щ��Ϸ����Ч��
//
// ----------------------------------------------------------------------------

CGameSelecter::CGameSelecter()
{

}

CGameSelecter::~CGameSelecter()
{

}

// ��Ϸ�Ƿ��ǿ��õ�
BOOL CGameSelecter::GameIsUsable(UINT uNameID)
{
    BOOL bCanUse = FALSE;

    bCanUse = FreeGameIsUsable(uNameID);
    if(FALSE == bCanUse)
    {
        bCanUse = PayGameIsUsable(uNameID);
    }
    return bCanUse;
}

// �����Ϸ�Ƿ����
BOOL CGameSelecter::FreeGameIsUsable(UINT uNameID)
{
#ifndef BZ_LICENSE
	return TRUE;
#endif

    BOOL bCanUse = FALSE;

    UINT uSelectID = 0;
    for(int i = 0; i < MAX_NUM_OF_GAME; ++i)
    {
        uSelectID = GetNameIDFromFreeTable(i);
        if(uSelectID < 1000) break;

        if(uSelectID == uNameID)
        {
            bCanUse = TRUE;
            break;
        }
    }

    return bCanUse;
}

// �շ���Ϸ�Ƿ����
BOOL CGameSelecter::PayGameIsUsable(UINT uNameID)
{

#ifndef BZ_LICENSE
	return TRUE;
#endif

    BOOL bCanUse = FALSE;

    UINT uSelectID = 0;
    for(int i = 0; i < MAX_NUM_OF_GAME; ++i)
    {
        uSelectID = GetNameIDFromPayTable(i);
        if(uSelectID < 1000) break;

        if(uSelectID == uNameID)
        {
            bCanUse = TRUE;
            break;
        }
    }

    return bCanUse;
}

// �ӱ��л�ȡ���NameID
UINT CGameSelecter::GetNameIDFromFreeTable(UINT uIndex)
{
    UINT uNameID = 0;
    CString strNameID = "";
    char chNum[100] = {0};
    BYTE byOutData = 0;

    uIndex *= DITS_NUM_OF_NAMEID;
    for(int i = uIndex; i < uIndex+DITS_NUM_OF_NAMEID; ++i)
    {
        memset(chNum, 0, sizeof(chNum));
        byOutData = Decode(g_FreeGameSet[i]);
        ::itoa(byOutData, chNum, 10);
        strNameID += chNum;
    }

    uNameID = ::atoi(strNameID.GetBuffer());
    return uNameID;
}

// �ӱ��л�ȡ�շ�NameID
UINT CGameSelecter::GetNameIDFromPayTable(UINT uIndex)
{
    UINT uNameID = 0;
    CString strNameID = "";
    char chNum[100] = {0};
    BYTE byOutData = 0;

    uIndex *= DITS_NUM_OF_NAMEID;
    for(int i = uIndex; i < uIndex+DITS_NUM_OF_NAMEID; ++i)
    {
        memset(chNum, 0, sizeof(chNum));
        byOutData = Decode(g_PayGameSet[i]);
        ::itoa(byOutData, chNum, 10);
        strNameID += chNum;
    }

    uNameID = ::atoi(strNameID.GetBuffer());
    return uNameID;
}

// �ӽ���
BYTE CGameSelecter::Encode(BYTE byData)
{
    BYTE byOutData = 0;
    byOutData = byData ^ 0x16;
    byOutData += 5;
    return byOutData;
}
BYTE CGameSelecter::Decode(BYTE byData)
{
    BYTE byOutData = 0;
    byOutData = byData - 5;
    byOutData = byOutData ^ 0x16;
    return byOutData;
}