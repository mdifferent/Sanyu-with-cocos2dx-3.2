#ifndef __MONSTER_DATA_H__
#define __MONSTER_DATA_H__

#include "AbstractBattlerData.h"

namespace battledata {
	enum MONSTER_TYPE {
		A
	};

	class MonsterData : public AbstractBattlerData
	{
	public:
		MonsterData(const string name) : AbstractBattlerData(name){}
		~MonsterData(void){}

	private:
		MONSTER_TYPE	_type;
		int				_exp;
	};
}

#endif