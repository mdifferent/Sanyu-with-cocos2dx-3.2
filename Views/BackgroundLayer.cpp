#include "BackgroundLayer.h"
#include "ConstValues.h"

bool BackgroundLayer::init()
{
	if (!Layer::init())	{
		CCLOG("Error in init CCLayer!");
		return false;
	}
	
	Sprite* sprite = Sprite::create(_bgName.c_str());
	if (!sprite) {
		CCLOG("Error in load bg map!");
		return false;
	}

	addChild(sprite, 0, "bg");

	return true;
}

void BackgroundLayer::onEnter()
{
	Layer::onEnter();
	this->getChildByName("bg")->runAction(FadeIn::create(BG_FADEIN_TIME));
}
