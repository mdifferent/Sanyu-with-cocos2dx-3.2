#ifndef __WALKER_LAYER_H__
#define __WALKER_LAYER_H__

#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

class WalkerLayer : public Layer
{
public:
	WalkerLayer(string name, int count, float ypos);
	~WalkerLayer();

	bool init();
	

	void surpriseTrigger();

private:
	string _name;
	int _frameCount;
	float _vPos;
};

#endif