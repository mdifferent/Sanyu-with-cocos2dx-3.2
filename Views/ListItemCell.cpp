#include "ListItemCell.h"
#include "Resources.h"
#include "ConstValues.h"

ListItemCell *ListItemCell::create(const string name, const string target, const int amount)
{
	ListItemCell *cell = new ListItemCell();
	if (!cell) {
		CC_SAFE_DELETE(cell);
		return NULL;
	}
	else {
		if (cell->init())
			cell->autorelease();
		else {
			CC_SAFE_DELETE(cell);
			return NULL;
		}
	}
	cell->updateLabels(name, target, amount);
	return cell;
}

bool ListItemCell::init(void)
{
	if (!TableViewCell::init()) {
		return false;
	}
	_pItemName = Label::createWithSystemFont("", NAME_FONT, NAME_FONT_SIZE);
	_pTarget = Label::createWithSystemFont("", NAME_FONT, NAME_FONT_SIZE);
	_pAmount = Label::createWithSystemFont("", NAME_FONT, NAME_FONT_SIZE);

	CCSize cellSize = this->getContentSize();
	_pItemName->setPosition(ccp(50, 0));
	addChild(_pItemName, 1);
	_pTarget->setPosition(ccp(200, 0));
	addChild(_pTarget, 1);
	_pAmount->setPosition(ccp(400, 0));
	addChild(_pAmount, 1);
	Texture2D *bgTexture = Director::getInstance()->getTextureCache()->addImage(CELL_BG_PATH);
	_bg = Sprite::create();
	_bg->setTexture(bgTexture);
	_bg->setAnchorPoint(Vec2(0,0));
	_bg->setPosition(Vec2(0, 0));
	addChild(_bg, 0);
	return true;
}

void ListItemCell::updateLabels(const string name, const string target, const int amount)
{
	if (isSelected())
		onDeselected();
	if (name.length() == 0 || amount == 0) {
		_pItemName->setString("");
		_pTarget->setString("");
		_pAmount->setString("");
		return;
	}
	_pItemName->setString(name.c_str());
	_pTarget->setString(target.c_str());
	char amount_char[15];
	_pAmount->setString(_itoa(amount, amount_char, 10));
}