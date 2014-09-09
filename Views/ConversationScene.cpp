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

bool ConversationScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    
    string background = "";
    string dialogueWindowBg = "";
    
    _bgLayer = BackgroundLayer::create(background);
    _charLayer = CharacterLayer::create();
    _speakLayer = DialogueLayer::create(dialogueWindowBg);
    
    return true;
}

void ConversationScene::changeBackground(const string name, ActionInterval *action)
{
    _speakLayer->runAction(FadeOut::create(0.5f));
    _charLayer->runAction(FadeOut::create(0.5f));
    _bgLayer->runAction(action);
}

void changeBackground(const string& name, ActionInterval *action)
{
    
}
void changeCharacter(int position, const string& name)
{
    
}
void speaking(const string& name, const string& text)
{
    
}
void showChoice(map<int,string> choices)
{
    
}

void switchDialogueWindow()
{
    
}