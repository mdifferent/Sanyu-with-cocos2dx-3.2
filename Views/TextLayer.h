//
//  TextLayer.h
//  Sanyu
//
//  Created by wuhanming on 14-9-7.
//
//

#ifndef __Sanyu__TextLayer__
#define __Sanyu__TextLayer__

#include "cocos2d.h"
#include <string>

USING_NS_CC;
using namespace std;

class TextLayer : public Layer
{
public:
    bool init();
    CREATE_FUNC(TextLayer);
    
    void showText(const string& content);
};

#endif /* defined(__Sanyu__TextLayer__) */
