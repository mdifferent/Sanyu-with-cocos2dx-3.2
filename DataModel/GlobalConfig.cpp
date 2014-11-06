#include "GlobalConfig.h"

GlobalConfig* GlobalConfig::_sharedInstance = new GlobalConfig();
GlobalConfig* GlobalConfig::getInstance()
{
	if (_sharedInstance == NULL)
		_sharedInstance = new GlobalConfig();

	//TEST DATA
	_sharedInstance->_fontPath = "";
	_sharedInstance->_fontSize = 24;
	_sharedInstance->_textDisplaySpeed = 20;
	_sharedInstance->_font = "Arial";
	_sharedInstance->_textLeftTop = Vec2(50,140);
	_sharedInstance->_textRightBottom = Vec2(750,20);
	_sharedInstance->_dialogueBackPath = "images/dialogue/text1.png";

	return _sharedInstance;
}