#include "PlayerData.h"

void PlayerData::obtainItem(const int id, const int count)
{
	if (_items.find(id) == _items.end())
		_items.insert(make_pair(id, count));
	else
		_items[id] += count;
}

void PlayerData::learnSkill(const int id, const int level)
{
	if (_skills.find(id) == _skills.end())
		_skills.insert(make_pair(id, level));
	else
		_skills[id] = level;
}

int PlayerData::useItem(const int id) 
{ 
	_items[id] -= 1; 
	if (_items[id] == 0) {
		_items.erase(id);
		return 0;
	}

	return _items[id];
}

void PlayerData::useSkill(const int id)
{

}