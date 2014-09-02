#include "BattleFieldScene.h"
#include "BackgroundLayer.h"
#include "InfoBarLayer.h"
#include "PlayerLayer.h"
#include "MonsterLayer.h"
#include "ListLayer.h"

BattleFieldScene::~BattleFieldScene()
{
	CC_SAFE_DELETE(_data);
}

BattleFieldScene* BattleFieldScene::scene(int sceneId)
{
	BattleFieldScene *scene = new BattleFieldScene(sceneId);
	if (scene && scene->init()) {
		scene->autorelease();
		return scene;
	}
	else {
		CC_SAFE_DELETE(scene);
		return nullptr;
	}
}

bool BattleFieldScene::init()
{
	if (!Scene::init()) {
		return false;
	}

	//Init data model
	_data = battledata::BattleData::loadData(_sceneId);
	if (!_data)
		return false;

	int playerCount = _data->getPlayerCount();
	int monsterCount = _data->getMonsterCount();
	for (int i = 0; i<playerCount; i++)
		_playerFinishFlag.insert(std::make_pair(i, false));
	for (int i = 0; i<monsterCount; i++)
		_monsterFinishFlag.insert(std::make_pair(i, true));

	//Init layers
	_bgLayer = BackgroundLayer::create(_data->getMapName());
	_infoLayer = InfoBarLayer::create();
	_playerLayer = PlayerLayer::createWithNames(_data->getPlayerNames());
	_monsterLayer = MonsterLayer::createWithNames(_data->getMonsterNames());
	if (_bgLayer && _infoLayer && _playerLayer && _monsterLayer) {
		this->addChild(_bgLayer, 0);
		this->addChild(_infoLayer, 1);
		this->addChild(_playerLayer, 2);
		this->addChild(_monsterLayer, 2);
	}
	else {
		CCLOG("Init layer error!");
		CC_SAFE_DELETE(_bgLayer);
		CC_SAFE_DELETE(_infoLayer);
		CC_SAFE_DELETE(_playerLayer);
		CC_SAFE_DELETE(_monsterLayer);
		return false;
	}
	//Init select list
	_listLayer = new ListLayer();
	_listLayer->setDataSource(this);
	if (_listLayer->init()) {
		_listLayer->setDelegate(this);
		_listLayer->setVisible(false);
		_listLayer->setTouchEnabled(false);
		this->addChild(_listLayer, 3);
	}
	else {
		CCLOG("Init select layer error!");
		CC_SAFE_DELETE(_listLayer);
		CC_SAFE_DELETE(_bgLayer);
		CC_SAFE_DELETE(_infoLayer);
		CC_SAFE_DELETE(_playerLayer);
		CC_SAFE_DELETE(_monsterLayer);
		return false;
	}

	_roundOwner = PLAYER;
	this->schedule(SEL_SCHEDULE(&BattleFieldScene::updateGame), 0.5f);

	return true;
}

void BattleFieldScene::updateGame(float ft)
{

}

TableViewCell* BattleFieldScene::tableCellAtIndex(TableView *table, ssize_t idx)
{
	return NULL;
}
ssize_t BattleFieldScene::numberOfCellsInTableView(TableView *table){ return 0; }
void BattleFieldScene::tableCellTouched(TableView* table, TableViewCell* cell){}