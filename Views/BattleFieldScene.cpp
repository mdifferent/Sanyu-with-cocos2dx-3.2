#include "BattleFieldScene.h"
#include "BackgroundLayer.h"
#include "InfoBarLayer.h"
#include "PlayerLayer.h"
#include "MonsterLayer.h"
#include "ListLayer.h"
#include "ConstValues.h"
#include "ListItemCell.h"
#include "../DataModel/InstanceDatabase.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	#include "../proj.win32/WIN32Utils.h"
#endif 

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
	_data = BattleData::loadData(_sceneId);
	if (!_data)
		return false;

	int playerCount = _data->getPlayerCount();
	int monsterCount = _data->getMonsterCount();
	Size size = Director::getInstance()->getWinSize();
	for (int i = 0; i<playerCount; i++)
		_playerFinishFlag.insert(std::make_pair(i, false));
	for (int i = 0; i<monsterCount; i++)
		_monsterFinishFlag.insert(std::make_pair(i, true));

	//Init layers
	_bgLayer = BackgroundLayer::create(_data->getMapName());
	_bgLayer->setPosition(size.width * 0.5, size.height * 0.5);
	_infoLayer = InfoBarLayer::create();
	_infoLayer->setPosition(size.width * 0.5, size.height * 0.5);
	map<int, string> *playerNames = _data->getPlayerNames();
	map<int, tuple<string, int, int, int, int>> initPlayerValues;
	for each (pair<int,string> var in *playerNames)
	{
		initPlayerValues.insert(make_pair(var.first, make_tuple(var.second,
			_data->getPlayerProperty(var.first, PLAYER_PROP_TYPE::MAX_HP),
			_data->getPlayerProperty(var.first, PLAYER_PROP_TYPE::CURRENT_HP),
			_data->getPlayerProperty(var.first, PLAYER_PROP_TYPE::MAX_SP),
			_data->getPlayerProperty(var.first, PLAYER_PROP_TYPE::CURRENT_SP))));
	}
	delete playerNames;
	_playerLayer = PlayerLayer::createWithNames(initPlayerValues);
	_monsterLayer = MonsterLayer::createWithNames(_data->getMonsterNames());
	_monsterLayer->setPosition(0,0);
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
	switch (_roundOwner) {
	case PLAYER:
		runPlayerRound();
		break;
	case COMPUTER:
		runComputerRound();
	}
	if (checkRoundFinished())
		switchOwner();
}

void BattleFieldScene::runPlayerRound()
{
	bool isMagicMatrixAva = false;
	for (int i = 0; i<_data->getMonsterCount(); i++) {
		int current = _data->getMonsterProperty(i, PLAYER_PROP_TYPE::CURRENT_HP);
		int max = _data->getMonsterProperty(i, PLAYER_PROP_TYPE::MAX_HP)*0.3;
		if (current < max && _data->getMonsterStatusAt(i) != BATTLER_STATUS::DEAD) {
			isMagicMatrixAva = true;
			_monsterLayer->onMagicMatrixAvailable();
			break;
		}
	}
	if (!isMagicMatrixAva)
		_monsterLayer->onMagicMatrixUnavailable();
	MonsterLayer::MONSTER_LAYER_STATUS monsterStatus = _monsterLayer->getStatus();
	PlayerLayer::PLAYER_LAYER_STATUS playerStatus = _playerLayer->getStatus();

	//Init status
	if (playerStatus == PlayerLayer::PLAYER_LAYER_STATUS::WAIT_COMMAND && monsterStatus == MonsterLayer::SLEEP) {
		_monsterLayer->resetTarget();
		_playerLayer->resetSelectedMenu();
		_playerLayer->resetSelectedPlayer();
		_playerLayer->resetTarget();
		CCLOG("Monster:sleep, Player: wait");
		return;
	}
	//Open menu
	if (playerStatus == PlayerLayer::PLAYER_LAYER_STATUS::MENU_OPEN && monsterStatus == MonsterLayer::SLEEP) {
		_playerLayer->resetSelectedMenu();
		switchList(false);
		return;
	}
	
	//Select command
	if (playerStatus == PlayerLayer::PLAYER_LAYER_STATUS::MENU_SELECTED && monsterStatus == MonsterLayer::SLEEP) {
		PlayerLayer::PLAYER_CMD playerCmd = _playerLayer->getSelectedMenu();
		if (playerCmd == PlayerLayer::PLAYER_CMD::ATTACK) {
			_monsterLayer->resetTarget();
			_monsterLayer->setStatus(MonsterLayer::WAIT_TARGET);
		}
		else if (playerCmd == PlayerLayer::PLAYER_CMD::ITEM || playerCmd == PlayerLayer::PLAYER_CMD::SKILL) {
			if (playerCmd == PlayerLayer::PLAYER_CMD::ITEM)
				_listLayer->setContentType(ITEM_LIST);
			else
				_listLayer->setContentType(SKILL_LIST);
			switchList(true); //Open select list
		}
		else if (playerCmd == PlayerLayer::PLAYER_CMD::GUARD || playerCmd == PlayerLayer::PLAYER_CMD::ESCAPE) {
			_monsterLayer->setStatus(MonsterLayer::SLEEP);
			if (playerCmd == PlayerLayer::PLAYER_CMD::GUARD)
				_data->setPlayerStatusAt(_playerLayer->getSelectedPlayer(), BATTLER_STATUS::DEFENSE);
			_playerFinishFlag[_playerLayer->getSelectedPlayer()] = true;
		}
		return;
	}
	//Attack
	if (playerStatus == PlayerLayer::PLAYER_LAYER_STATUS::MENU_SELECTED && _playerLayer->getSelectedMenu() == PlayerLayer::PLAYER_CMD::ATTACK) {
		if (monsterStatus == MonsterLayer::WAIT_TARGET) {
			if (_playerLayer->getStatus() == PlayerLayer::PLAYER_LAYER_STATUS::MENU_OPEN) {
				_playerLayer->resetSelectedMenu();
				_monsterLayer->setStatus(MonsterLayer::SLEEP);
			}
		}
		else if (monsterStatus == MonsterLayer::TARGET_SELECTED) {
			int attackTarget = _monsterLayer->getTarget();
			int attackSource = _playerLayer->getSelectedPlayer();
			int attackValue = _data->getPlayerProperty(attackSource, PLAYER_PROP_TYPE::MELEE_ATTACK);
			int defenseValue = _data->getMonsterProperty(attackTarget, PLAYER_PROP_TYPE::MELEE_DEFENSE);
			int damage = attackValue - defenseValue;
			int monsterCurrentHP = _data->getMonsterProperty(attackTarget, PLAYER_PROP_TYPE::CURRENT_HP);
			int monsteMaxHP = _data->getMonsterProperty(attackTarget, PLAYER_PROP_TYPE::MAX_HP);
			//TODO:BUFF and DEBUFF may be considered in the futrue
			if (monsterCurrentHP <= damage) {
				_data->setMonsterStatusAt(attackTarget, BATTLER_STATUS::DEAD);
				_data->setMonsterProperty(attackTarget, PLAYER_PROP_TYPE::CURRENT_HP, 0);
				_monsterLayer->onAttacked(attackTarget, -damage, (damage / monsteMaxHP) * 100.0f, true);
			}
			else {
				_data->setMonsterProperty(attackTarget, PLAYER_PROP_TYPE::CURRENT_HP, monsterCurrentHP - damage);
				_monsterLayer->onAttacked(attackTarget, -damage, (damage / monsteMaxHP) * 100.0f, false);
			}
			//CCLOG("Remain HP:%d", m_data->getMonster(iAttackTarget)->getProperty(CURRENT_HP));
			_data->setPlayerStatusAt(attackSource, BATTLER_STATUS::FINISHED);
			_playerFinishFlag[attackSource] = true;
			_monsterLayer->setStatus(MonsterLayer::SLEEP);
			_playerLayer->setStatus(PlayerLayer::PLAYER_LAYER_STATUS::WAIT_COMMAND);
		}
		return;
	}
	
	//Item & Skill 
	//For enemy
	if (playerStatus == PlayerLayer::PLAYER_LAYER_STATUS::MENU_SELECTED && monsterStatus == MonsterLayer::TARGET_SELECTED) {
		int attackSource = _playerLayer->getSelectedPlayer();
		if (_playerLayer->getSelectedMenu() == PlayerLayer::PLAYER_CMD::ITEM) {
			effectOnMonsters(InstanceDatabase::getDatabaseInstance()->getItemById(getSelectedItemId()));
		}
		else if (_playerLayer->getSelectedMenu() == PlayerLayer::PLAYER_CMD::SKILL) {
			int iSkillId = getSelectedItemId();
			SkillData *pData = (SkillData*)InstanceDatabase::getDatabaseInstance()->getSkillById(iSkillId);
			int iCost = pData->getCost();
			int iCurrentSP = _data->getPlayerProperty(attackSource, PLAYER_PROP_TYPE::CURRENT_SP);
			if (iCost <= iCurrentSP) {
				effectOnMonsters(pData);
				_data->setPlayerProperty(attackSource, PLAYER_PROP_TYPE::CURRENT_SP, iCurrentSP - iCost);
				_playerLayer->onPlayerPropModified(2, 0 - attackSource, 0 - iCost);
			}
			else
				CCLOG("No enough SP");
		}
		_data->setPlayerStatusAt(attackSource, BATTLER_STATUS::FINISHED);
		_playerFinishFlag[attackSource] = true;
		_monsterLayer->setStatus(MonsterLayer::SLEEP);
		_playerLayer->setStatus(PlayerLayer::PLAYER_LAYER_STATUS::WAIT_COMMAND);
		return;
	}
	//For friend
	if (playerStatus == PlayerLayer::PLAYER_LAYER_STATUS::TARGET_SELECTED && monsterStatus == MonsterLayer::SLEEP) {
		int iOperationSource = _playerLayer->getSelectedPlayer();
		int iTargetPlayer = _playerLayer->getTarget();
		int iCurrentHP = _data->getPlayerProperty(iTargetPlayer, PLAYER_PROP_TYPE::CURRENT_HP);
		int iMaxHP = _data->getPlayerProperty(iTargetPlayer, PLAYER_PROP_TYPE::MAX_HP);
		int iCurrentSP = _data->getPlayerProperty(iTargetPlayer, PLAYER_PROP_TYPE::CURRENT_SP);
		int iMaxSP = _data->getPlayerProperty(iTargetPlayer, PLAYER_PROP_TYPE::MAX_SP);
		int iItemId = getSelectedItemId();
		AbstractListItemData *itemData = NULL;
		if (_playerLayer->getSelectedMenu() == PlayerLayer::PLAYER_CMD::ITEM)
			itemData = InstanceDatabase::getDatabaseInstance()->getItemById(iItemId);
		else if (_playerLayer->getSelectedMenu() == PlayerLayer::PLAYER_CMD::SKILL)
			itemData = InstanceDatabase::getDatabaseInstance()->getSkillById(iItemId);
		if (itemData == NULL) {
			CCLOG("Get item/skill data error!");
			return;
		}
		map<EFFECT_ATTRIBUTE, int> effect = itemData->getItemEffects();
		map<EFFECT_ATTRIBUTE, int>::iterator effIter = effect.begin();
		while (effIter != effect.end()) {
			switch (effIter->first) {
			case EFFECT_ATTRIBUTE::CURRENT_HP:
				if (iCurrentHP + effIter->second > iMaxHP)
					_data->setPlayerProperty(iTargetPlayer, PLAYER_PROP_TYPE::CURRENT_HP, iMaxHP);
				else
					_data->setPlayerProperty(iTargetPlayer, PLAYER_PROP_TYPE::CURRENT_HP, iCurrentHP + effIter->second);
				_playerLayer->onPlayerPropModified(1, iTargetPlayer, effIter->second);
				break;
			case EFFECT_ATTRIBUTE::CURRENT_SP:
				if (iCurrentSP + effIter->second > iMaxSP)
					_data->setPlayerProperty(iTargetPlayer, PLAYER_PROP_TYPE::CURRENT_SP, iMaxSP);
				else
					_data->setPlayerProperty(iTargetPlayer, PLAYER_PROP_TYPE::CURRENT_SP, iCurrentSP + effIter->second);
				_playerLayer->onPlayerPropModified(2, iTargetPlayer, effIter->second);
				break;
			};
			effIter++;
		}
		_data->setPlayerStatusAt(iOperationSource, BATTLER_STATUS::FINISHED);				//Target conflict with source
		_playerFinishFlag[iOperationSource] = true;
		_monsterLayer->setStatus(MonsterLayer::SLEEP);
		_playerLayer->setStatus(PlayerLayer::PLAYER_LAYER_STATUS::WAIT_COMMAND);
		return;
	}
	if (monsterStatus == MonsterLayer::SPECIAL_ATTACK) {
		CCLOG("Special Attack");
		_playerLayer->beforeSpecialAttack();
		return;
	}
	if (monsterStatus == MonsterLayer::SPECIAL_ATTACK_FINISHED) {
		CCLOG("Special Attack Finished");
		if (_monsterLayer->isBubbleFailed()) {
			int currentHP = _data->getPlayerProperty(0, PLAYER_PROP_TYPE::CURRENT_HP);
			int maxHP = _data->getPlayerProperty(0, PLAYER_PROP_TYPE::MAX_HP);
			float damage = maxHP * 0.05;
			if (damage > currentHP) {
				_data->setPlayerStatusAt(0, BATTLER_STATUS::DEAD);
				_data->setPlayerProperty(0, PLAYER_PROP_TYPE::CURRENT_HP, 0);
			}
			else {
				_data->setPlayerProperty(0, PLAYER_PROP_TYPE::CURRENT_HP, currentHP - damage);
			}
			_playerLayer->onPlayerPropModified(1, 0, -damage);
		}
		_playerLayer->afterSpecialAttack();
		_playerLayer->setStatus(PlayerLayer::PLAYER_LAYER_STATUS::WAIT_COMMAND);
		_monsterLayer->setStatus(MonsterLayer::SLEEP);
		return;
	}
	return;
}

void BattleFieldScene::runComputerRound()
{
	CCLOG("COMPUTER ROUND");
	int playerCount = _data->getPlayerCount();
	int mosnterCount = _data->getMonsterCount();
	int attackTarget = -1;
	int iMinHP = TOP_HP;
	for (int i = 0; i<mosnterCount; i++) {
		CCLOG("Monster %d", i);
		if (_data->getMonsterStatusAt(i) != BATTLER_STATUS::DEAD) {
			do {
				attackTarget = rand() % playerCount;
			} while (_data->getPlayerStatusAt(attackTarget) == BATTLER_STATUS::DEAD);
				
			/*
			for (int j = 0; j<playerCount; j++) {
				if (_data->getPlayerStatusAt(j) != BATTLER_STATUS::DEAD &&
					_data->getPlayerProperty(j, PLAYER_PROP_TYPE::CURRENT_HP)< iMinHP) {
					iMinHP = _data->getPlayerProperty(j, PLAYER_PROP_TYPE::CURRENT_HP);
					attackTarget = j;
				}
			}*/
			int defenseValue = _data->getPlayerProperty(attackTarget, PLAYER_PROP_TYPE::MELEE_DEFENSE);
			int attackValue = _data->getMonsterProperty(i, PLAYER_PROP_TYPE::MELEE_ATTACK);
			int damageValue = _data->getPlayerStatusAt(attackTarget) == BATTLER_STATUS::DEFENSE ? attackValue - defenseValue : attackValue;
			int playerCurrentHP = _data->getPlayerProperty(attackTarget, PLAYER_PROP_TYPE::CURRENT_HP);
			_playerLayer->onPlayerPropModified(1, attackTarget, -damageValue);
			if (damageValue >= playerCurrentHP) {
				_data->setPlayerProperty(attackTarget, PLAYER_PROP_TYPE::CURRENT_HP, 0);
				_data->setPlayerStatusAt(attackTarget, BATTLER_STATUS::DEAD);
			}
			else {
				_data->setPlayerProperty(attackTarget, PLAYER_PROP_TYPE::CURRENT_HP, playerCurrentHP - damageValue);
			}
			_data->setMonsterStatusAt(i, BATTLER_STATUS::FINISHED);
			_monsterFinishFlag[i] = true;
		}
	}
}

bool BattleFieldScene::checkRoundFinished() {
	bool res = true;
	if (_roundOwner == PLAYER) {
		int iPlayerCount = _playerFinishFlag.size();
		for (int i = 0; i<iPlayerCount; i++)
		if (_playerFinishFlag[i] == false)		//False = haven't run action
			res = false;
	}
	else if (_roundOwner == COMPUTER) {
		int iMonsterCount = _monsterFinishFlag.size();
		for (int i = 0; i<iMonsterCount; i++)
		if (_monsterFinishFlag[i] == false)
			res = false;
	}
	return res;
}

TableViewCell* BattleFieldScene::tableCellAtIndex(TableView *table, ssize_t idx)
{
	CCLOG("No of cell=%d", idx);
	int iPlayerNum = _playerLayer->getSelectedPlayer();
	if (iPlayerNum < 0)
		return NULL;
	TableViewCell *cell = table->dequeueCell();
	string cellItemName;
	string cellItemTarget;
	int cellCount = 0;
	AbstractListItemData *item = NULL;
	switch (_listLayer->getContentType()) {
	case ITEM_LIST:
		if (_data->getPlayerItemCount(iPlayerNum) > 0) {
			pair<int,int> itemData = _data->getPlayerItem(iPlayerNum, idx);
			item = InstanceDatabase::getDatabaseInstance()->getItemById(itemData.first);
			cellCount = itemData.second;
		}
		break;
	case SKILL_LIST:
		if (_data->getPlayerSkillCount(iPlayerNum) > 0) {
			pair<int, int> skillData = _data->getPlayerSkill(iPlayerNum, idx);
			item = InstanceDatabase::getDatabaseInstance()->getSkillById(skillData.first);
			cellCount = ((SkillData*)item)->getCost();
		}
	};
	if (item != NULL) {
		cellItemName = item->getName();
		if (item->getTargetType() == TARGET_TYPE::FRIEND)
		if (item->getMultiTarget())
			cellItemTarget = PLAYER_ALL;
		else
			cellItemTarget = PLAYER_ONE;
		else if (item->getTargetType() == TARGET_TYPE::ENEMY)
		if (item->getMultiTarget())
			cellItemTarget = ENEMY_ALL;
		else
			cellItemTarget = ENEMY_ONE;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		GBKToUTF(cellItemName);
		GBKToUTF(cellItemTarget);
#endif
	}
	if (!cell) {
		cell = ListItemCell::create(cellItemName, cellItemTarget, cellCount);
		return cell;
	}
	else {
		ListItemCell *oldCell = dynamic_cast<ListItemCell*>(cell);
		oldCell->updateLabels(cellItemName, cellItemTarget, cellCount);
		return oldCell;
	}
	return NULL;
}

ssize_t BattleFieldScene::numberOfCellsInTableView(TableView *table)
{ 
	int playerNum = _playerLayer->getSelectedPlayer();
	if (playerNum < 0)
		return 0;
	int cellCount = 0;
	switch (_playerLayer->getSelectedMenu()) {
	case PlayerLayer::PLAYER_CMD::ITEM:
		cellCount = _data->getPlayerItemCount(playerNum);
		break;
	case PlayerLayer::PLAYER_CMD::SKILL:
		cellCount = _data->getPlayerSkillCount(playerNum);
		break;
	default:
		cellCount = 0;
	}
	return cellCount;
}

void BattleFieldScene::tableCellTouched(TableView* table, TableViewCell* cell)
{
	log("cell touched at index: %i", cell->getIdx());
	ListItemCell *newcell = (ListItemCell*)cell;
	int idx = cell->getIdx();
	_listLayer->setVisible(false);
	int iPlayerNum = _playerLayer->getSelectedPlayer();
	if (iPlayerNum < 0)
		return;
	switch (_listLayer->getContentType()) {
	case ITEM_LIST:	{
		int itemCount = _data->getPlayerItemCount(iPlayerNum);
		if (idx > itemCount || itemCount == 0)
			return;
		int itemId = _data->getPlayerItem(iPlayerNum, idx).first;
		_selectedListItemId = itemId;
		AbstractListItemData *pItem = InstanceDatabase::getDatabaseInstance()->getItemById(itemId);
		if (pItem->getTargetType() == TARGET_TYPE::ENEMY) {
			if (pItem->getMultiTarget())
				_monsterLayer->setStatus(MonsterLayer::TARGET_SELECTED);
			else
				_monsterLayer->setStatus(MonsterLayer::WAIT_TARGET);
		}
		else if (pItem->getTargetType() == TARGET_TYPE::FRIEND) {
			_monsterLayer->setStatus(MonsterLayer::SLEEP);
			if (pItem->getMultiTarget())
				_playerLayer->setStatus(PlayerLayer::PLAYER_LAYER_STATUS::TARGET_SELECTED);
			else
				_playerLayer->setStatus(PlayerLayer::PLAYER_LAYER_STATUS::WAIT_TARGET);
			}
		_data->playerUseItem(_playerLayer->getSelectedPlayer(), itemId);
		break;
	}
	case SKILL_LIST: {
		int skillCount = _data->getPlayerSkillCount(iPlayerNum);
		if (idx > skillCount || skillCount == 0)
			return;
		int skillId = _data->getPlayerSkill(iPlayerNum, idx).first;
		_selectedListItemId = skillId;
		AbstractListItemData *pItem = InstanceDatabase::getDatabaseInstance()->getSkillById(skillId);
		if (pItem->getTargetType() == TARGET_TYPE::ENEMY) {
			if (pItem->getMultiTarget())
				_monsterLayer->setStatus(MonsterLayer::TARGET_SELECTED);
			else
				_monsterLayer->setStatus(MonsterLayer::WAIT_TARGET);
		}
		else if (pItem->getTargetType() == TARGET_TYPE::FRIEND) {
			_monsterLayer->setStatus(MonsterLayer::SLEEP);
			if (pItem->getMultiTarget())
				_playerLayer->setStatus(PlayerLayer::PLAYER_LAYER_STATUS::TARGET_SELECTED);
			else
				_playerLayer->setStatus(PlayerLayer::PLAYER_LAYER_STATUS::WAIT_TARGET);
		}
		_data->playerUseSkill(_playerLayer->getSelectedPlayer(), skillId);
		break;
	}
	};
	switchList(false);
}

void BattleFieldScene::tableCellHighlight(TableView* table, TableViewCell* cell)
{
	ListItemCell *newcell = (ListItemCell*)cell;
	newcell->onSelected();
}

void BattleFieldScene::tableCellUnhighlight(TableView* table, TableViewCell* cell)
{
	ListItemCell *newcell = (ListItemCell*)cell;
	newcell->onDeselected();
}

void BattleFieldScene::switchList(bool isOpen) {
	_listLayer->setTouchEnabled(isOpen);
	_listLayer->setVisible(isOpen);
}

void BattleFieldScene::effectOnMonsters(AbstractListItemData* pEffectSource)
{
	if (pEffectSource->getMultiTarget()) {
		int monsterCount = _data->getMonsterCount();
		for (size_t i = 0; i < monsterCount; i++) {
			if (_data->getMonsterStatusAt(i) != BATTLER_STATUS::DEAD) {
				effectOnMonster(i, pEffectSource);
			}
		}
	}
	else {
		int attackTarget = _monsterLayer->getTarget();
		effectOnMonster(attackTarget, pEffectSource);
	}
}

void BattleFieldScene::effectOnMonster(int monsterNo, AbstractListItemData* pEffectSource)
{
	map<EFFECT_ATTRIBUTE, int> effect = pEffectSource->getItemEffects();
	map<EFFECT_ATTRIBUTE, int>::iterator effIter = effect.begin();
	int monsterCurrentHP = _data->getMonsterProperty(monsterNo, PLAYER_PROP_TYPE::CURRENT_HP);
	int monsterMaxHP = _data->getMonsterProperty(monsterNo, PLAYER_PROP_TYPE::MAX_HP);
	while (effIter != effect.end()) {
		switch (effIter->first) {
		case EFFECT_ATTRIBUTE::CURRENT_HP:
			if (monsterCurrentHP <= effIter->second) {
				_data->setMonsterStatusAt(monsterNo, BATTLER_STATUS::DEAD);
				_data->setMonsterProperty(monsterNo, PLAYER_PROP_TYPE::CURRENT_HP, 0);
				_monsterLayer->onAttacked(monsterNo, 0 - effIter->second, (effIter->second / monsterMaxHP)*100.0f, true);
			}
			else {
				_data->setMonsterProperty(monsterNo, PLAYER_PROP_TYPE::CURRENT_HP, monsterCurrentHP - effIter->second);
				_monsterLayer->onAttacked(monsterNo, 0 - effIter->second, (effIter->second / monsterMaxHP)*100.0f, false);
			}
			break;
		case EFFECT_ATTRIBUTE::CURRENT_SP:
			//TODO:Other effects
			break;
		}
		effIter++;
	}
}

void BattleFieldScene::switchOwner() {
	if (_roundOwner == PLAYER) {
		map<int, bool>::iterator it = _monsterFinishFlag.begin();
		while (it != _monsterFinishFlag.end()) {
			if (_data->getMonsterStatusAt(it->first) == BATTLER_STATUS::DEAD)
				it->second = true;
			else
				it->second = false;
			it++;
		}
		_roundOwner = COMPUTER;
	}
	else if (_roundOwner == COMPUTER) {
		map<int, bool>::iterator it = _playerFinishFlag.begin();
		while (it != _playerFinishFlag.end()) {
			if (_data->getPlayerStatusAt(it->first) == BATTLER_STATUS::DEAD)
				it->second = true;
			else
				it->second = false;
			it++;
		}
		_roundOwner = PLAYER;
	}
}