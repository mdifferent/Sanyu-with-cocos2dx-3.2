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

	float xpos = Director::getInstance()->getVisibleSize().width * 0.5;
	Sprite *bg = Sprite::create(_bg);
	float anchorPos = bg->getContentSize().width * 0.5;
	bg->setAnchorPoint(Vec2(0, anchorPos));
	bg->setPosition(xpos, 0);
	addChild(bg, 0, "bg");

	if (GlobalConfig::getInstance()->getFontPath().length() == 0) {
		TTFConfig ttf;
		ttf.fontFilePath = GlobalConfig::getInstance()->getFontPath();
		_contentLabel = Label::createWithTTF(ttf,"");
	}
	else {
		_contentLabel = Label::create();
		_contentLabel->setMaxLineWidth(GlobalConfig::getInstance()->getTextAreaWidth());
	}

	_contentLabel->setPosition(GlobalConfig::getInstance()->getTextLeftTop());
	_contentLabel->setAnchorPoint(Vec2(0, 1));
	_contentLabel->setOpacity(0);

	return true;
}

void DialogueLayer::showText(const string content, const string font, const int size)
{
	_contentLabel->setString(content);
	_contentLabel->setSystemFontName(font);
	_contentLabel->setSystemFontSize(size);
	_contentLabel->setOpacity(255);

	
}

void DialogueLayer::showTextWithName(const string name, const string content, const string font, const int size)
{

}

void DialogueLayer::showTextWithNameAndHead(const string name, const string content, const string font, const int size)
{

}