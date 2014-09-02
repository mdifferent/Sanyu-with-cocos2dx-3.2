#ifndef __PLAYER_DATA_H__
#define __PLAYER_DATA_H__

#include "AbstractBattlerData.h"

namespace battledata {
	class PlayerData : public AbstractBattlerData
	{
	public:
		PlayerData(const string name) : AbstractBattlerData(name){};

		int useItem(const int id);
		void obtainItem(const int id, const int iCount = 1);

		void learnSkill(const int id, const int level = 1);
		void useSkill(const int id);
	};
}
#endif