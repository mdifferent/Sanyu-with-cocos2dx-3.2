#ifndef __LIST_ITEM_DATA_H__
#define __LIST_ITEM_DATA_H__
#include <string>
#include <map>

using namespace std;

	enum class TARGET_TYPE { FRIEND, ENEMY };
	enum class EFFECT_ATTRIBUTE { MAX_HP, CURRENT_HP, MAX_SP, CURRENT_SP, MELEE_ATTACK = 6, DEFENSE };

	class AbstractListItemData
	{
	public:
		AbstractListItemData(int id, string name, TARGET_TYPE target, bool multi)
			:_id(id), _name(name), _targetType(target), _isMultiTarget(multi) {}
		~AbstractListItemData() {}

		string getName() const { return _name; }
		TARGET_TYPE getTargetType() const { return _targetType; }
		bool getMultiTarget() const { return _isMultiTarget; }
		map<EFFECT_ATTRIBUTE, int> &getItemEffects() { return _effects; }
		void setEffect(pair<EFFECT_ATTRIBUTE, int> effect) { _effects[effect.first] = effect.second; }
		virtual int getCost() = 0;

	protected:
		int							_id;
		string						_name;
		bool						_isMultiTarget;
		TARGET_TYPE					_targetType;
		map<EFFECT_ATTRIBUTE, int>	_effects;
	};
#endif