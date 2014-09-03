//
//  HeadSprite.cpp
//  Sanyu
//
//  Created by wuhanming on 14-8-31.
//
//

#include "HeadSprite.h"
#include "ConstValues.h"
#include "Resources.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	#include "../proj.win32/WIN32Utils.h"
#endif 

bool HeadSprite::init()
{
    if (!Sprite::init())
        return false;

	char pName[MAX_FILE_PATH_LENGTH];
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	GBKToUTF(_name);
#endif
	sprintf(pName, HEAD_NAME, _name.c_str());
	CCLOG("%s", pName);
    this->setTexture(HEAD_NAME);
    Sprite *hp = Sprite::create(HP_BAR);
    Sprite *sp = Sprite::create(SP_BAR);
    if (!hp || !sp) {
        return false;
    }
    hp->setPosition(165,44);
    sp->setPosition(157,18);
    this->addChild(hp, 1, 11);
    this->addChild(sp, 1, 12);
    
    //Player HP bar
    ProgressTimer *hpBarTimer = ProgressTimer::create(hp);
    hpBarTimer->setType(ProgressTimer::Type::BAR);
    hpBarTimer->setMidpoint(Vec2(0,0));
    hpBarTimer->setBarChangeRate(Vec2(1,0));
    hpBarTimer->setPosition(170,70);
    addChild(hpBarTimer,1,"hpbar");
    
    //Player SP bar
    ProgressTimer *spBarTimer = ProgressTimer::create(sp);
    spBarTimer->setType(ProgressTimer::Type::BAR);
    spBarTimer->setMidpoint(Vec2(0,0));
    spBarTimer->setBarChangeRate(Vec2(1, 0));
    spBarTimer->setPosition(170,50);
    addChild(spBarTimer,1,"spbar");
    
    //Player Name
    Label* nameLabel = Label::createWithSystemFont(_name, NAME_FONT, NAME_FONT_SIZE);
    nameLabel->setPosition(165,80);
    this->addChild(nameLabel,2,"name");
    
    //Player HP number
    Label* hpLabel = Label::createWithSystemFont("0/0", NAME_FONT, HP_NUM_FONT_SIZE);
    hpLabel->setPosition(165,44);
    this->addChild(hpLabel,2,"hpnum");
    
    //Player SP number
    Label* spLabel = Label::createWithSystemFont("0/0", NAME_FONT, HP_NUM_FONT_SIZE);
    spLabel->setPosition(157,18);
    this->addChild(spLabel,2,"spnum");

    return true;
}

void HeadSprite::onValueModified(int value, int target)
{
	Label *label = NULL;
	ProgressTimer *bar = NULL;
	if (target == 1) {
		label = dynamic_cast<Label*>(this->getChildByName("hpnum"));
		bar = dynamic_cast<ProgressTimer*>(this->getChildByName("hpbar"));
	}
	else if (target == 2) {
		label = dynamic_cast<Label*>(this->getChildByName("spnum"));
		bar = dynamic_cast<ProgressTimer*>(this->getChildByName("spbar"));
	}
		
	string hpStr = label->getString();
	size_t pos = hpStr.find("/");
	int maxValue = stoi(hpStr.substr(pos + 1));
	int currentHp = stoi(hpStr.substr(0, pos));
	int newValue = currentHp + value;
	if (newValue < 0)
		newValue = 0;
	label->setString(to_string(newValue).append(hpStr.substr(pos)));

	float deltaPer = (abs(value) / maxValue)  * 100.0f;
    float per = bar->getPercentage();
	if (currentHp == 0)
		bar->runAction(ProgressFromTo::create(0.5f, per, 0));
	else if (value > 0)
		bar->runAction(ProgressFromTo::create(0.5f, per, per + deltaPer));
	else if (value < 0)
		bar->runAction(ProgressFromTo::create(0.5f, per, per - deltaPer));

}