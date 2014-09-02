#ifndef __BATTLER_DATA_H__
#define __BATTLER_DATA_H__

#include <map>
#include <string>

#include "cocos2d.h"

using namespace std;

namespace battledata
{
	enum PLAYER_PROP_TYPE
	{
		MAX_HP,
		CURRENT_HP,
		MAX_SP,
		CURRENT_SP,
		LEVEL,
		EXP,
		MELEE_ATTACK,
		MELEE_DEFENSE
	};

	enum BATTLER_STATUS {
		NORMAL,
		DEAD,
		DEFENSE,
		FINISHED
	};

	class AbstractBattlerData
	{
	public:
		AbstractBattlerData(string name);
		AbstractBattlerData(const AbstractBattlerData &data);
		~AbstractBattlerData(void) {};

		const string getName() const { return _name; }
		const BATTLER_STATUS getStatus() const { return _status; }
		void setStatus(const BATTLER_STATUS status) { _status = status; }

		void setProperty(const PLAYER_PROP_TYPE, const int);
		int getProperty(const PLAYER_PROP_TYPE) const;

	private:
		string _name;
		BATTLER_STATUS _status;
		map<PLAYER_PROP_TYPE, int> _properties;	//name-value
		map<int, int> _items;						//id-amount
		map<int, int> _skills;						//id-level
		map<PLAYER_PROP_TYPE, int> _buffs;
	};
}


#endif