#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"
#include <string>
#include "CommonUtils.h"
USING_NS_CC;
using namespace std;

enum class BG_TRANSITION_TYPE {
	FADE,
	DISSOLVE
};

class BackgroundLayer : public Layer
{
public:
	BackgroundLayer(const string name) : _bgName(name) {}

	bool init();
	CREATE_FUNC_WITH_STRING(BackgroundLayer, name);

	void onEnter();

	void switchBg(const string, BG_TRANSITION_TYPE, float para = 0.5f);
	void showBg(ActionInterval*);
	void hideBg(ActionInterval*);
private:
	string _bgName;
	Sprite* _main;
	Sprite* _next;
};
#endif