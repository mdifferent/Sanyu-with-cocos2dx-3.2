//
//  ChoiceLayer.cpp
//  Sanyu
//
//  Created by wuhanming on 14-9-7.
//
//

#include "ChoiceLayer.h"

static const char BUTTON_BG[] = "";
bool ChoiceLayer::init()
{
    if (!Layer::init())
        return false;
    
    ControlButton *button0 = ControlButton::create();
    button0->setTag(0);
    button0->setBackgroundSprite(Scale9Sprite::create(BUTTON_BG));
    button0->addTargetWithActionForControlEvents(this,cccontrol_selector(ChoiceLayer::choicesCallback), Control::EventType::TOUCH_UP_INSIDE);
    ControlButton *button1 = ControlButton::create();
    button1->setTag(1);
    button1->setBackgroundSprite(Scale9Sprite::create(BUTTON_BG));
    button1->addTargetWithActionForControlEvents(this,cccontrol_selector(ChoiceLayer::choicesCallback), Control::EventType::TOUCH_UP_INSIDE);
    
    addChild(button0,0,0);
    addChild(button1,0,1);
    return true;
}

void ChoiceLayer::setChoices(vector<string> choices)
{
    size_t btnCount = getChildrenCount();
    size_t choiceCount = choices.size();
    for (int i=0; i<btnCount; i++) {
        ControlButton *btn = (ControlButton*)getChildByTag(i);
        btn->setTitleForState(choices.at(i), Control::State::NORMAL);
    }
    if (choiceCount > btnCount) {
        for (int i = btnCount; i<choices.size(); i++) {
            ControlButton *button0 = ControlButton::create();
            button0->setTag(i);
            button0->setBackgroundSprite(Scale9Sprite::create(BUTTON_BG));
            button0->addTargetWithActionForControlEvents(this,cccontrol_selector(ChoiceLayer::choicesCallback), Control::EventType::TOUCH_UP_INSIDE);
            button0->setTitleForState(choices.at(i), Control::State::NORMAL);
        }
    }
}

void ChoiceLayer::choicesCallback(Ref* sender, Control::EventType event)
{
    ControlButton *pressedBtn = (ControlButton*)sender;
    _selectedTag = pressedBtn->getTag();
    
}