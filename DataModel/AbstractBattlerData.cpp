#include "AbstractBattlerData.h"

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