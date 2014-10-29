#ifndef __BATTLE_FIELD_SCENE_H__
#define __BATTLE_FIELD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../DataModel/BattleData.h"
#include "../DataModel/AbstractListItemData.h"

USING_NS_CC;
USING_NS_CC_EXT;

class BattleData;
class BackgroundLayer;
class InfoBarLayer;
class PlayerLayer;
class MonsterLayer;
class ListLayer;

enum ROUND_OWNER {
	PLAYER,
	COMPUTER
};

class BattleFieldScene : public Scene, public TableViewDataSource, public TableViewDelegate
{
public:
	BattleFieldScene(int sceneId) { _sceneId = sceneId; }
	~BattleFieldScene(void);

	virtual bool init();
	static BattleFieldScene* scene(int sceneId);

	void updateGame(float ft);						//Main loop

	TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	ssize_t numberOfCellsInTableView(TableView *table);
	void tableCellTouched(TableView* table, TableViewCell* cell);
	void tableCellHighlight(TableView* table, TableViewCell* cell);
	void tableCellUnhighlight(TableView* table, TableViewCell* cell);
	Size cellSizeForTable(TableView *table);

	int getSelectedItemId() { return _selectedListItemId; }

private:
	void runPlayerRound();
	void runComputerRound();
	bool checkRoundFinished();
	void switchOwner();
	void switchList(bool isOpen);
	void effectOnMonsters(AbstractListItemData* pEffectSource);
	void effectOnMonster(int monsterNo, AbstractListItemData* pEffectSource);
	bool checkBattleEnd();


private:
	int							_sceneId;
	BattleData*					_data;
	ROUND_OWNER					_roundOwner;

	BackgroundLayer*			_bgLayer;
	InfoBarLayer*				_infoLayer;
	PlayerLayer*				_playerLayer;
	MonsterLayer*				_monsterLayer;
	ListLayer*					_listLayer;

	int _selectedListItemId;
	int _roundCounter;
	int _isWin;

	map<int, bool> _playerFinishFlag;
	map<int, bool> _monsterFinishFlag;
};
#endif

