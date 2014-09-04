#include "MonsterLayer.h"
#include "Resources.h"

bool MonsterLayer::init()
{
	if (!Layer::init())
		return false;

	int playerCount = _heads.size();
	float screenWidth = Director::getInstance()->getVisibleSize().width;
	float screenHeight = Director::getInstance()->getVisibleSize().height;

	for each (pair<int,string> var in _heads) {
		Sprite *sprite = Sprite::create(var.second);
		float xpos = screenWidth*0.5 + (var.first - playerCount*0.5 + 0.5)*screenWidth;
		float ypos = screenHeight*0.6;
		sprite->setPosition(xpos, ypos);
		sprite->setOpacity(0);
		addChild(sprite, 0, var.first);
	}

	//Magic matrix tag
	Sprite *magicTag = Sprite::create(MAGIC_BTN_PATH);
	magicTag->setOpacity(0);
	magicTag->setPosition(ccp(750, 550));
	addChild(magicTag, 1, "magicTag");

	Sprite *magicPointer = Sprite::create(MAGIC_UNAVA_PATH);
	magicPointer->setOpacity(0);
	magicPointer->setPosition(ccp(750, 550));
	addChild(magicPointer, 2, "magicPointer");
	CCTextureCache::sharedTextureCache()->addImage(MAGIC_AVA_PATH);
	CCTextureCache::sharedTextureCache()->addImage(MAGIC_UNAVA_PATH);

	ProgressTimer *longHPBar = ProgressTimer::create(Sprite::create(LONG_HP_BAR));
	longHPBar->setType(ProgressTimer::Type::BAR);
	longHPBar->setMidpoint(ccp(0, 0));
	longHPBar->setPercentage(100);
	longHPBar->setBarChangeRate(ccp(1, 0));
	longHPBar->setOpacity(0);
	longHPBar->setPosition(ccp(screenWidth*0.5, screenHeight*0.3));
	addChild(longHPBar, 2, "hpbar");

	Sprite *timeBarEmpty = Sprite::create(TIME_BAR_EMPTY);
	timeBarEmpty->setOpacity(0);
	timeBarEmpty->setPosition(ccp(screenWidth*0.5, screenHeight*0.7));
	addChild(timeBarEmpty, 2, "timebar_empty");

	ProgressTimer *timeBarFull = ProgressTimer::create(Sprite::create(TIME_BAR_FULL));
	timeBarFull->setType(ProgressTimer::Type::BAR);
	timeBarFull->setMidpoint(ccp(0, 0));
	timeBarFull->setPercentage(100);
	timeBarFull->setBarChangeRate(ccp(1, 0));
	timeBarFull->setOpacity(0);
	timeBarFull->setPosition(ccp(screenWidth*0.5, screenHeight*0.7));
	addChild(timeBarFull, 2, "timebar_full");

	SpriteFrameCache *cache = SpriteFrameCache::sharedSpriteFrameCache();
	cache->addSpriteFramesWithFile(BUBBLE_PLIST_PATH, BUBBLE_TEXTURE_PATH);

	return true;
}

MonsterLayer* MonsterLayer::createWithNames(const map<int, string>* names)
{
	MonsterLayer *layer = new MonsterLayer(names);
	if (layer && layer->init()) {
		layer->autorelease();
		return layer;
	}
	else {
		CC_SAFE_DELETE(layer);
		return NULL;
	}
}