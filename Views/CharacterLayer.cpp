//
//  CharacterLayer.cpp
//  Sanyu
//
//  Created by wuhanming on 14-9-7.
//
//

#include "CharacterLayer.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
#include "../proj.win32/WIN32Utils.h"
#endif 

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
		sprite->setOpacity(255);
		sprite->runAction(MoveBy::create(transTime, Vec2(0, spriteSize.height)));
		break;
	case CHAR_TRANSITION::MOVE_TOP_BOUND:
		sprite->setPosition(_posDefine[pos].x, screenSize.height);
		sprite->setOpacity(255);
		sprite->runAction(MoveBy::create(transTime, Vec2(0, -screenSize.height)));
		break;
	case CHAR_TRANSITION::MOVE_LEFT_BOUND:
		sprite->setPosition(0-spriteSize.width*0.5, 0);
		sprite->setOpacity(255);
		sprite->runAction(MoveTo::create(transTime, Vec2(_posDefine[pos].x, 0)));
		break;
	case CHAR_TRANSITION::MOVE_RIGHT_BOUND:
		sprite->setPosition(screenSize.width + spriteSize.width*0.5, 0);
		sprite->setOpacity(255);
		sprite->runAction(MoveTo::create(transTime, Vec2(_posDefine[pos].x, 0)));
		break;
	case CHAR_TRANSITION::MOVE_BETWEEN:
		sprite->runAction(MoveTo::create(transTime, _posDefine[pos]));
		break;
	case CHAR_TRANSITION::DISSOLVE:
		sprite->setPosition(_posDefine[pos]);
		sprite->runAction(FadeIn::create(transTime));
		break;
	default:
		sprite->setPosition(_posDefine[pos]);
		sprite->setOpacity(255);
		break;
	}
}

string CharacterLayer::composePath(string name, list<string>& property)
{
	string path = "images/";
	path.append(name);
	for (string prop : property) {
		path.append("_");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		GBKToUTF(prop);
#endif
		path.append(prop);
	}
	path.append(".png");
	CCLOG("%s", path);
	return path;
}

void CharacterLayer::showCharacter(string name, list<string>& property, const string position, CHAR_TRANSITION trans, float transTime)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	GBKToUTF(name);
#endif
	string path = composePath(name, property);
	Sprite* sprite = nullptr;
	if (_charsPos.count(name) == 0) {
		//If this character haven't been shown on screen
		//Create a new one on position, may be on top of another one
		sprite = Sprite::create(path);
		if (sprite != nullptr) {
			sprite->setAnchorPoint(Vec2(0.5, 0));
			sprite->setOpacity(0);
			sprite->setName(name);
			addChild(sprite);
			if (position.length() == 0) {
				displayOnPosition(sprite, "center", trans, transTime);
				_charsPos[name] = "center";
			}
			else {
				displayOnPosition(sprite, position, trans, transTime);
				_charsPos[name] = position;
			}
		}
		else {
			CCLOG("Error in create sprite : %s", path);
		}
	}
	else {
		//If this character has been shown on screen
		string currentPosStr = _charsPos[name];
		sprite = static_cast<Sprite*>(this->getChildByName(name));
		if (currentPosStr == position || position.length() == 0) {
			//sprite->setOpacity(0);
			sprite->setTexture(path);
			/*TODO: Other effect
			if (trans == CHAR_TRANSITION::DISSOLVE)
				displayOnPosition(sprite, position, trans, transTime);
			else 
				displayOnPosition(sprite, position, CHAR_TRANSITION::NONE, transTime);*/
		}
		else {
			//change position and texture
			sprite->setTexture(path);
			if (trans == CHAR_TRANSITION::MOVE_BETWEEN)
				displayOnPosition(sprite, position, trans, transTime);
			else
				displayOnPosition(sprite, position, CHAR_TRANSITION::NONE, transTime);
			_charsPos[name] = position;
		}
	}
}

void CharacterLayer::showCharacter(string name, list<string>& property, Vec2 posistion, CHAR_TRANSITION tran, float transTime)
{
    
}

void CharacterLayer::showCharacter(string name, list<string>& property, float xpos, CHAR_TRANSITION tran, float transTime)
{
	showCharacter(name, property, Vec2(xpos, 0), tran, transTime);
}

void CharacterLayer::removeCharacter(string name, CHAR_TRANSITION tran, float transTime)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	GBKToUTF(name);
#endif
	Sprite* sprite = static_cast<Sprite*>(this->getChildByName(name));
	Size screenSize = Director::getInstance()->getWinSize();
	if (sprite != nullptr && _charsPos.count(name) > 0) {
		Size spriteSize = sprite->getContentSize();
		auto removeSpriteAction = CallFunc::create([this,name](){ this->removeChildByName(name); });
		switch (tran)
		{
		case CHAR_TRANSITION::DISSOLVE:
			sprite->runAction(Sequence::createWithTwoActions(FadeOut::create(transTime), removeSpriteAction));
			break;
		case CHAR_TRANSITION::MOVE_TOP_BOUND:
			sprite->runAction(Sequence::createWithTwoActions(MoveBy::create(transTime, Vec2(0, screenSize.height)), removeSpriteAction));
			break;
		case CHAR_TRANSITION::MOVE_BOTTOM_BOUND:
			sprite->runAction(Sequence::createWithTwoActions(MoveBy::create(transTime, Vec2(0, -spriteSize.height)), removeSpriteAction));
			break;
		case CHAR_TRANSITION::MOVE_LEFT_BOUND:
			sprite->runAction(Sequence::createWithTwoActions(MoveTo::create(transTime, Vec2(-spriteSize.width*0.5, 0)), removeSpriteAction));
			break;
		case CHAR_TRANSITION::MOVE_RIGHT_BOUND:
			sprite->runAction(Sequence::createWithTwoActions(MoveTo::create(transTime, Vec2(screenSize.width + spriteSize.width*0.5, 0)), removeSpriteAction));
			break;
		default:
			this->removeChildByName(name);
			break;
		}
		_charsPos.erase(name);
	}
	else
		CCLOG("Error in finding character : %s", name);
}

int CharacterLayer::getCharacterCount()
{
	return _charsPos.size();
}
