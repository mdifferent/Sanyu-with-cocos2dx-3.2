#ifndef __DIGIT_SPRITE_H__
#define __DIGIT_SPRITE_H__

#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

class DigitSprite : public Node
{
public:
	bool init();
	CREATE_FUNC(DigitSprite);

	void showDigit(int value);
	
private:
	void extendSpriteBatch(int count);
};
#endif