#ifndef __PLAYER_LAYER_H__
#define __PLAYER_LAYER_H__

#include "cocos2d.h"
#include <map>
USING_NS_CC;
using namespace std;

class battledata::PlayerData;

class PlayerLayer : public Layer
{
public:
	PlayerLayer();
	~PlayerLayer();

	virtual bool init();
	static PlayerLayer* createWithData(const map<int, battledata::PlayerData*>& data);

private:
};
#endif