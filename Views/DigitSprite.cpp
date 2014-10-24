#include "DigitSprite.h"
#include "Resources.h"
#include "ConstValues.h"

bool DigitSprite::init()
{
	if (!Node::init())
		return false;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(DIGIT_PLIST_PATH, DIGIT_PNG_PATH);
	extendSpriteBatch(DEFAULT_DAMAGE_DIGIT);
	this->setCascadeOpacityEnabled(false);
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
		char cnum[10];
		sprintf(cnum, NUMBER_SPRITE_NAME_TEMPLATE, num.at(len - i - 1));
		SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(cnum);
		sprite->setSpriteFrame(spriteFrame);
		sprite->runAction(Sequence::create(FadeIn::create(0.1f), DelayTime::create(0.1*i), MoveBy::create(0.3f, Vec2(0, 30)), 
			DelayTime::create(0.1*(len-i)), FadeOut::create(0.1f), MoveBy::create(0.1f, Vec2(0, -30)), NULL));
	}
}

void DigitSprite::extendSpriteBatch(int delta)
{
	for (int i = this->getChildrenCount(); i < delta; i++) {
		auto sprite = Sprite::createWithSpriteFrameName("number_0");
		float x = getPositionX() - i * sprite->getContentSize().width;
		float y = getPositionY();
		sprite->setPosition(x, y);
		addChild(sprite, 0, i);
		sprite->setOpacity(0);
	}
}