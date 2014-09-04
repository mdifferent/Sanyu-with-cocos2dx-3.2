#include "MonsterHeadSprite.h"
#include "DigitSprite.h"
#include "ConstValues.h"
#include "Resources.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
	#include "../proj.win32/WIN32Utils.h"
#endif 

bool MonsterHeadSprite::init()
{
	if (!Sprite::init())
		return false;

	char pName[MAX_FILE_PATH_LENGTH];
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	GBKToUTF(_name);
#endif
	sprintf(pName, MONSTER_HEAD_NAME, _name.c_str());
	CCLOG("%s", pName);
	this->setTexture(MONSTER_HEAD_NAME);

	Sprite *hp = Sprite::create(MONSTER_HP_BAR);
	ProgressTimer *hpBarTimer = ProgressTimer::create(hp);
	hpBarTimer->setType(ProgressTimer::Type::BAR);
	hpBarTimer->setMidpoint(Vec2(0, 0));
	hpBarTimer->setBarChangeRate(Vec2(1, 0));
	hpBarTimer->setPosition(getPositionX(),	getContentSize().height);
	hpBarTimer->setOpacity(0);
	addChild(hpBarTimer, 1, "hpbar");

	//Damage number
	DigitSprite *digit = DigitSprite::create();
	digit->setPosition(getPosition());
	addChild(digit, 3, "digit");
	return true;
}

void MonsterHeadSprite::onHPModified(int deltaValue, float deltaPercent)
{
	ProgressTimer *bar = dynamic_cast<ProgressTimer*>(this->getChildByName("hpbar"));
	float currentPer = bar->getPercentage();
	if (deltaValue > 0)
		bar->runAction(Sequence::create(FadeIn::create(0.3f),
		CCProgressFromTo::create(0.3f, currentPer, currentPer + deltaPercent), 
		CCFadeOut::create(0.3f), NULL));
	else
		bar->runAction(Sequence::create(FadeIn::create(0.3f),
		ProgressFromTo::create(0.3f, currentPer, currentPer - deltaPercent), 
		FadeOut::create(0.3f), NULL));

	//Show damage number
	if (deltaValue < 0) {
		DigitSprite *digit = (DigitSprite*)getChildByName("digit");
		digit->showDigit(abs(deltaValue));
	}
}