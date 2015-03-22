#include "WalkingScene.h"
#include "BattleFieldScene.h"
#include "WalkBackgroundLayer.h"
#include "WalkerLayer.h"

WalkingScene::WalkingScene(string walkerNamePrefix, int walkerFrameCount, string bgPrefix, int bgFrameCount) 
: _bgPrefix(bgPrefix), _bgFrameCount(bgFrameCount), _walkerNamePrefix(walkerNamePrefix), _walkerFrameCount(walkerFrameCount)
{
}

WalkingScene::~WalkingScene(void)
{
	removeAllChildren();
}

bool WalkingScene::init()
{
	if (!Scene::init()) {
		CCLOG("Error in init WalkingScene!");
		return false;
	}

	auto bgLayer = new WalkBackgroundLayer(_bgPrefix, _bgFrameCount);
	if (bgLayer && bgLayer->init()) {
		bgLayer->autorelease();
		addChild(bgLayer, 0, "bg");
	}
	else {
		CCLOG("Error in create BackgroundLayer!");
		delete bgLayer;
		return false;
	}

	auto walkerLayer = new WalkerLayer(_walkerNamePrefix, _walkerFrameCount, bgLayer->getBottomPos());
	if (walkerLayer && walkerLayer->init()) {
		walkerLayer->autorelease();
		addChild(walkerLayer, 1, "walker");
	}
	else {
		CCLOG("Error in create WalkerLayer!");
		delete walkerLayer;
		return false;
	}

}