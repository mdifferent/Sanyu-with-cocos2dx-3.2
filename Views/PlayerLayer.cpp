#include "PlayerLayer.h"

bool PlayerLayer::init()
{
	return true;
}

PlayerLayer* PlayerLayer::createWithNames(const map<int, string>* names)
{
	PlayerLayer *layer = new PlayerLayer(names);
	if (layer && layer->init()) {
		layer->autorelease();
		return layer;
	}
	else {
		CC_SAFE_DELETE(layer);
		return NULL;
	}
}