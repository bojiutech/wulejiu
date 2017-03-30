#ifndef _GAMESELECT_H_
#define _GAMESELECT_H_
// ----------------------------------------------------------------------------
//
// PengJiLin, 2011-4-2, ָ����Щ��Ϸ����Ч��
//
// ----------------------------------------------------------------------------

#define MAX_NUM_OF_GAME     900     // ������Ϸ����
#define DITS_NUM_OF_NAMEID  8       // NameID ��λ��

class CGameSelecter
{
public:
    CGameSelecter();
    ~CGameSelecter();

public:
    // ��Ϸ�Ƿ��ǿ��õ�
    BOOL GameIsUsable(UINT uNameID);

private:
    // �����Ϸ�Ƿ����
    BOOL FreeGameIsUsable(UINT uNameID);

    // �շ���Ϸ�Ƿ����
    BOOL PayGameIsUsable(UINT uNameID);

    // �ӱ��л�ȡ���NameID
    UINT GetNameIDFromFreeTable(UINT uIndex);

    // �ӱ��л�ȡ�շ�NameID
    UINT GetNameIDFromPayTable(UINT uIndex);

    // �ӽ���
    BYTE Encode(BYTE byData);
    BYTE Decode(BYTE byData);

private:

};


#endif