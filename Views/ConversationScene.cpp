//
//  ConversationScene.cpp
//  Sanyu
//
//  Created by wuhanming on 14-9-6.
//
//

#include "ConversationScene.h"
#include "CharacterLayer.h"
#include "DialogueLayer.h"
#include "BackgroundLayer.h"
#include "..\DataModel\GlobalConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
#include "../proj.win32/WIN32Utils.h"
#endif 

bool ConversationScene::init()
{
    if (!Scene::init()) {
        return false;
    }

	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = CC_CALLBACK_2(ConversationScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    string background = "images/bk.jpg";
	string dialogueWindowBg = GlobalConfig::getInstance()->getDialogueBackPath();
    
    _bgLayer = BackgroundLayer::create(background);
    _charLayer = CharacterLayer::create();
    _speakLayer = DialogueLayer::create(dialogueWindowBg);

	addChild(_bgLayer, 0);
	addChild(_speakLayer, 2);
    
    return true;
}

bool ConversationScene::onTouchBegan(Touch *touch, Event *pEvent)
{
	switch (_status)
	{
	case CONVER_STATUS::MENU:
	case CONVER_STATUS::DIALOGUE:
		_speakLayer->onClicked();
		break;
	default:
		break;
	}
	return false;
}

void ConversationScene::changeBackground(const string name, ActionInterval *action)
{
    _speakLayer->runAction(FadeOut::create(0.5f));
    _charLayer->runAction(FadeOut::create(0.5f));
	_bgLayer->switchBg(name, BG_TRANSITION_TYPE::FADE);
}

void ConversationScene::speaking(string name, string text, const bool showHead)
{
	_status = CONVER_STATUS::DIALOGUE;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	if (name.length() > 0)
		GBKToUTF(name);
	GBKToUTF(text);
#endif
	if (name.length() == 0)
		_speakLayer->showText(text);
	else if (showHead)
		_speakLayer->showTextWithNameAndHead(name, text);
	else
		_speakLayer->showTextWithName(name, text);
}

void ConversationScene::changeCharacter(int position, const string name)
{

}

void ConversationScene::showChoice(map<int, string> choices)
{
	_status = CONVER_STATUS::MENU;
}

void ConversationScene::switchDialogueWindow()
{
	if (_speakLayer->getOpacity() == 0)
		_speakLayer->setOpacity(255);
	else
		_speakLayer->setOpacity(0);
}