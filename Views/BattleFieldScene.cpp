#include "BattleFieldScene.h"
#include "BackgroundLayer.h"
#include "InfoBarLayer.h"
#include "PlayerLayer.h"
#include "MonsterLayer.h"
#include "ListLayer.h"
#include "ConstValues.h"
#include "../DataModel/InstanceDatabase.h"

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
		int current = _data->getMonsterProperty(i, battledata::CURRENT_HP);
		int max = _data->getMonsterProperty(i, battledata::MAX_HP)*0.3;
		if (current < max && _data->getMonsterStatusAt(i) != DEAD) {
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
	if (playerStatus == PlayerLayer::WAIT_TARGET && monsterStatus == MonsterLayer::SLEEP) {
		_monsterLayer->resetTarget();
		_playerLayer->resetSelectedMenu();
		_playerLayer->resetSelectedPlayer();
		_playerLayer->resetTarget();
		CCLOG("Monster:sleep, Player: wait");
		return;
	}
	//Open menu
	if (playerStatus == PlayerLayer::MENU_OPEN && monsterStatus == MonsterLayer::SLEEP) {
		_playerLayer->resetSelectedMenu();
		switchList(false);
		return;
	}
	
	//Select command
	if (playerStatus == PlayerLayer::MENU_SELECTED && monsterStatus == MonsterLayer::SLEEP) {
		PlayerLayer::PLAYER_CMD playerCmd = _playerLayer->getSelectedMenu();
		if (playerCmd == PlayerLayer::ATTACK) {
			_monsterLayer->resetTarget();
			_monsterLayer->setStatus(MonsterLayer::WAIT_TARGET);
		}
		else if (playerCmd == PlayerLayer::ITEM || playerCmd == PlayerLayer::SKILL) {
			if (playerCmd == PlayerLayer::ITEM)
				_listLayer->setContentType(ITEM_LIST);
			else
				_listLayer->setContentType(SKILL_LIST);
			switchList(true); //Open select list
		}
		else if (playerCmd == PlayerLayer::GUARD || playerCmd == PlayerLayer::ESCAPE) {
			_monsterLayer->setStatus(MonsterLayer::SLEEP);
			if (playerCmd == PlayerLayer::GUARD)
				_data->setPlayerStatusAt(_playerLayer->getSelectedPlayer(), battledata::DEFENSE);
			_playerFinishFlag[_playerLayer->getSelectedPlayer()] = true;
		}
		return;
	}
	//Attack
	if (playerStatus == PlayerLayer::MENU_SELECTED && _playerLayer->getSelectedMenu() == PlayerLayer::ATTACK) {
		if (monsterStatus == MonsterLayer::WAIT_TARGET) {
			if (_playerLayer->getStatus() == PlayerLayer::MENU_OPEN) {
				_playerLayer->resetSelectedMenu();
				_monsterLayer->setStatus(MonsterLayer::SLEEP);
			}
		}
		else if (monsterStatus == MonsterLayer::TARGET_SELECTED) {
			int attackTarget = _monsterLayer->getTarget();
			int attackSource = _playerLayer->getSelectedPlayer();
			int attackValue = _data->getPlayerProperty(attackSource, battledata::MELEE_ATTACK);
			int defenseValue = _data->getMonsterProperty(attackTarget, MELEE_DEFENSE);
			int damage = attackValue - defenseValue;
			int monsterCurrentHP = _data->getMonsterProperty(attackTarget, battledata::CURRENT_HP);
			int monsteMaxHP = _data->getMonsterProperty(attackTarget, battledata::MAX_HP);
			//TODO:BUFF and DEBUFF may be considered in the futrue
			if (monsterCurrentHP <= damage) {
				_data->setMonsterStatusAt(attackTarget, DEAD);
				_data->setMonsterProperty(attackTarget, battledata::CURRENT_HP, 0);
				_monsterLayer->onAttacked(attackTarget, -damage, (damage / monsteMaxHP) * 100.0f, true);
			}
			else {
				_data->setMonsterProperty(attackTarget, battledata::CURRENT_HP, monsterCurrentHP - damage);
				_monsterLayer->onAttacked(attackTarget, -damage, (damage / monsteMaxHP) * 100.0f, false);
			}
			//CCLOG("Remain HP:%d", m_data->getMonster(iAttackTarget)->getProperty(CURRENT_HP));
			_data->setPlayerStatusAt(attackSource, FINISHED);
			_playerFinishFlag[attackSource] = true;
			_monsterLayer->setStatus(MonsterLayer::SLEEP);
			_playerLayer->setStatus(PlayerLayer::WAIT_COMMAND);
		}
		return;
	}
	
	//Item & Skill 
	//For enemy
	if (playerStatus == PlayerLayer::MENU_SELECTED && monsterStatus == MonsterLayer::TARGET_SELECTED) {
		int attackSource = _playerLayer->getSelectedPlayer();
		if (_playerLayer->getSelectedMenu() == PlayerLayer::ITEM) {
			effectOnMonsters(InstanceDatabase::getDatabaseInstance()->getItemById(getSelectedItemId()));
		}
		else if (_playerLayer->getSelectedMenu() == PlayerLayer::SKILL) {
			int iSkillId = getSelectedItemId();
			SkillData pData = (SkillData&)InstanceDatabase::getDatabaseInstance()->getSkillById(iSkillId);
			int iCost = pData.getCost();
			int iCurrentSP = _data->getPlayerProperty(attackSource, battledata::CURRENT_SP);
			if (iCost <= iCurrentSP) {
				effectOnMonsters(pData);
				_data->setPlayerProperty(attackSource, battledata::CURRENT_SP, iCurrentSP - iCost);
				_playerLayer->onPlayerPropModified(battledata::CURRENT_SP, 0-attackSource, 0 - iCost);
			}
			else
				CCLOG("No enough SP");
		}
		_data->setPlayerStatusAt(attackSource, FINISHED);
		_playerFinishFlag[attackSource] = true;
		_monsterLayer->setStatus(MonsterLayer::SLEEP);
		_playerLayer->setStatus(PlayerLayer::WAIT_COMMAND);
		return;
	}
	//For friend
	if (playerStatus == PlayerLayer::TARGET_SELECTED && monsterStatus == MonsterLayer::SLEEP) {
		int iOperationSource = _playerLayer->getSelectedPlayer();
		int iTargetPlayer = _playerLayer->getTarget();
		int iCurrentHP = _data->getPlayerProperty(iTargetPlayer, battledata::CURRENT_HP);
		int iMaxHP = _data->getPlayerProperty(iTargetPlayer, battledata::MAX_HP);
		int iCurrentSP = _data->getPlayerProperty(iTargetPlayer, battledata::CURRENT_SP);
		int iMaxSP = _data->getPlayerProperty(iTargetPlayer, battledata::MAX_SP);
		int iItemId = getSelectedItemId();
		AbstractListItemData *itemData = NULL;
		if (_playerLayer->getSelectedMenu() == PlayerLayer::ITEM)
			itemData = &InstanceDatabase::getDatabaseInstance()->getItemById(iItemId);
		else if (_playerLayer->getSelectedMenu() == PlayerLayer::SKILL)
			itemData = &InstanceDatabase::getDatabaseInstance()->getSkillById(iItemId);
		if (itemData == NULL) {
			CCLOG("Get item/skill data error!");
			return;
		}
		map<listdata::EffectAttribute, int> effect = itemData->getItemEffects();
		map<listdata::EffectAttribute, int>::iterator effIter = effect.begin();
		while (effIter != effect.end()) {
			switch (effIter->first) {
			case listdata::CURRENT_HP:
				if (iCurrentHP + effIter->second > iMaxHP)
					_data->setPlayerProperty(iTargetPlayer, battledata::CURRENT_HP, iMaxHP);
				else
					_data->setPlayerProperty(iTargetPlayer, battledata::CURRENT_HP, iCurrentHP + effIter->second);
				_playerLayer->onPlayerPropModified(battledata::CURRENT_HP, iTargetPlayer, effIter->second);
				break;
			case listdata::CURRENT_SP:
				if (iCurrentSP + effIter->second > iMaxSP)
					_data->setPlayerProperty(iTargetPlayer, battledata::CURRENT_SP, iMaxSP);
				else
					_data->setPlayerProperty(iTargetPlayer, battledata::CURRENT_SP, iCurrentSP + effIter->second);
				_playerLayer->onPlayerPropModified(battledata::CURRENT_SP, iTargetPlayer, effIter->second);
				break;
			};
			effIter++;
		}
		_data->setPlayerStatusAt(iOperationSource, FINISHED);				//Target conflict with source
		_playerFinishFlag[iOperationSource] = true;
		_monsterLayer->setStatus(MonsterLayer::SLEEP);
		_playerLayer->setStatus(PlayerLayer::WAIT_COMMAND);
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
			int currentHP = _data->getPlayerProperty(0, battledata::CURRENT_HP);
			int maxHP = _data->getPlayerProperty(0, battledata::MAX_HP);
			float damage = maxHP * 0.05;
			if (damage > currentHP) {
				_data->setPlayerStatusAt(0, DEAD);
				_data->setPlayerProperty(0, battledata::CURRENT_HP, 0);
			}
			else {
				_data->setPlayerProperty(0, battledata::CURRENT_HP, currentHP - damage);
			}
			_playerLayer->onPlayerPropModified(battledata::CURRENT_HP, 0, -damage);
		}
		_playerLayer->afterSpecialAttack();
		_playerLayer->setStatus(PlayerLayer::WAIT_COMMAND);
		_monsterLayer->setStatus(MonsterLayer::SLEEP);
		return;
	}
	return;
}

void BattleFieldScene::runComputerRound()
{
	CCLOG("COMPUTER ROUND");
	int mosnterCount = _data->getPlayerCount();
	int playerCount = _data->getMonsterCount();
	int attackTarget = -1;
	int iMinHP = TOP_HP;
	for (int i = 0; i<mosnterCount; i++) {
		CCLOG("Monster %d", i);
		if (_data->getMonsterStatusAt(i) != DEAD) {
			for (int j = 0; j<playerCount; j++) {
				if (_data->getPlayerStatusAt(j) != DEAD && 
					_data->getPlayerProperty(j, battledata::CURRENT_HP)< iMinHP ) {
					iMinHP = _data->getPlayerProperty(j, battledata::CURRENT_HP);
					attackTarget = j;
				}
			}
			int defenseValue = _data->getPlayerProperty(attackTarget, MELEE_DEFENSE);
			int attackValue = _data->getMonsterProperty(i, battledata::MELEE_ATTACK);
			int damageValue = _data->getPlayerStatusAt(attackTarget) == battledata::DEFENSE ? attackValue - defenseValue : attackValue;
			int playerCurrentHP = _data->getPlayerProperty(attackTarget, battledata::CURRENT_HP);
			_playerLayer->onPlayerPropModified(1, attackTarget, damageValue);
			if (damageValue >= playerCurrentHP) {
				_data->setPlayerProperty(attackTarget, battledata::CURRENT_HP, 0);
				_data->setPlayerStatusAt(attackTarget, DEAD);
			}
			else {
				_data->setPlayerProperty(attackTarget, battledata::CURRENT_HP, playerCurrentHP - damageValue);
			}
			_data->setMonsterStatusAt(i, battledata::BATTLER_STATUS::FINISHED);
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
	return NULL;
}
ssize_t BattleFieldScene::numberOfCellsInTableView(TableView *table){ return 0; }
void BattleFieldScene::tableCellTouched(TableView* table, TableViewCell* cell){}

void BattleFieldScene::switchList(bool isOpen) {
	_listLayer->setTouchEnabled(isOpen);
	_listLayer->setVisible(isOpen);
}

void BattleFieldScene::effectOnMonsters(AbstractListItemData& pEffectSource)
{
	if (pEffectSource.getMultiTarget()) {
		int monsterCount = _data->getMonsterCount();
		for (size_t i = 0; i < monsterCount; i++) {
			if (_data->getMonsterStatusAt(i) != DEAD) {
				effectOnMonster(i, pEffectSource);
			}
		}
	}
	else {
		int attackTarget = _monsterLayer->getTarget();
		effectOnMonster(attackTarget, pEffectSource);
	}
}

void BattleFieldScene::effectOnMonster(int monsterNo, AbstractListItemData& pEffectSource)
{
	map<listdata::EffectAttribute, int> effect = pEffectSource.getItemEffects();
	map<listdata::EffectAttribute, int>::iterator effIter = effect.begin();
	int monsterCurrentHP = _data->getMonsterProperty(monsterNo, battledata::CURRENT_HP);
	int monsterMaxHP = _data->getMonsterProperty(monsterNo, battledata::MAX_HP);
	while (effIter != effect.end()) {
		switch (effIter->first) {
		case battledata::CURRENT_HP: 
			if (monsterCurrentHP <= effIter->second) {
				_data->setMonsterStatusAt(monsterNo,DEAD);
				_data->setMonsterProperty(monsterNo, battledata::CURRENT_HP, 0);
				_monsterLayer->onAttacked(monsterNo, 0 - effIter->second, (effIter->second / monsterMaxHP)*100.0f, true);
			}
			else {
				_data->setMonsterProperty(monsterNo, battledata::CURRENT_HP, monsterCurrentHP - effIter->second);
				_monsterLayer->onAttacked(monsterNo, 0 - effIter->second, (effIter->second / monsterMaxHP)*100.0f, false);
			}
			break;
		case battledata::CURRENT_SP:
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
			if (_data->getMonsterStatusAt(it->first) == DEAD)
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
			if (_data->getPlayerStatusAt(it->first) == DEAD)
				it->second = true;
			else
				it->second = false;
			it++;
		}
		_roundOwner = PLAYER;
	}
}