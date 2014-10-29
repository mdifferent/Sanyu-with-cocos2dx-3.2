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
#include "DataModel\GlobalConfig.h"

bool ConversationScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    
    string background = "images/bk.png";
	string dialogueWindowBg = "images/dialogue/text1.png";
    
    _bgLayer = BackgroundLayer::create(background);
    _charLayer = CharacterLayer::create();
    _speakLayer = DialogueLayer::create(dialogueWindowBg);
    
    return true;
}

void ConversationScene::changeBackground(const string name, ActionInterval *action)
{
    _speakLayer->runAction(FadeOut::create(0.5f));
    _charLayer->runAction(FadeOut::create(0.5f));
	_bgLayer->switchBg(name, BG_TRANSITION_TYPE::FADE);
}

void ConversationScene::speaking(const string name, const string text, const bool showHead)
{
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
    
}

void ConversationScene::switchDialogueWindow()
{
    
}