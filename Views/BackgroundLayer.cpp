#include "BackgroundLayer.h"
#include "ConstValues.h"

bool BackgroundLayer::init()
{
	if (!Layer::init())	{
		CCLOG("Error in init CCLayer!");
		return false;
	}

	_main = Sprite::create(_bgName.c_str());
	if (!_main) {
		CCLOG("Error in load bg map!");
		return false;
	}
	else {
		_main->setAnchorPoint(Vec2(0, 0));
	}
	

	_next = Sprite::create();
	_next->setAnchorPoint(Vec2(0, 0));
	_next->setOpacity(0);

	addChild(_main, 0);
	addChild(_next, -1);

	return true;
}

void BackgroundLayer::onEnter()
{
	Layer::onEnter();
	_main->runAction(FadeIn::create(BG_FADEIN_TIME));
}

void BackgroundLayer::switchBg(const string name, BG_TRANSITION_TYPE type, float para)
{
	ActionInterval *action = NULL;
	switch (type)
	{
	case BG_TRANSITION_TYPE::FADE:
		action = FadeOut::create(para*0.5);
		_main->runAction(action);
		_main->setTexture(name);
		showBg(action->reverse());
		break;
	case BG_TRANSITION_TYPE::DISSOLVE:
		_next->setTexture(name);
		_next->setOpacity(255);
		action = FadeOut::create(para);
		_main->runAction(action);
		_main->setTexture(_next->getTexture());
		_main->setOpacity(255);
		_next->setOpacity(0);
	default:
		break;
	}
}

void BackgroundLayer::showBg(ActionInterval* action)
{
	_main->runAction(action);
}

void BackgroundLayer::hideBg(ActionInterval* action)
{
	_main->runAction(action);
}