#include "AbstractBattlerData.h"

AbstractBattlerData::AbstractBattlerData(string name) :_name(name)
{
	_properties.insert(make_pair(PLAYER_PROP_TYPE::MAX_HP, 0));
	_properties.insert(make_pair(PLAYER_PROP_TYPE::CURRENT_HP, 0));
	_properties.insert(make_pair(PLAYER_PROP_TYPE::MAX_SP, 0));
	_properties.insert(make_pair(PLAYER_PROP_TYPE::CURRENT_SP, 0));
	_properties.insert(make_pair(PLAYER_PROP_TYPE::MELEE_ATTACK, 0));
	_properties.insert(make_pair(PLAYER_PROP_TYPE::MELEE_DEFENSE, 0));
}

pair<int, int> AbstractBattlerData::getItem(int num)
{
	map<int, int>::const_iterator itemIt = _items.begin();
	for (size_t i = 0; i < num; i++) {
		itemIt++;
	}
	return make_pair(itemIt->first, itemIt->second);
}

pair<int, int> AbstractBattlerData::getSkill(int num)
{
	map<int, int>::const_iterator itemIt = _skills.begin();
	for (size_t i = 0; i < num; i++) {
		itemIt++;
	}
	return make_pair(itemIt->first, itemIt->second);
}