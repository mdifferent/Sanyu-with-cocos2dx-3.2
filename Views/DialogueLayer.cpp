//
//  DialogueLayer.cpp
//  Sanyu
//
//  Created by wuhanming on 14-9-7.
//
//

#include "DialogueLayer.h"

DialogueLayer::DialogueLayer(const string bg)
{
	_bg = bg;
}

bool DialogueLayer::init()
{
	if (!Layer::init())
		return false;
	return true;
}