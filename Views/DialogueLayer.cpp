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

	int textAreaMaxHeight = GlobalConfig::getInstance()->getTextAreaHeight();
	int textAreaMaxWidth = GlobalConfig::getInstance()->getTextAreaWidth();

	if (GlobalConfig::getInstance()->getFontPath().length() > 0) {
		TTFConfig ttf;
		ttf.fontFilePath = GlobalConfig::getInstance()->getFontPath();
		_contentLabel = Label::createWithTTF(ttf,"");
	}
	else {
		_contentLabel = Label::create();
		_contentLabel->setDimensions(textAreaMaxWidth, textAreaMaxHeight);
	}

	_contentLabel->setAnchorPoint(Vec2(0, 1));
	_contentLabel->setPosition(GlobalConfig::getInstance()->getTextLeftTop());

	return true;
}

void DialogueLayer::showText(const string content, const string font, const int size, Color3B color, bool skipFirstLine)
{
	_contentLabel->setString(content);
	_contentLabel->setSystemFontName(font);
	_contentLabel->setSystemFontSize(size);
	_contentLabel->setColor(color);
	
	displayDialogue(size, skipFirstLine);
}

void DialogueLayer::showTextWithName(const string name, const string content, const string font, const int size, Color3B color)
{
	showText(name + '\n' + content, font, size, color, true);
}

void DialogueLayer::showTextWithNameAndHead(const string name, const string content, const string font, const int size, Color3B color)
{

}

void DialogueLayer::displayDialogue(const int fontsize, bool skipFirstLine) {
	int textAreaMaxHeight = GlobalConfig::getInstance()->getTextAreaHeight();
	int textAreaMaxWidth = GlobalConfig::getInstance()->getTextAreaWidth();
	int charsPerLine = textAreaMaxWidth / fontsize;
	int lineCount = textAreaMaxHeight / charsPerLine + 1;
	int lineDisplayTime = charsPerLine / GlobalConfig::getInstance()->getTextSpeed() + 1;

	Node* stencil = Node::create();
	ClippingNode* clippingNode = ClippingNode::create(stencil);
	clippingNode->addChild(_contentLabel);
	addChild(clippingNode, 1, "clippernode");

	_status = DIALOGUE_STATUS::DISPLAYING;

	if (skipFirstLine) {
		auto clip = LayerColor::create(Color4B::BLACK, textAreaMaxWidth, fontsize);
		clip->setPosition(Vec2(GlobalConfig::getInstance()->getTextLeftTop().x - fontsize,
			GlobalConfig::getInstance()->getTextLeftTop().y - fontsize));
		stencil->addChild(clip, 0);
	}

	for (int i = 0; i < lineCount; i++) {
		if (skipFirstLine && i==0)
			continue;
		auto clip = LayerColor::create(Color4B::BLACK, fontsize, fontsize);
		float xpos = GlobalConfig::getInstance()->getTextLeftTop().x - fontsize;
		float ypos = GlobalConfig::getInstance()->getTextLeftTop().y - (i + 1)*fontsize;
		clip->setPosition(Vec2(xpos, ypos));
		stencil->addChild(clip, 0, i);
		float delayTime = lineDisplayTime * i;
		if (skipFirstLine)
			delayTime -= lineDisplayTime;
		clip->runAction(Sequence::create(DelayTime::create(delayTime),
			ScaleTo::create(lineDisplayTime, 2 * charsPerLine + 1, 1),
			CallFuncN::create(CC_CALLBACK_1(DialogueLayer::onSpeakFinished, this)), NULL));
	}
}

void DialogueLayer::onSpeakFinished(Node* sender) {
	auto node = dynamic_cast<ClippingNode*>(this->getChildByName("clippernode"));
	auto stencil = node->getStencil();
	if (stencil->getChildrenCount() == sender->getTag() + 1)
		_status = DIALOGUE_STATUS::NORMAL;
}