#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

class BackgroundLayer : public Layer
{
public:
	BackgroundLayer(void);
	~BackgroundLayer(void);

	bool init();
	static BackgroundLayer *createWithMapName(const string name);
private:
	string _bgName;
};
#endif