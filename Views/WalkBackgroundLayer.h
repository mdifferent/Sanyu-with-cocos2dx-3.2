#ifndef __WALK_BACKGROUND_LAYER_H__
#define __WALK_BACKGROUND_LAYER_H__

#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

class WalkBackgroundLayer : public Layer
{
public:
	WalkBackgroundLayer(string prefix, int count = 2);
	~WalkBackgroundLayer(){};

	bool init();
	void update(float);
	float getBottomPos();
	void stopWalking();

private:
	string _prefix;
	int _sliceCount;
	bool _isStopped;
	float _speed;
};

#endif