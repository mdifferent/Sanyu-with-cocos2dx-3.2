#ifndef __BATTLE_FIELD_SCENE_H__
#define __BATTLE_FIELD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "../DataModel/BattleData.h"

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

private:
	int							_sceneId;
	battledata::BattleData*		_data;
	ROUND_OWNER					_roundOwner;

	BackgroundLayer*			_bgLayer;
	InfoBarLayer*				_infoLayer;
	PlayerLayer*				_playerLayer;
	MonsterLayer*				_monsterLayer;
	ListLayer*					_listLayer;

	map<int, bool> _playerFinishFlag;
	map<int, bool> _monsterFinishFlag;
};
#endif

