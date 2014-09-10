#ifndef _MONSTER_HEAD_SPRITE_H_
#define _MONSTER_HEAD_SPRITE_H_

#include "cocos2d.h"
#include <string>
#include "CommonUtils.h"

USING_NS_CC;
using namespace std;

class MonsterHeadSprite : public Sprite
{
public:
	MonsterHeadSprite(const string name) { _name = name; }
	bool init();
	CREATE_FUNC_WITH_STRING(MonsterHeadSprite, name);

	void onHPModified(int deltaValue, float percent, bool isDead);
	float getHpPercent();
private:
	string _name;
};

#endif