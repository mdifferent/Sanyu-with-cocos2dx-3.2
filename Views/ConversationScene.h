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

class ConversationScene : public Scene
{
public:
    virtual bool init();
    static ConversationScene* create();
    
    void changeBackground(const string name, Action action);
    void changeCharacter(int position, const string name);
    void speaking(const string name, const string text);
    void showChoice(map<int,string> choices);
private:
    Layer* _bgLayer;
    Layer* _speakLayer;
    Layer* _charLayer;
    Layer* _choiceBtnLayer;
    Layer* _textLayer;
};

#endif
