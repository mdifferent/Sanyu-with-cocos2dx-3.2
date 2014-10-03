#include "DigitSprite.h"
#include "Resources.h"
#include "ConstValues.h"

bool DigitSprite::init()
{
	if (!Node::init())
		return false;
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(DIGIT_PLIST_PATH, DIGIT_PNG_PATH);
	extendSpriteBatch(DEFAULT_DAMAGE_DIGIT);
	setOpacity(255);
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
		sprite->setOpacity(255);
		//sprite->runAction(FadeIn::create(0.5f));
		//sprite->runAction(Sequence::create(FadeTo::create(0.5f, 255), MoveBy::create(0.5f, Vec2(0, 50)), NULL));
		sprite->runAction(MoveBy::create(0.5f, Vec2(0, 50)));
	}
	
	for each (Node* sprite in getChildren()) {
		sprite->runAction(Sequence::createWithTwoActions(FadeOut::create(0.5f),	MoveBy::create(0.1f, Vec2(0, -50))));
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