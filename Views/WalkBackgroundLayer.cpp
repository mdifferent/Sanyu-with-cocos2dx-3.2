#include "WalkBackgroundLayer.h"
#include "ConstValues.h"

WalkBackgroundLayer::WalkBackgroundLayer(string prefix, int count) :_prefix(prefix), _sliceCount(count)
{
	_speed = 100.0f;
	_isStopped = false;
}

bool WalkBackgroundLayer::init()
{
	if (!Layer::init())	{
		CCLOG("Error in init WalkBackgroundLayer!");
		return false;
	}

	float screenWidth = Director::getInstance()->getVisibleSize().width;
	float screenHeight = Director::getInstance()->getVisibleSize().height;

	for (int i = 1; i <= _sliceCount; ++i) {
		char path[MAX_FILE_PATH_LENGTH] = {0};
		sprintf(path, WALKING_PATH, _prefix.c_str(), i);
		Sprite *back = Sprite::create(path);
		if (back) {
			back->setAnchorPoint(Vec2(0.0f, 0.5f));
			back->setPosition(Vec2(back->getContentSize().width * (i-1), screenHeight * 0.5));
			addChild(back, 0, i);
		}
		else {
			CCLOG("Error in load walking background no.%d!", i);
			return false;
		}

	}

	scheduleUpdate();

	return true;
}

void WalkBackgroundLayer::update(float dt)
{
	float screenWidth = Director::getInstance()->getVisibleSize().width;
	for (int i = 1; i <= _sliceCount; ++i) {
		Node *child = getChildByTag(i);
		float oldPositionX = child->getPositionX();
		float newPositionX = oldPositionX - dt * _speed;
		child->setPositionX(newPositionX);
		if (child->getPositionX() < 0 - child->getContentSize().width)
			child->setPositionX(screenWidth-10);				
	}
}

void WalkBackgroundLayer::stopWalking()
{
	unscheduleUpdate();
}

float WalkBackgroundLayer::getBottomPos()
{
	float screenHeight = Director::getInstance()->getVisibleSize().height;
	return 0.5 * screenHeight - 0.5 * getChildByTag(1)->getContentSize().height;
}