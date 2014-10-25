#include "BattleData.h"
#include "PlayerData.h"
#include "MonsterData.h"

BattleData::BattleData(void)
{
	string name1 = "XT";
	string name2 = "罹子";
	string name3 = "豆包";
	string name4 = "神乐";
	PlayerData *pd1 = new PlayerData(name1);
	pd1->setProperty(PLAYER_PROP_TYPE::MAX_HP, 500);
	pd1->setProperty(PLAYER_PROP_TYPE::CURRENT_HP, 500);
	pd1->setProperty(PLAYER_PROP_TYPE::MAX_SP, 500);
	pd1->setProperty(PLAYER_PROP_TYPE::CURRENT_SP, 500);
	pd1->setProperty(PLAYER_PROP_TYPE::MELEE_ATTACK, 30);
	pd1->setProperty(PLAYER_PROP_TYPE::MELEE_DEFENSE, 10);
	pd1->obtainItem(2);
	pd1->learnSkill(1);
	PlayerData *pd2 = new PlayerData(name2);
	pd2->setProperty(PLAYER_PROP_TYPE::MAX_HP, 500);
	pd2->setProperty(PLAYER_PROP_TYPE::CURRENT_HP, 500);
	pd2->setProperty(PLAYER_PROP_TYPE::MAX_SP, 500);
	pd2->setProperty(PLAYER_PROP_TYPE::CURRENT_SP, 500);
	pd2->setProperty(PLAYER_PROP_TYPE::MELEE_ATTACK, 30);
	pd2->obtainItem(1);
	pd2->obtainItem(2);
	pd2->obtainItem(2);
	pd2->learnSkill(2);
	PlayerData *pd3 = new PlayerData(name3);
	pd3->setProperty(PLAYER_PROP_TYPE::MAX_HP, 500);
	pd3->setProperty(PLAYER_PROP_TYPE::CURRENT_HP, 500);
	pd3->setProperty(PLAYER_PROP_TYPE::MAX_SP, 500);
	pd3->setProperty(PLAYER_PROP_TYPE::CURRENT_SP, 500);
	pd3->setProperty(PLAYER_PROP_TYPE::MELEE_ATTACK, 30);
	pd3->learnSkill(2);
	PlayerData *pd4 = new PlayerData(name4);
	pd4->setProperty(PLAYER_PROP_TYPE::MAX_HP, 500);
	pd4->setProperty(PLAYER_PROP_TYPE::CURRENT_HP, 500);
	pd4->setProperty(PLAYER_PROP_TYPE::MAX_SP, 500);
	pd4->setProperty(PLAYER_PROP_TYPE::CURRENT_SP, 500);
	pd4->setProperty(PLAYER_PROP_TYPE::MELEE_ATTACK, 30);

	_players.insert(std::pair<int, PlayerData*>(0, pd1));
	_players.insert(std::pair<int, PlayerData*>(1, pd2));
	_players.insert(std::pair<int, PlayerData*>(2, pd3));
	_players.insert(std::pair<int, PlayerData*>(3, pd4));
	MonsterData *pdm1 = new MonsterData("森林镰鼠");
	pdm1->setProperty(PLAYER_PROP_TYPE::MAX_HP, 200);
	pdm1->setProperty(PLAYER_PROP_TYPE::CURRENT_HP, 200);
	pdm1->setProperty(PLAYER_PROP_TYPE::MELEE_ATTACK, 50);
	pdm1->setProperty(PLAYER_PROP_TYPE::MELEE_DEFENSE, 5);
	MonsterData *pdm2 = new MonsterData("森林镰鼠老大");
	pdm2->setProperty(PLAYER_PROP_TYPE::MAX_HP, 300);
	pdm2->setProperty(PLAYER_PROP_TYPE::CURRENT_HP, 300);
	pdm2->setProperty(PLAYER_PROP_TYPE::MELEE_ATTACK, 70);
	pdm2->setProperty(PLAYER_PROP_TYPE::MELEE_DEFENSE, 10);
	MonsterData *pdm3 = new MonsterData("森林镰鼠");
	pdm3->setProperty(PLAYER_PROP_TYPE::MAX_HP, 200);
	pdm3->setProperty(PLAYER_PROP_TYPE::CURRENT_HP, 200);
	pdm3->setProperty(PLAYER_PROP_TYPE::MELEE_ATTACK, 50);
	pdm3->setProperty(PLAYER_PROP_TYPE::MELEE_DEFENSE, 5);
	_monsters.insert(std::pair<int, MonsterData*>(0, pdm1));
	_monsters.insert(std::pair<int, MonsterData*>(1, pdm2));
	_monsters.insert(std::pair<int, MonsterData*>(2, pdm3));

	_winCon = WINNING_CONDITIONS::KILL_ALL;
	_loseCon = LOSE_CONDITION::ALL_DEAD;

	_roundLimit = 0;
}

BattleData::~BattleData()
{
	for each (pair<int, PlayerData*> var in _players) {
		delete var.second;
	}

	for each (pair<int, MonsterData*> var in _monsters)	{
		delete var.second;
	}
}

BattleData* BattleData::loadData(int sceneNo)
{
	BattleData *data = new BattleData();
	if (data) {
		data->setMapName("images/bk.jpg");
	}
	return data;
}

map<int, string>* BattleData::getPlayerNames()
{
	map<int, string> *names = new map<int, string>();
	for each (pair<int, PlayerData*> var in _players) {
		names->insert(make_pair(var.first, var.second->getName()));
	}
	return names;
}

map<int, string>* BattleData::getMonsterNames()
{
	map<int, string> *names = new map<int, string>();
	for each (pair<int, MonsterData*> var in _monsters)	{
		names->insert(make_pair(var.first, var.second->getName()));
	}
	return names;
}
