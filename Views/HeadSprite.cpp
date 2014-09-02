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

/*
HeadSprite* HeadSprite::createWithPlayerName(const string name)
{
    HeadSprite *sprite = new HeadSprite(name);
    if (sprite && sprite->init()) {
        sprite->autorelease();
        return sprite;
    }
    else {
        CC_SAFE_DELETE(sprite);
        return NULL;
    }
}*/

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
    addChild(hpBarTimer,1,1);
    
    //Player SP bar
    ProgressTimer *spBarTimer = ProgressTimer::create(sp);
    spBarTimer->setType(ProgressTimer::Type::BAR);
    spBarTimer->setMidpoint(Vec2(0,0));
    spBarTimer->setBarChangeRate(Vec2(1, 0));
    spBarTimer->setPosition(170,50);
    addChild(spBarTimer,1,2);
    
    //Player Name
    Label* nameLabel = Label::createWithSystemFont(_name, NAME_FONT, NAME_FONT_SIZE);
    nameLabel->setPosition(165,80);
    //nameLabel->setOpacity(0);
    this->addChild(nameLabel,2,3);
    
    //Player HP number
    Label* hpLabel = Label::createWithSystemFont("0/0", NAME_FONT, HP_NUM_FONT_SIZE);
    hpLabel->setPosition(165,44);
    //hpLabel->setOpacity(0);
    this->addChild(hpLabel,2,4);
    
    //Player SP number
    Label* spLabel = Label::createWithSystemFont("0/0", NAME_FONT, HP_NUM_FONT_SIZE);
    spLabel->setPosition(157,18);
    //spLabel->setOpacity(0);
    this->addChild(spLabel,2,5);

    return true;
}

void HeadSprite::onHPModified(int value,float percentage)
{
    ProgressTimer *hpBar = dynamic_cast<ProgressTimer*>(this->getChildByTag(4));
    float per = hpBar->getPercentage();
    hpBar->runAction(ProgressFromTo::create(0.5f,per,per+percentage));
    
}

void HeadSprite::onSPModified(int value, float percentage)
{
    
}