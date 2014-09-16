#ifndef __MONSTER_DATA_H__
#define __MONSTER_DATA_H__

#include "AbstractBattlerData.h"

	enum class MONSTER_TYPE {
		A
	};

	class MonsterData : public AbstractBattlerData
	{
	public:
		MonsterData(const string name) : AbstractBattlerData(name){}
	private:
		MONSTER_TYPE	_type;
		int				_exp;
	};

#endif