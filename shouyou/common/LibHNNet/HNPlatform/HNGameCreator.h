#ifndef HNGame_Creator_h__
#define HNGame_Creator_h__

#include "HNBaseType.h"
#include "HNUIExport.h"
#include "HNNetExport.h"
#include "HNGame/HNGameUIBase.h" 
#include "cocos2d.h"
#include <unordered_map>

typedef std::function<HNGameUIBase* (UINT uDeskId, bool autoCreate)> GAME_CREATE_SELECTOR;

typedef std::function<HNLayer* (Node* parent)> ROOM_CREATE_SELECTOR;

class HNGameCreator
{
public:
	// ��Ϸ����
	enum GAMETYPE
	{
		UNKNOWN = 0, // δ֪����
		NORMAL,      // ������Ϸ
		BR,          // ������Ϸ
		SINGLE       // ������Ϸ
	};
	static const BYTE INVALID_PRIORITY = 0xFF;

	struct ItemCreator
	{
		BYTE priority;
		GAMETYPE type;
		UINT uNameId;
		UINT uKindId;
		GAME_CREATE_SELECTOR	gameSelector;
		ROOM_CREATE_SELECTOR	roomSelector;

		ItemCreator() : uNameId(0), uKindId(0), type(UNKNOWN), gameSelector(nullptr), roomSelector(nullptr)
		{

		}

		bool validGame()
		{
			return (0 != uNameId) && (UNKNOWN != type) && (nullptr != gameSelector);
		}

		bool valid()
		{
			return (0 != uNameId) /*&& (0 != uKindId)*/ && (UNKNOWN != type) && (nullptr != gameSelector);
		}
	};

public:
	// ��ȡ����
	static HNGameCreator* getInstance();

	// ���ٵ���
	static void destroyInstance();

	// ��ȡע����Ϸ����
	int getRegistGameCount();

public:
	// ע����Ϸ
	void addGame(UINT uNameId, GAMETYPE type, GAME_CREATE_SELECTOR createGameSelector, ROOM_CREATE_SELECTOR createRoomSelector = nullptr);

	// ����ע����Ϸ������id
	void setGameKindId(UINT uNameId, UINT uKindId);
	
	// ��ȡ��Ч����Ϸ�б�
	bool getValidGames(std::vector<ComNameInfo*>* validGames);
	std::vector<ComNameInfo*> getValidGames();

	// ��ȡ��Ϸ���ȼ�
	BYTE getGamePriority(UINT uNameId);
	
	// ���õ�ǰѡ�����ϷID
	void setCurrentGame(UINT uNameId);
	
	// ��ǰ��ϷID
	UINT getCurrentGameNameID() const;
	
	// ��ǰ��Ϸ����
	UINT getCurrentGameKindID() const;
	
	// ��ȡ��Ϸ����
	GAMETYPE getCurrentGameType() const;

	// ��ȡ�ͻ��˱���ע�����Ϸid�б�
	std::vector<UINT> getRegistGameIdList();

public:
	// ������Ϸ�ͻ���
	bool startGameClient(UINT uNameId, BYTE bDeskIndex, bool bAutoCreate);
	
	// ������Ϸ����
	bool startGameRoom(UINT uNameId, Node* parent);

protected:
	// У����Ϸ
	BYTE validGame(UINT uNameId);

private:
	// ���캯��
	HNGameCreator();

	// ��������
	virtual ~HNGameCreator();

private:
	// ע����Ϸ�б�
	std::unordered_map<UINT, ItemCreator> _creators;

	// ��ǰ������Ϸ
	ItemCreator* _currentCreator;

	// ���ȼ�
	BYTE	_basePriority;

	// ��Ϸ��Ϸ����
	int     _validCount;

	// ��Ч��Ϸ�б�
	std::vector<ComNameInfo*> _validGames;

	// ����ע�����Ϸid�б�
	std::vector<UINT> _localGameIdList;
};

#define GameCreator()	HNGameCreator::getInstance()

#endif // HNGame_Creator_h__
