#ifndef __PLAYER_LAYER_H__
#define __PLAYER_LAYER_H__

#include "cocos2d.h"
#include <map>
#include <string>
using namespace std;
USING_NS_CC;

class PlayerLayer : public Layer
{
public:
	PlayerLayer(const map<int, string>* names) { _heads = *names; }
	~PlayerLayer() { delete &_heads; }

	bool init();
	static PlayerLayer* createWithNames(const map<int, string>*);
private:
	map<int, string> _heads;
};
#endif