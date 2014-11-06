//
//  CharacterLayer.cpp
//  Sanyu
//
//  Created by wuhanming on 14-9-7.
//
//

#include "CharacterLayer.h"

bool CharacterLayer::init()
{
	if (!Layer::init())
		return false;

	Size winSize = Director::getInstance()->getWinSize();
	_leftPosX = winSize.width * 0.25;
	_centerPosX = winSize.width * 0.5;
	_rightPosX = winSize.width * 0.75;

	_left = Sprite::create();
	_left->setPosition(Vec2(_leftPosX, 0));
	_left->setAnchorPoint(Vec2(0.5, 0));
	_left->setOpacity(0);
	_center = Sprite::create();
	_center->setPosition(Vec2(_centerPosX, 0));
	_center->setAnchorPoint(Vec2(0.5, 0));
	_center->setOpacity(0);
	_right = Sprite::create();
	_right->setPosition(Vec2(_rightPosX, 0));
	_right->setAnchorPoint(Vec2(0.5, 0));
	_right->setOpacity(0);

    return true;
}

void CharacterLayer::showCharacter(const string& name, const CHAR_POSITION position, Vector<string> property, CHAR_TRANSITION tran)
{
	string path;
	path.append(name);
	for (string prop : property) {
		path.append("_");
		path.append(prop);
	}

	switch (position)
	{
	case CHAR_POSITION::LEFT:
		_left->setSpriteFrame(path);
		break;
	default:
		break;
	}
}

void CharacterLayer::showCharacter(const string& name, Vec2 posistion, Vector<string> *property, CHAR_TRANSITION tran)
{
    
}

void CharacterLayer::showCharacter(const string& name, float xpos, Vector<string> *property, CHAR_TRANSITION tran)
{
    
}

void CharacterLayer::removeCharacter(const string& name, CHAR_TRANSITION tran)
{
    
}

int CharacterLayer::getCharacterCount()
{
    return _characters.size();
}
