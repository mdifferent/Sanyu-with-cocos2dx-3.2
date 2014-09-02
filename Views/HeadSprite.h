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
    //static HeadSprite* createWithPlayerName(const string name);
	CREATE_FUNC_WITH_STRING(HeadSprite, name);

    void onHPModified(int value,float percentage);
    void onSPModified(int value,float percentage);
private:
    string _name;
};

#endif
