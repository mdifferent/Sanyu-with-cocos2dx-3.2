#ifndef __MONSTER_LAYER_H__
#define __MONSTER_LAYER_H__

#include "cocos2d.h"

USING_NS_CC;

class battledata::MonsterData;

class MonsterLayer : public Layer
{
public:
	MonsterLayer();
	~MonsterLayer();

	virtual bool init();
	static MonsterLayer* createWithData(const map<int, battledata::MonsterData*>& data);

private:

};
#endif