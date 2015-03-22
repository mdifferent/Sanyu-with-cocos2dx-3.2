#include "WalkerLayer.h"
#include "ConstValues.h"

WalkerLayer::WalkerLayer(string name, int count, float ypos) :_name(name), _frameCount(count), _vPos(ypos)
{

}

WalkerLayer::~WalkerLayer()
{

}

bool WalkerLayer::init()
{
	if (!Layer::init())	{
		CCLOG("Error in init WalkerLayer!");
		return false;
	}

	float screenWidth = Director::getInstance()->getVisibleSize().width;

	SpriteFrameCache *cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(WALKER_PLIST_PATH, WALKER_TEXTURE_PATH);

	char frameName[30];
	Sprite *walker = Sprite::create();
	walker->setAnchorPoint(Vec2(0.5f, 0.0f));
	walker->setPosition(Vec2(screenWidth * 0.5, _vPos));
	addChild(walker, 0, "walker");

	Animation *walkAnimation = Animation::create();
	for (int i = 1; i <= _frameCount; ++i) {
		sprintf_s(frameName, 20, "%s%d.png", _name.c_str(), i);
		walkAnimation->addSpriteFrame(cache->getSpriteFrameByName(frameName));
	}
	for (int i = _frameCount; i > 1; --i) {
		sprintf_s(frameName, 20, "%s%d.png", _name.c_str(), i);
		walkAnimation->addSpriteFrame(cache->getSpriteFrameByName(frameName));
	}
	walkAnimation->setLoops(-1);
	walkAnimation->setRestoreOriginalFrame(false);
	walkAnimation->setDelayPerUnit(0.2f);

	walker->runAction(RepeatForever::create(Animate::create(walkAnimation)));

	return true;
}



void WalkerLayer::surpriseTrigger()
{
	Sprite *walker = dynamic_cast<Sprite*>(getChildByName("walker"));
	walker->stopAllActions();
	walker->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(_name + "_jing.png"));
}