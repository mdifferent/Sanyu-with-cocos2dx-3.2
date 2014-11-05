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

enum class DIALOGUE_STATUS {
	NORMAL,
	DISPLAYING
};

class DialogueLayer : public Layer
{
public:
    DialogueLayer(const string bg);

	CREATE_FUNC_WITH_STRING(DialogueLayer, bg);
    bool init();
    
	void showText(const string content, const string font = "", const int size = GlobalConfig::getInstance()->getFontSize(), Color3B color = Color3B::BLACK, bool skipFirstLine = false);
	void showTextWithName(const string name, const string content, const string font = "", const int size = GlobalConfig::getInstance()->getFontSize(), Color3B color = Color3B::BLACK);
	void showTextWithNameAndHead(const string name, const string content, const string font = "", const int size = GlobalConfig::getInstance()->getFontSize(), Color3B color = Color3B::BLACK);

	void onSpeakFinished(Node* sender);

private:
	void displayDialogue(const int fontsize, bool skipFirstLine);

    string _bg;
    string _name;
    string _content;

	Label *_contentLabel;
	DIALOGUE_STATUS _status;

};

#endif /* defined(__Sanyu__DialogueLayer__) */
