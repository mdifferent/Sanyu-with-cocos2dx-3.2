//
//  HeadSprite.h
//  Sanyu
//
//  Created by wuhanming on 14-8-31.
//
//

#ifndef Sanyu_HeadSprite_h
#define Sanyu_HeadSprite_h

#include "cocos2d.h"
#include <string>
#include "CommonUtils.h"

USING_NS_CC;
using namespace std;

class HeadSprite : public Sprite
{
public:
    HeadSprite(const string name) {_name = name;}
    
    virtual bool init();
	CREATE_FUNC_WITH_STRING(HeadSprite, name);

	virtual void onValueModified(int value, int type);	//type 1: HP, 2:SP
protected:
    string _name;
};

#endif
