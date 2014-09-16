#ifndef __SKILL_DATA_H__
#define __SKILL_DATA_H__

#include "AbstractListItemData.h"

	enum class SKILL_TYPE {
		RECOVER,
		ATTACK,
		ENHENCE,
		WEAKEN
	};

	class SkillData : public AbstractListItemData
	{
	public:
		SkillData(int id, string name, TARGET_TYPE target, bool multi, int cost, SKILL_TYPE type)
			:AbstractListItemData(id, name, target, multi), _cost(cost), _type(type) {}

		SKILL_TYPE getSkillType() const { return _type; }
		int getCost() { return _cost; }
	private:
		int _cost;
		SKILL_TYPE _type;
	};


#endif