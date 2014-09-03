#include "InfoBarLayer.h"
#include "Resources.h"
#include "ConstValues.h"

bool InfoBarLayer::init()
{
	if (!Layer::init()) {
		CCLOG("Error in init CCLayer!");
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	Sprite* pSprite = Sprite::create(INFO_BAR);
	if (pSprite) {
		this->addChild(pSprite, 0, 0);
		_infoLabel = Label::createWithSystemFont("", NAME_FONT, NAME_FONT_SIZE);
		_infoLabel->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height - 30));
		return true;
	}
	else {
		CCLOG("Error in init create infobar, map name is null!");
		return false;
	}
}

void InfoBarLayer::showText(string text, float secs)
{
	if (_infoLabel->getOpacity() != 0)
		_infoLabel->setOpacity(0);
	_infoLabel->setString(text.c_str());

	ActionInterval *action = FadeIn::create(0.1f);
	if (secs <= 0)
		_infoLabel->runAction(action);
	else
		_infoLabel->runAction(Sequence::create(DelayTime::create(3.0f), action, DelayTime::create(secs), action->reverse(), NULL));
}

void InfoBarLayer::clearText()
{
	if (_infoLabel->getOpacity() > 0)
		_infoLabel->runAction(FadeOut::create(0.1f));
}