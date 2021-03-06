//
//  ConversationScene.h
//  Sanyu
//
//  Created by wuhanming on 14-8-31.
//
//

#ifndef Sanyu_ConversationScene_h
#define Sanyu_ConversationScene_h

#include "cocos2d.h"
#include <string>
USING_NS_CC;
using namespace std;

class BackgroundLayer;
class CharacterLayer;
class DialogueLayer;
class TextLayer;
class ChoiceLayer;

enum class CONVER_STATUS {
	DIALOGUE,
	MENU
};

class ConversationScene : public Scene
{
public:
    virtual bool init();
    CREATE_FUNC(ConversationScene);
    
    void changeBackground(const string name, ActionInterval *action);
    void changeCharacter(int position, const string name);
	void speaking(string name, string text, const bool showHead = false);
    void showChoice(map<int,string> choices);
    void switchDialogueWindow();

	bool onTouchBegan(Touch *touch, Event *pEvent);
	CC_SYNTHESIZE(CONVER_STATUS, _status, Status);
private:
    BackgroundLayer* _bgLayer;
    CharacterLayer* _charLayer;
    DialogueLayer* _speakLayer;
    TextLayer* _textLayer;
    ChoiceLayer* _choiceBtnLayer;
};

#endif
