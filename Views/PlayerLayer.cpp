#include "PlayerLayer.h"
#include "HeadSprite.h"
#include "Resources.h"
#include "ConstValues.h"

bool PlayerLayer::init()
{
	if (!CCLayer::init())
		return false;
	int playerCount = _heads.size();
	float screenWidth = Director::getInstance()->getVisibleSize().width;

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = [&playerCount,this](Touch* touch, Event* event) {
		Vec2 touchPos = touch->getLocationInView();
		CCLOG("Touch at x:%f,y:%f",touchPos.x,touchPos.y);
		if (touchPos.y <= this->getChildByTag(0)->getContentSize().height) {
			for (int i = 0; i < playerCount; i++) {
				Rect rect = this->getChildByTag(i)->getBoundingBox();
				if (rect.containsPoint(touchPos)) {
					switch (_status) {
					case PlayerLayer::PLAYER_LAYER_STATUS::WAIT_TARGET:
						_target = i;
						_status = PlayerLayer::PLAYER_LAYER_STATUS::TARGET_SELECTED;
						return false;
					case PlayerLayer::PLAYER_LAYER_STATUS::MENU_SELECTED:
					case PlayerLayer::PLAYER_LAYER_STATUS::WAIT_COMMAND:
					case PlayerLayer::PLAYER_LAYER_STATUS::MENU_OPEN:
						_selectedPlayer = i;
						openMenu(i);
						return false;
					}
				}
			}
		}
		else if (this->_status == PlayerLayer::PLAYER_LAYER_STATUS::MENU_OPEN) {
			closeMenu();
			_status = PlayerLayer::PLAYER_LAYER_STATUS::WAIT_COMMAND;
			_cmd = PlayerLayer::PLAYER_CMD::NONE;
		}
		return false; 
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);

	for each (pair<int, string> var in _heads) {
		HeadSprite *sprite = HeadSprite::create(var.second);
		float playerWidth = sprite->getContentSize().width;
		float playerHeight = sprite->getContentSize().height;
		float playerX = screenWidth*0.5 + (var.first - playerCount*0.5 + 0.5)*playerWidth;
		float playerY = 0 - playerHeight*0.5;
		sprite->setPosition(playerX, playerY);
		addChild(sprite, 0, var.first);
		PLAYER_HEAD_HEIGHT = sprite->getContentSize().height;
	}

	auto *atkBtn = MenuItemImage::create(MAINMENU_BTN_ATTACK, MAINMENU_BTN_ATTACK_PRESSED, CC_CALLBACK_1(PlayerLayer::playerAttackCallback, this));
	auto *skillBtn = MenuItemImage::create(MAINMENU_BTN_SKILL, MAINMENU_BTN_SKILL_PRESSED, CC_CALLBACK_1(PlayerLayer::playerSkillCallback, this));
	auto *itemBtn = MenuItemImage::create(MAINMENU_BTN_ITEM, MAINMENU_BTN_ITEM_PRESSED, CC_CALLBACK_1(PlayerLayer::playerItemCallback, this));
	auto *guardBtn = MenuItemImage::create(MAINMENU_BTN_GUARD, MAINMENU_BTN_GUARD_PRESSED, CC_CALLBACK_1(PlayerLayer::playerGuardCallback, this));
	auto *escapeBtn = MenuItemImage::create(MAINMENU_BTN_ESCAPE, MAINMENU_BTN_ESCAPE_PRESSED, CC_CALLBACK_1(PlayerLayer::playerEscapeCallback, this));
	auto *playerMenu = Menu::create(atkBtn, skillBtn, itemBtn, guardBtn, escapeBtn, NULL);
	playerMenu->alignItemsVertically();
	playerMenu->setEnabled(false);
	playerMenu->setOpacity(0);
	playerMenu->setPosition(-10, -10);
	addChild(playerMenu, 1, "menu");

	_status = PlayerLayer::PLAYER_LAYER_STATUS::WAIT_COMMAND;
	_cmd = PlayerLayer::PLAYER_CMD::NONE;

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

void PlayerLayer::playerAttackCallback(Ref* pSender)
{
	_status = PlayerLayer::PLAYER_LAYER_STATUS::MENU_SELECTED;
	_cmd = PlayerLayer::PLAYER_CMD::ATTACK;
	closeMenu();
	//m_data->at(m_selectedPlayer)->setStatus(NORMAL);
}

void PlayerLayer::playerSkillCallback(Ref* pSender)
{
	_status = PlayerLayer::PLAYER_LAYER_STATUS::MENU_SELECTED;
	_cmd = PlayerLayer::PLAYER_CMD::SKILL;
	closeMenu();
	//m_data->at(m_selectedPlayer)->setStatus(NORMAL);
}

void PlayerLayer::playerGuardCallback(Ref* pSender)
{
	//m_data->at(m_selectedPlayer)->setStatus(DEFENSE);
	_status = PlayerLayer::PLAYER_LAYER_STATUS::MENU_SELECTED;
	_cmd = PlayerLayer::PLAYER_CMD::GUARD;
	closeMenu();
}

void PlayerLayer::playerEscapeCallback(Ref* pSender)
{
	_status = PlayerLayer::PLAYER_LAYER_STATUS::MENU_SELECTED;
	_cmd = PlayerLayer::PLAYER_CMD::ESCAPE;
	closeMenu();
	//m_data->at(m_selectedPlayer)->setStatus(NORMAL);
}

void PlayerLayer::playerItemCallback(Ref* pSender)
{
	_status = PlayerLayer::PLAYER_LAYER_STATUS::MENU_SELECTED;
	_cmd = PlayerLayer::PLAYER_CMD::ITEM;
	closeMenu();
	//m_data->at(m_selectedPlayer)->setStatus(NORMAL);
}

void PlayerLayer::openMenu(int pos)
{
	Point middlePoint = this->getChildByTag(pos)->getPosition();
	Menu *pMenu = (Menu*)this->getChildByName("menu");
	pMenu->setEnabled(true);
	pMenu->setPosition(Vec2(middlePoint.x + 50, middlePoint.y + 60));
	pMenu->runAction(FadeIn::create(0.2f));
	_status = PlayerLayer::PLAYER_LAYER_STATUS::MENU_OPEN;
	_cmd = PlayerLayer::PLAYER_CMD::NONE;
}

void PlayerLayer::closeMenu(void)
{
	Menu *pMenu = (Menu*)this->getChildByName("menu");
	if (pMenu->getOpacity() > 0) {
		pMenu->runAction(CCFadeOut::create(0.2f));
		pMenu->setEnabled(false);
	}
}

void PlayerLayer::onPlayerPropModified(int type, int target, int value)
{
	HeadSprite *sprite = (HeadSprite*)this->getChildByTag(target);
	sprite->onValueModified(value, type);
}

void PlayerLayer::beforeSpecialAttack(int playerNo)
{
	float middleX = Director::getInstance()->getVisibleSize().width/2;
	for each (pair<int, string> var in _heads) {
		if (var.first != playerNo)
			this->getChildByTag(var.first)->runAction(FadeOut::create(0.5f));
	}
	float horiDistance = middleX*0.5 - this->getChildByTag(playerNo)->getPositionX();
	this->getChildByTag(playerNo)->runAction(MoveBy::create(0.5f, Vec2(horiDistance, 0)));
}

void PlayerLayer::afterSpecialAttack(int playerNo)
{
	int playerCount = _heads.size();
	float middleX = Director::getInstance()->getVisibleSize().width / 2;
	float playerPosX = this->getChildByTag(playerNo)->getPositionX();
	float headWidth = this->getChildByTag(playerNo)->getContentSize().width;
	float horiDistance = middleX + (playerNo - playerCount*0.5 + 0.5)*headWidth - playerPosX;
	this->getChildByTag(playerNo)->runAction(MoveBy::create(1.0f, Vec2(horiDistance, 0)));
	for each (pair<int, string> var in _heads) {
		if (var.first != playerNo)
			this->getChildByTag(var.first)->runAction(FadeIn::create(0.5f));
	}
}