#include "ListLayer.h"
#include "ConstValues.h"
#include "Resources.h"

bool ListLayer::init() {

	if (!Layer::init()) {
		return false;
	}

	Size winSize = Director::getInstance()->getVisibleSize();
	_pBackImg = Sprite::create(SELECT_LIST_BG_PATH);
	_pTableView = TableView::create(_datasource, Size(BACK_WIDTH, BACK_HEIGHT - BACK_LABEL_HEIGHT));
	_pLabel = Label::createWithSystemFont(SKILL_TITLE, "Arial", 18);
	if (_pBackImg && _pTableView && _pLabel) {
		float fCenterX = winSize.width*0.5;
		float fCenterY = winSize.height*0.5;
		float fWinWidth = _pBackImg->getContentSize().width;
		float fWinHeight = _pBackImg->getContentSize().height;
		float fLabelWidth = _pLabel->getContentSize().width;
		float fLabelHeight = _pLabel->getContentSize().height;
		_pTableView->setDirection(ScrollView::Direction::VERTICAL);
		_pTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
		_pTableView->setPosition(fCenterX - fWinWidth*0.5, fCenterY*1.2 - fWinHeight*0.5);
		_pLabel->setPosition(fCenterX - fWinWidth*0.5 + fLabelWidth*0.5, fCenterY*1.2 + fWinHeight*0.5 - fLabelHeight*0.5);
		_pBackImg->setPosition(fCenterX, fCenterY*1.2);
		this->addChild(_pBackImg, 3);
		this->addChild(_pLabel, 4);
		this->addChild(_pTableView, 4);
		_type = EMPTY;
		_pTableView->reloadData();
	}
	else {
		//CC_SAFE_DELETE(_pBackImg);
		CC_SAFE_DELETE(_pTableView);
		//CC_SAFE_DELETE(_pLabel);
		CCLOG("Create List view error!");
		return false;
	}

	//auto *okBtn = MenuItemImage::create(SELECT_LIST_OK, SELECT_LIST_OK_PRESS, CC_CALLBACK_1(MainMenuScene::startCallback, this));
	//auto *cancelBtn = MenuItemImage::create(SELECT_LIST_CANCEL, SELECT_LIST_CANCEL_PRESS, CC_CALLBACK_1(MainMenuScene::loadCallback, this));

	return true;
}


void ListLayer::setContentType(LIST_TYPE type) {
	if (_type != type) {
		_type = type;
		switch (_type) {
		case ITEM_LIST:
			_pLabel->setString(ITEM_TITLE);
			break;
		case SKILL_LIST:
			_pLabel->setString(SKILL_TITLE);
			break;
		case EMPTY:
			_pLabel->setString("None");
		}
		//_pLabel->setDirty(true);
	}
	_pTableView->reloadData();
}

//Deprecated
void ListLayer::setTouchEnabled(bool value)
{
	Layer::setTouchEnabled(value);
	if (_pTableView)
		_pTableView->setTouchEnabled(value);
}