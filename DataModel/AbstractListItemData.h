#ifndef __LIST_ITEM_DATA_H__
#define __LIST_ITEM_DATA_H__
#include <string>
#include <map>

using namespace std;

namespace listdata {

	enum TargetType { FRIEND, ENEMY };
	enum EffectAttribute { MAX_HP, CURRENT_HP, MAX_SP, CURRENT_SP, MELEE_ATTACK = 6, DEFENSE };

	class AbstractListItemData
	{
	public:
		AbstractListItemData(int id, string name, TargetType target, bool multi)
			:_id(id), _name(name), _targetType(target), _isMultiTarget(multi) {}
		~AbstractListItemData() {}

		string getName() const { return _name; }
		TargetType getTargetType() const { return _targetType; }
		bool getMultiTarget() const { return _isMultiTarget; }
		map<EffectAttribute, int> &getItemEffects() { return _effects; }
		void setEffect(pair<EffectAttribute, int> effect) { _effects[effect.first] = effect.second; }

	protected:
		int							_id;
		string						_name;
		bool						_isMultiTarget;
		TargetType					_targetType;
		map<EffectAttribute, int>	_effects;
	};
}
#endif