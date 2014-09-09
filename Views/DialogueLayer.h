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

USING_NS_CC;
using namespace std;

class DialogueLayer : public Layer
{
public:
    DialogueLayer(const string bg);
    bool init();
    CREATE_FUNC_WITH_STRING(DialogueLayer, bg);
    
    void showText(const string content);
    void showTextWithName(const string name, const string content);
    void showTextWithNameAndHead(const string name, const string content);
private:
    string _bg;
    string _name;
    string _content;
};

#endif /* defined(__Sanyu__DialogueLayer__) */
