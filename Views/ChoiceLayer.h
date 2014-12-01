//
//  ChoiceLayer.h
//  Sanyu
//
//  Created by wuhanming on 14-9-7.
//
//

#ifndef __Sanyu__ChoiceLayer__
#define __Sanyu__ChoiceLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <vector>
#include <string>

USING_NS_CC;
USING_NS_CC_EXT;
using namespace std;

class ChoiceLayer : public Layer
{
public:
    bool init();
    CREATE_FUNC(ChoiceLayer);
    
    void setChoices(vector<string> choices);
    void choicesCallback(Ref* sender, Control::EventType event);
    int getRecentSelectedResult() const {return _selectedTag;}
private:
	ControlButton* createButton(int idx, string title = "");
    int _selectedTag;
};

#endif /* defined(__Sanyu__ChoiceLayer__) */
