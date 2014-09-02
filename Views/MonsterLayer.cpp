#include "MonsterLayer.h"

bool MonsterLayer::init()
{
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