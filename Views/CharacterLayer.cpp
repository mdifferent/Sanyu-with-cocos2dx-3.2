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

	_posDefine[LEFT] = Vec2(winSize.width * 0.25, 0);
	_posDefine[RIGHT] = Vec2(winSize.width * 0.75, 0);
	_posDefine[CENTER] = Vec2(winSize.width * 0.5, 0);

    return true;
}

void CharacterLayer::displayOnPosition(Sprite *sprite, string pos, CHAR_TRANSITION trans, float transTime)
{
	Size screenSize = Director::getInstance()->getWinSize();
	Size spriteSize = sprite->getContentSize();
	switch (trans)
	{
	case CHAR_TRANSITION::MOVE_BOTTOM_BOUND:
		sprite->setPosition(_posDefine[pos].x, 0 - spriteSize.height);
		sprite->runAction(MoveBy::create(transTime, Vec2(0, spriteSize.height)));
	case CHAR_TRANSITION::MOVE_TOP_BOUND:
		sprite->setPosition(_posDefine[pos].x, screenSize.height);
		sprite->runAction(MoveBy::create(transTime, Vec2(0, -screenSize.height)));
	case CHAR_TRANSITION::MOVE_LEFT_BOUND:
		sprite->setPosition(0-spriteSize.width*0.5, 0);
		sprite->runAction(MoveTo::create(transTime, Vec2(_posDefine[pos].x, 0)));
	case CHAR_TRANSITION::MOVE_RIGHT_BOUND:
		sprite->setPosition(screenSize.width + spriteSize.width*0.5, 0);
		sprite->runAction(MoveTo::create(transTime, Vec2(_posDefine[pos].x, 0)));
	case CHAR_TRANSITION::MOVE_BETWEEN:
		sprite->runAction(MoveTo::create(transTime, _posDefine[pos]));
	case CHAR_TRANSITION::DISSOLVE:
		sprite->runAction(FadeIn::create(transTime));
	default:
		sprite->setPosition(_posDefine[pos]);
		sprite->setOpacity(255);
		break;
	}
}

void CharacterLayer::showCharacter(const string& name, list<string>& property, const string position, CHAR_TRANSITION trans, float transTime)
{
	string path;
	path.append(name);
	for (string prop : property) {
		path.append("_");
		path.append(prop);
	}

	Sprite* sprite = nullptr;
	if (_charsPos.count(name) == 0) {						
		//If this character haven't been shown on screen
		//Create a new one on position, may be on top of another one
		sprite = Sprite::create(path);
		if (sprite != nullptr) {
			sprite->setAnchorPoint(Vec2(0.5, 1));
			sprite->setOpacity(0);
			sprite->setName(name);
			addChild(sprite);
			displayOnPosition(sprite, position, trans, transTime);
		}
		else {
			CCLOG("Error in create sprite : %s", path);
		}
		_charsPos[name] = position;
	}
	else {
		//If this character has been shown on screen
		string currentPosStr = _charsPos[name];
		sprite = static_cast<Sprite*>(this->getChildByName(name));
		if (currentPosStr == position) {
			sprite->setOpacity(0);
			sprite->setSpriteFrame(path);
			if (trans == CHAR_TRANSITION::DISSOLVE)
				displayOnPosition(sprite, position, trans, transTime);
			else 
				displayOnPosition(sprite, position, CHAR_TRANSITION::NONE, transTime);
		}
		else {
			//change position and texture
			sprite->setSpriteFrame(path);
			if (trans == CHAR_TRANSITION::MOVE_BETWEEN)
				displayOnPosition(sprite, position, trans, transTime);
			else
				displayOnPosition(sprite, position, CHAR_TRANSITION::NONE, transTime);
			_charsPos[name] = position;
		}
	}
}

void CharacterLayer::showCharacter(const string& name, list<string>& property, Vec2 posistion, CHAR_TRANSITION tran, float transTime)
{
    
}

void CharacterLayer::showCharacter(const string& name, list<string>& property, float xpos, CHAR_TRANSITION tran, float transTime)
{
    
}

void CharacterLayer::removeCharacter(const string& name, CHAR_TRANSITION tran, float transTime)
{
	Sprite* sprite = static_cast<Sprite*>(this->getChildByName(name));
	Size screenSize = Director::getInstance()->getWinSize();
	Size spriteSize = sprite->getContentSize();
	if (sprite != nullptr && _charsPos.count(name) > 0) {
		switch (tran)
		{
		case CHAR_TRANSITION::DISSOLVE:
			sprite->runAction(FadeOut::create(transTime));
			break;
		case CHAR_TRANSITION::MOVE_TOP_BOUND:
			sprite->runAction(MoveBy::create(transTime, Vec2(0, screenSize.height)));
			break;
		case CHAR_TRANSITION::MOVE_BOTTOM_BOUND:
			sprite->runAction(MoveBy::create(transTime, Vec2(0, -spriteSize.height)));
			break;
		case CHAR_TRANSITION::MOVE_LEFT_BOUND:
			sprite->runAction(MoveTo::create(transTime, Vec2(-spriteSize.width*0.5, 0)));
			break;
		case CHAR_TRANSITION::MOVE_RIGHT_BOUND:
			sprite->runAction(MoveTo::create(transTime, Vec2(screenSize.width + spriteSize.width*0.5, 0)));
			break;
		default:
			sprite->setOpacity(0);
			break;
		}
		this->removeChildByName(name);
		_charsPos.erase(name);
	}
	else
		CCLOG("Error in finding character : %s", name);
}

int CharacterLayer::getCharacterCount()
{
	return _charsPos.size();
}
