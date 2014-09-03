#ifndef __INFOBAR_LAYER_H__
#define __INFOBAR_LAYER_H__

#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

class InfoBarLayer : public Layer
{
public:
	bool init();
	CREATE_FUNC(InfoBarLayer);

	void showText(string text, float secs);
	void clearText();

private:
	Label* _infoLabel;
};
#endif