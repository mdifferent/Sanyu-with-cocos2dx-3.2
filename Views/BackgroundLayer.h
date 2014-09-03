#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"
#include <string>
#include "CommonUtils.h"
USING_NS_CC;
using namespace std;

class BackgroundLayer : public Layer
{
public:
	BackgroundLayer(const string name) : _bgName(name) {}

	bool init();
	CREATE_FUNC_WITH_STRING(BackgroundLayer, name);

	void onEnter();
private:
	string _bgName;
};
#endif