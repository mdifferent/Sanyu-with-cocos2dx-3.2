#ifndef __GLOBAL_CONFIG_H__
#define __GLOBAL_CONFIG_H__

#include <string>
#include "cocos2d.h"

using namespace std;
USING_NS_CC;

class GlobalConfig
{
public:
	static GlobalConfig* getInstance();

	float	getTextAreaWidth() const { return _textRightBottom.x - _textLeftTop.x; }
	float	getTextAreaHeight() const { return _textLeftTop.y - _textRightBottom.y; }

	CC_SYNTHESIZE(int, _textDisplaySpeed, TextSpeed);	//How many characters displayed for one seconds

	//Dialogue display font
	CC_SYNTHESIZE(string, _fontPath, FontPath);			//Read from ttf
	CC_SYNTHESIZE(string, _font, FontName);				//Use system font
	CC_SYNTHESIZE(int, _fontSize, FontSize);			//Use system font 

	//Dialogue paragraph left-top corner position
	CC_SYNTHESIZE(Vec2, _textLeftTop, TextLeftTop);
	CC_SYNTHESIZE(Vec2, _textRightBottom, TextRightBottom);

private:
	GlobalConfig() {}
	~GlobalConfig() {}

	static GlobalConfig* _sharedInstance;
};

#endif