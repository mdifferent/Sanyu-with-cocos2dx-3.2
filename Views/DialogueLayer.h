//
//  DialogueLayer.h
//  Sanyu
//
//  Created by wuhanming on 14-9-7.
//
//

#ifndef __Sanyu__DialogueLayer__
#define __Sanyu__DialogueLayer__

#include "cocos2d.h"
#include <string>
#include "CommonUtils.h"
#include "../DataModel/GlobalConfig.h"

USING_NS_CC;
using namespace std;

class DialogueLayer : public Layer
{
public:
    DialogueLayer(const string bg);

	CREATE_FUNC_WITH_STRING(DialogueLayer, bg);
    bool init();
    
	void showText(const string content, const string font = "", const int size = GlobalConfig::getInstance()->getFontSize(), Color3B color = Color3B::BLACK);
	void showTextWithName(const string name, const string content, const string font = "", const int size = GlobalConfig::getInstance()->getFontSize(), Color3B color = Color3B::BLACK);
	void showTextWithNameAndHead(const string name, const string content, const string font = "", const int size = GlobalConfig::getInstance()->getFontSize(), Color3B color = Color3B::BLACK);

private:
    string _bg;
    string _name;
    string _content;

	Label *_contentLabel;

};

#endif /* defined(__Sanyu__DialogueLayer__) */
