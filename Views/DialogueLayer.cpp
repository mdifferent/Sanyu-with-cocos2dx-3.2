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
	bg->setAnchorPoint(Vec2(0.5, 0));
	bg->setPosition(xpos, 0);
	addChild(bg, 0, "bg");

	if (GlobalConfig::getInstance()->getFontPath().length() > 0) {
		TTFConfig ttf;
		ttf.fontFilePath = GlobalConfig::getInstance()->getFontPath();
		_contentLabel = Label::createWithTTF(ttf,"");
	}
	else {
		_contentLabel = Label::create();
		_contentLabel->setDimensions(GlobalConfig::getInstance()->getTextAreaWidth(), 
			GlobalConfig::getInstance()->getTextAreaHeight());
	}

	_contentLabel->setAnchorPoint(Vec2(0, 1));
	_contentLabel->setPosition(GlobalConfig::getInstance()->getTextLeftTop());
	_contentLabel->setOpacity(0);
	//addChild(_contentLabel, 1);

	return true;
}

void DialogueLayer::showText(const string content, const string font, const int size, Color3B color)
{
	_contentLabel->setString(content);
	_contentLabel->setSystemFontName(font);
	_contentLabel->setSystemFontSize(size);
	_contentLabel->setOpacity(255);
	_contentLabel->setColor(color);
	
	
	auto clip = LayerColor::create(Color4B::BLACK, 24, 24);
	//clip->setAnchorPoint(Vec2(0, 1));
	clip->setPosition(GlobalConfig::getInstance()->getTextLeftTop());

	Node* stencil = Node::create();
	stencil->addChild(clip,-1);

	ClippingNode* clippingNode = ClippingNode::create(stencil);
	clippingNode->addChild(_contentLabel,-1);

	addChild(clippingNode);
}

void DialogueLayer::showTextWithName(const string name, const string content, const string font, const int size, Color3B color)
{

}

void DialogueLayer::showTextWithNameAndHead(const string name, const string content, const string font, const int size, Color3B color)
{

}