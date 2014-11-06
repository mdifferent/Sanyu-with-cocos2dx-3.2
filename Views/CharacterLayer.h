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

enum class CHAR_POSITION {
	LEFT,
	CENTER,
	RIGHT
};

enum class CHAR_TRANSITION {
	DISSOLVE,
	MOVE_LEFT,
	MOVE_RIGHT,
	MOVE_BOTTOM,
	MOVE_TOP,
};

class CharacterLayer : public Layer
{
public:
    virtual bool init();
    CREATE_FUNC(CharacterLayer);
    
	void showCharacter(const string& name, const CHAR_POSITION position, Vector<string> property = NULL, CHAR_TRANSITION trans = CHAR_TRANSITION::DISSOLVE);
	void showCharacter(const string& name, Vec2 posistion, Vector<string> *property = NULL, CHAR_TRANSITION trans = CHAR_TRANSITION::DISSOLVE);
	void showCharacter(const string& name, float xpos, Vector<string> *property = NULL, CHAR_TRANSITION trans = CHAR_TRANSITION::DISSOLVE);
	void removeCharacter(const string& name, CHAR_TRANSITION trans = CHAR_TRANSITION::DISSOLVE);
    int getCharacterCount();

	CC_SYNTHESIZE(float, _leftPosX, LeftPosX);
	CC_SYNTHESIZE(float, _centerPosX, CenterPosX);
	CC_SYNTHESIZE(float, _rightPosX, RightPosX);
    
private:
    map<string, Vec2> _characters;

	Sprite *_left;
	Sprite *_center;
	Sprite *_right;
};

#endif
