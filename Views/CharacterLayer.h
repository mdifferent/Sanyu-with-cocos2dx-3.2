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
#include <list>
#include <string>

USING_NS_CC;
using namespace std;


static const char LEFT[] = "left";
static const char CENTER[] = "center";
static const char RIGHT[] = "right";

enum class CHAR_TRANSITION {
	DISSOLVE,
	MOVE_BETWEEN,
	MOVE_LEFT_BOUND,
	MOVE_RIGHT_BOUND,
	MOVE_BOTTOM_BOUND,
	MOVE_TOP_BOUND,
	NONE
};

class CharacterLayer : public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(CharacterLayer);
    
	void showCharacter(const string& name, list<string>& property, const string position = "center", CHAR_TRANSITION trans = CHAR_TRANSITION::DISSOLVE, float transTime = 0.5f);
	void showCharacter(const string& name, list<string>& property, float xpos, CHAR_TRANSITION trans = CHAR_TRANSITION::DISSOLVE, float transTime = 0.5f);
	void showCharacter(const string& name, list<string>& property, Vec2 posistion, CHAR_TRANSITION trans = CHAR_TRANSITION::DISSOLVE, float transTime = 0.5f);
	void removeCharacter(const string& name, CHAR_TRANSITION trans = CHAR_TRANSITION::DISSOLVE, float transTime = 0.5f);
    int getCharacterCount();
    
private:
	void displayOnPosition(Sprite *, string, CHAR_TRANSITION, float);
	
	map<string, string> _charsPos;		//character name - position name
	map<string, Vec2> _posDefine;		//position name - position in point

};

#endif
