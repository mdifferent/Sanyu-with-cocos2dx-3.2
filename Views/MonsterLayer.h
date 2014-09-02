#ifndef __MONSTER_LAYER_H__
#define __MONSTER_LAYER_H__

#include "cocos2d.h"
#include <map>
#include <string>

USING_NS_CC;
using namespace std;

class MonsterLayer : public Layer
{
public:
	MonsterLayer(const map<int, string>* names) { _heads = *names; }
	~MonsterLayer() { delete &_heads; }

	bool init();
	static MonsterLayer* createWithNames(const map<int, string>*);
private:
	map<int, string> _heads;
};
#endif