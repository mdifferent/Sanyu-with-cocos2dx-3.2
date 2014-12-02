//
//  ChoiceLayer.cpp
//  Sanyu
//
//  Created by wuhanming on 14-9-7.
//
//

#include "ChoiceLayer.h"
#include "Resources.h"
#include "DataModel\GlobalConfig.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
#include "../proj.win32/WIN32Utils.h"
#endif 

bool ChoiceLayer::init()
{
    if (!Layer::init())
        return false;
    
	auto button0 = createButton(0);
	auto button1 = createButton(1);

    return true;
}

ControlButton* ChoiceLayer::createButton(int idx, string title)
{
	string choiceBtnBg = GlobalConfig::getInstance()->getChoiceMenuBgPath();
	Size screenSize = Director::getInstance()->getVisibleSize();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	GBKToUTF(title);
#endif 
	auto button = ControlButton::create(title, 
		GlobalConfig::getInstance()->getChoiceMenuFontName(), 
		GlobalConfig::getInstance()->getChoiceMenuFontSize());
	button->addTargetWithActionForControlEvents(this, cccontrol_selector(ChoiceLayer::choicesCallback), Control::EventType::TOUCH_UP_INSIDE);
	button->setBackgroundSpriteForState(Scale9Sprite::create(choiceBtnBg), Control::State::NORMAL);
	button->setPreferredSize(Size(screenSize.width*0.6, GlobalConfig::getInstance()->getChoiceMenuFontSize() + 10));
	button->setOpacity(0);
	button->setTitleColorForState(GlobalConfig::getInstance()->getChoiceMenuFontColor(), Control::State::NORMAL);
	addChild(button, 0, idx);
	return button;
}

void ChoiceLayer::setChoices(vector<string> choices)
{
    size_t btnCount = getChildrenCount();
    size_t choiceCount = choices.size();
	float btnHeight = GlobalConfig::getInstance()->getChoiceMenuFontSize() + 10;
	float spaceBetweenBtn = btnHeight;
	float deltaUnit = btnHeight + spaceBetweenBtn;
	float initHeight = choiceCount % 2 == 0 
		? spaceBetweenBtn*0.5 + (choiceCount / 2 - 1)*deltaUnit
		: spaceBetweenBtn + btnHeight*0.5 + ((choiceCount - 1) / 2 - 1)*deltaUnit;

	if (choiceCount > btnCount)
		for (int i = btnCount; i<choices.size(); i++) {
			auto btn = createButton(i, choices[i]);
		}
	for (int i = 0; i < choiceCount; i++) {
        auto btn = (ControlButton*)getChildByTag(i);
		string choice = choices.at(i);
		btn->setPosition(Vec2(0, initHeight - i*deltaUnit));
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
		GBKToUTF(choice);
#endif 
        btn->setTitleForState(choice, Control::State::NORMAL);
		btn->setOpacity(255);
    }
}

void ChoiceLayer::choicesCallback(Ref* sender, Control::EventType event)
{
    ControlButton *pressedBtn = (ControlButton*)sender;
    _selectedTag = pressedBtn->getTag();
	CCLOG("Select tag : %d", _selectedTag);
	for (auto child : getChildren())
		child->setOpacity(0);
}