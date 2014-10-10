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
	HeadSprite(const string name, const int maxHp, const int currentHp,	const int maxSp, const int currentSp)
		: _name(name), _maxHp(maxHp), _currentHp(currentHp), _maxSp(maxSp), _currentSp(currentSp) {}
    
    virtual bool init();
	static HeadSprite* createWithNameAndValues(const string name, const int maxHp, const int currentHp, const int maxSp, const int currentSp);

	virtual void onValueModified(int value, int type);	//type 1: HP, 2:SP
	void hide(float duration);
	void show(float duration);
protected:
    string _name;
	int _maxHp;
	int _currentHp;
	int _maxSp;
	int _currentSp;
};

#endif
