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
	this->setTexture(pName);

	Sprite *hp = Sprite::create(MONSTER_HP_BAR);
	ProgressTimer *hpBarTimer = ProgressTimer::create(hp);
	hpBarTimer->setType(ProgressTimer::Type::BAR);
	hpBarTimer->setMidpoint(Vec2(0, 0));
	hpBarTimer->setBarChangeRate(Vec2(1, 0));
	hpBarTimer->setPosition(getContentSize().width*0.5,	getContentSize().height);
	hpBarTimer->setOpacity(0);
	hpBarTimer->setPercentage(100.0);
	addChild(hpBarTimer, 1, "hpbar");

	//Damage number
	DigitSprite *digit = DigitSprite::create();
	digit->setPosition(getAnchorPointInPoints());
	addChild(digit, 3, "digit");
	digit->setOpacity(0);

	this->setCascadeOpacityEnabled(true);
	return true;
}

void MonsterHeadSprite::onHPModified(int deltaValue, float deltaPercent, bool isDead)
{
	ProgressTimer *bar = dynamic_cast<ProgressTimer*>(this->getChildByName("hpbar"));
	float currentPer = bar->getPercentage();

	if (deltaValue < 0) {
		DigitSprite *digit = (DigitSprite*)getChildByName("digit");
		digit->showDigit(abs(deltaValue));
		if (isDead) {
			if (currentPer - deltaPercent < 0)
				bar->setOpacity(255);
				bar->runAction(Sequence::create(ProgressFromTo::create(0.3f, currentPer, 0),
					FadeOut::create(0.3f), NULL));
		}
		else {
			bar->setOpacity(255);
			bar->runAction(Sequence::create(ProgressFromTo::create(0.3f, currentPer, currentPer - deltaPercent),
				FadeOut::create(0.3f), NULL));
		}
	}
	else {
		bar->setOpacity(255);
		bar->runAction(Sequence::create(ProgressFromTo::create(0.3f, currentPer, currentPer + deltaPercent),
			FadeOut::create(0.3f), NULL));
	}
}

float MonsterHeadSprite::getHpPercent()
{
	ProgressTimer *hpBarTimer = (ProgressTimer*)getChildByName("hpbar");
	return hpBarTimer->getPercentage();
}