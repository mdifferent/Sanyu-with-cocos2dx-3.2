#include "PlayerLayer.h"
#include "HeadSprite.h"
#include "Resources.h"

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
				Vec2 startPoint = this->getChildByTag(i)->getAnchorPointInPoints();
				CCLOG("%d start at x:%f,y:%f", i, startPoint.x, startPoint.y);
				Size size = this->getChildByTag(i)->getContentSize();
				Rect rect = Rect(startPoint.x, startPoint.y, size.width, size.height);
				if (rect.containsPoint(touchPos)) {
					switch (_status) {
					case WAIT_TARGET:
						_target = i;
						_status = TARGET_SELECTED;
						return false;
					case MENU_SELECTED:
					case WAIT_COMMAND:
					case MENU_OPEN:
						_selectedPlayer = i;
						openMenu(i);
						return false;
					}
				}
			}
		}
		else if (this->_status == MENU_OPEN) {
			closeMenu();
			_status = WAIT_COMMAND;
			_cmd = NONE;
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

	_status = WAIT_COMMAND;
	_cmd = NONE;

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
	_status = MENU_SELECTED;
	_cmd = ATTACK;
	closeMenu();
	//m_data->at(m_selectedPlayer)->setStatus(NORMAL);
}

void PlayerLayer::playerSkillCallback(Ref* pSender)
{
	_status = MENU_SELECTED;
	_cmd = SKILL;
	closeMenu();
	//m_data->at(m_selectedPlayer)->setStatus(NORMAL);
}

void PlayerLayer::playerGuardCallback(Ref* pSender)
{
	//m_data->at(m_selectedPlayer)->setStatus(DEFENSE);
	_status = MENU_SELECTED;
	_cmd = GUARD;
	closeMenu();
}

void PlayerLayer::playerEscapeCallback(Ref* pSender)
{
	_status = MENU_SELECTED;
	_cmd = ESCAPE;
	closeMenu();
	//m_data->at(m_selectedPlayer)->setStatus(NORMAL);
}

void PlayerLayer::playerItemCallback(Ref* pSender)
{
	_status = MENU_SELECTED;
	_cmd = ITEM;
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
	_status = MENU_OPEN;
	_cmd = NONE;
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