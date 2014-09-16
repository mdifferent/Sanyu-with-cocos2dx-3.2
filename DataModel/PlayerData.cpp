#include "PlayerData.h"

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