#include "DigitSprite.h"
#include "Resources.h"
#include "ConstValues.h"

bool DigitSprite::init()
{
	if (!Sprite::init())
		return false;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(DIGIT_PLIST_PATH, DIGIT_PNG_PATH);
	extendSpriteBatch(DEFAULT_DAMAGE_DIGIT);
	setOpacity(0);
	return true;
}

void DigitSprite::showDigit(int value)
{
	string num = to_string(value);
	int avaSpriteCount = getChildrenCount();
	int len = num.length();
	if (len > avaSpriteCount) 
		extendSpriteBatch(len - avaSpriteCount);
	for (int i = 0; i < len;i++) {
		Sprite* sprite = (Sprite*)this->getChildByTag(i);
		sprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("number_" + num.at(i)));
	}
	this->runAction(FadeIn::create(0.1f));
	for each (Node* sprite in getChildren()) 
		sprite->runAction(MoveBy::create(0.5f, Vec2(0, 25)));
	this->runAction(FadeOut::create(0.1f));
}

void DigitSprite::extendSpriteBatch(int delta)
{
	for (int i = this->getChildrenCount(); i < delta; i++) {
		auto sprite = Sprite::createWithSpriteFrameName("number_0");
		sprite->setPosition(getPositionX() + getContentSize().width, getPositionY() + getContentSize().height);
		addChild(sprite, 0, i);
	}
}