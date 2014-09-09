//
//  DialogueLayer.h
//  Sanyu
//
//  Created by wuhanming on 14-9-6.
//
//

#ifndef Sanyu_DialogueLayer_h
#define Sanyu_DialogueLayer_h

#include "cocos2d.h"
#include <map>
#include <string>

USING_NS_CC;
using namespace std;

class CharacterLayer : public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(CharacterLayer);
    
    void setCharacter(const string& name, const int position, Vector<string> *property = NULL, ActionInterval *action = NULL);
    void setCharacter(const string& name, Vec2 posistion, Vector<string> *property = NULL, ActionInterval *action = NULL);
    void setCharacter(const string& name, float xpos, Vector<string> *property = NULL, ActionInterval *action = NULL);
    void removeCharacter(const string& name, ActionInterval *action = NULL );
    int getCharacterCount();
    
private:
    map<string, Vec2> _characters;
};

#endif
