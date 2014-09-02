#include "BattleData.h"
#include "PlayerData.h"
#include "MonsterData.h"

BattleData::~BattleData()
{
	for each (pair<int, PlayerData*> var in _players)
	{
		delete var.second;
	}

	for each (pair<int, MonsterData*> var in _monsters)
	{
		delete var.second;
	}
}

BattleData* BattleData::loadData(int sceneNo)
{
	return NULL;
}

map<int, string>* BattleData::getPlayerNames()
{
	map<int, string> *names = new map<int, string>();
	for each (pair<int, PlayerData*> var in _players)
	{
		names->insert(make_pair(var.first, var.second->getName()));
	}
	return names;
}

map<int, string>* BattleData::getMonsterNames()
{
	map<int, string> *names = new map<int, string>();
	for each (pair<int, MonsterData*> var in _monsters)
	{
		names->insert(make_pair(var.first, var.second->getName()));
	}
	return names;
}