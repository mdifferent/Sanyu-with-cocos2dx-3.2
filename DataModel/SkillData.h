#ifndef __SKILL_DATA_H__
#define __SKILL_DATA_H__

#include "AbstractListItemData.h"

namespace listdata
{
	enum SKILL_TYPE {
		RECOVER,
		ATTACK,
		ENHENCE,
		WEAKEN
	};

	class SkillData : public AbstractListItemData
	{
	public:
		SkillData(int id, string name, TargetType target, bool multi, int cost, SKILL_TYPE type)
			:AbstractListItemData(id, name, target, multi), _cost(cost), _type(type) {}
		~SkillData(){}

		SKILL_TYPE getSkillType() const { return _type; }
		int getCost() const { return _cost; }
	private:
		int _cost;
		SKILL_TYPE _type;
	};
}

#endif