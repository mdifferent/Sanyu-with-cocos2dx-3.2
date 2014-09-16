#ifndef __BATTLER_DATA_H__
#define __BATTLER_DATA_H__

#include <map>
#include <string>

#include "cocos2d.h"

using namespace std;

	enum class PLAYER_PROP_TYPE
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

	enum class BATTLER_STATUS {
		NORMAL,
		DEAD,
		DEFENSE,
		FINISHED
	};

	class AbstractBattlerData
	{
	public:
		AbstractBattlerData(string name) :_name(name) {}
		AbstractBattlerData(const AbstractBattlerData &data) :_name(data.getName()), _status(data.getStatus()){}
		~AbstractBattlerData(void) {}

		const string getName() const { return _name; }
		const BATTLER_STATUS getStatus() const { return _status; }
		void setStatus(const BATTLER_STATUS status) { _status = status; }

		void setProperty(const PLAYER_PROP_TYPE pro, const int value) { _properties[pro] = value; }
		int getProperty(const PLAYER_PROP_TYPE pro) const { return _properties.at(pro); }
		pair<int, int> getItem(int num);
		pair<int, int> getSkill(int num);
		int getItemCount() { return _items.size(); }
		int getSkillCount() { return _skills.size(); }
		

	protected:
		string _name;
		BATTLER_STATUS _status;
		map<PLAYER_PROP_TYPE, int> _properties;	//name-value
		map<int, int> _items;						//id-amount
		map<int, int> _skills;						//id-level
		map<PLAYER_PROP_TYPE, int> _buffs;
	};


#endif