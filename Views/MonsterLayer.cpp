#include "MonsterLayer.h"
#include "Resources.h"
#include "ConstValues.h"
#include "MonsterHeadSprite.h"

bool MonsterLayer::init()
{
	if (!Layer::init())
		return false;

	int playerCount = _heads.size();
	float screenWidth = Director::getInstance()->getVisibleSize().width;
	float screenHeight = Director::getInstance()->getVisibleSize().height;

	initTouchListener();
	for each (pair<int,string> var in _heads) {
		MonsterHeadSprite *sprite = MonsterHeadSprite::create(var.second);
		float xpos = screenWidth*0.5 + (var.first - playerCount*0.5 + 0.5)*screenWidth;
		float ypos = screenHeight*0.6;
		sprite->setPosition(xpos, ypos);
		sprite->setOpacity(0);
		addChild(sprite, 0, var.first);
	}

	//Magic matrix tag
	Sprite *magicTag = Sprite::create(MAGIC_BTN_PATH);
	magicTag->setOpacity(0);
	magicTag->setPosition(Vec2(750, 550));
	addChild(magicTag, 1, "magicTag");

	Sprite *magicPointer = Sprite::create(MAGIC_UNAVA_PATH);
	magicPointer->setOpacity(0);
	magicPointer->setPosition(Vec2(750, 550));
	addChild(magicPointer, 2, "magicPointer");
	Director::getInstance()->getTextureCache()->addImage(MAGIC_AVA_PATH);
	Director::getInstance()->getTextureCache()->addImage(MAGIC_UNAVA_PATH);

	ProgressTimer *longHPBar = ProgressTimer::create(Sprite::create(LONG_HP_BAR));
	longHPBar->setType(ProgressTimer::Type::BAR);
	longHPBar->setMidpoint(Vec2(0, 0));
	longHPBar->setPercentage(100);
	longHPBar->setBarChangeRate(Vec2(1, 0));
	longHPBar->setOpacity(0);
	longHPBar->setPosition(Vec2(screenWidth*0.5, screenHeight*0.3));
	addChild(longHPBar, 2, "hpbar");

	Sprite *timeBarEmpty = Sprite::create(TIME_BAR_EMPTY);
	timeBarEmpty->setOpacity(0);
	timeBarEmpty->setPosition(Vec2(screenWidth*0.5, screenHeight*0.7));
	addChild(timeBarEmpty, 2, "timebar_empty");

	ProgressTimer *timeBarFull = ProgressTimer::create(Sprite::create(TIME_BAR_FULL));
	timeBarFull->setType(ProgressTimer::Type::BAR);
	timeBarFull->setMidpoint(Vec2(0, 0));
	timeBarFull->setPercentage(100);
	timeBarFull->setBarChangeRate(Vec2(1, 0));
	timeBarFull->setOpacity(0);
	timeBarFull->setPosition(Vec2(screenWidth*0.5, screenHeight*0.7));
	addChild(timeBarFull, 2, "timebar_full");

	SpriteFrameCache *cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile(BUBBLE_PLIST_PATH, BUBBLE_TEXTURE_PATH);

	return true;
}

bool MonsterLayer::initTouchListener()
{
	auto listener1 = EventListenerTouchOneByOne::create();
	listener1->setSwallowTouches(true);
	listener1->onTouchBegan = [this](Touch* touch, Event* event) {
		if (_status == SLEEP && !_isMagicMatrixAvailable)
			return false;
		else if (_isMagicMatrixAvailable) {
			Point touchPos = touch->getLocation();
			Rect tagRect = getChildByName("magicTag")->getBoundingBox();
			if (tagRect.containsPoint(touchPos)) {
				Sprite* magicPointer = (Sprite*)getChildByName("magicPointer");
				magicPointer->setScale(1.0f);
				magicPointer->runAction(CCFadeIn::create(0.1f));
				setStatus(SPECIAL_ATTACK_PRE);
				return true;
			}
		}
		if (_status == WAIT_TARGET) {
			if (touch->getLocationInView().y < PLAYER_HEAD_HEIGHT) {
				this->setStatus(SLEEP);
				return false;
			}
			else {
				for each (pair<int, string> var in _heads) {
					auto monster = getChildByTag(var.first);
					if (monster->getBoundingBox().containsPoint(touch->getLocationInView())) {
						MoveBy *pMoveAction = MoveBy::create(0.05f, Vec2(10, 10));
						monster->runAction(Repeat::create(Sequence::createWithTwoActions(pMoveAction, pMoveAction->reverse()), 4));
						//this->getChildByTag(var.first)->runAction(MoveTo::create(0.05f, m_originalPos.at(var.first)));
						this->setStatus(TARGET_SELECTED);
						CCLOG("Target is %d", var.first);
						_target = var.first;
						return false;
					}
				}
			}
		}
		else if (_status == SPECIAL_ATTACK) {
			for each (Sprite* bubble in _bubbles) {
				Rect bubbleRect = bubble->getBoundingBox();
				if (bubbleRect.containsPoint(touch->getLocation())) {
					bubble->stopAllActions();
					SpriteFrameCache *cache = SpriteFrameCache::getInstance();
					Animation *breakAnimation = Animation::create();
					breakAnimation->addSpriteFrame(cache->getSpriteFrameByName("paopao_m6"));
					breakAnimation->addSpriteFrame(cache->getSpriteFrameByName("paopao_m7"));
					breakAnimation->addSpriteFrame(cache->getSpriteFrameByName("paopao_m8"));
					breakAnimation->addSpriteFrame(cache->getSpriteFrameByName("paopao_m9"));
					breakAnimation->addSpriteFrame(cache->getSpriteFrameByName("paopao_m10"));
					breakAnimation->setDelayPerUnit(0.1f);
					breakAnimation->setLoops(1);
					breakAnimation->setRestoreOriginalFrame(false);
					bubble->runAction(Sequence::createWithTwoActions(Animate::create(breakAnimation),
						FadeOut::create(0.1f)));
					_BubbleHit++;
					removeChild(bubble, true);
					ProgressTimer *longHPBar = (ProgressTimer*)getChildByName("hpbar");
					float currentPercent = longHPBar->getPercentage();
					longHPBar->runAction(ProgressFromTo::create(0.1f, currentPercent, currentPercent - 10.0));
					break;
				}
			}
		}
		return false;
	};
	listener1->onTouchMoved = [this](Touch* touch, Event* event) {
		if (_status == SPECIAL_ATTACK_PRE) {
			if (touch->getLocation() == touch->getPreviousLocation())
				return;
			Sprite* magicPointer = (Sprite*)getChildByName("magicPointer");
			magicPointer->setPosition(touch->getLocation());
			for each (pair<int,string> var in _heads) {
				MonsterHeadSprite *monster = (MonsterHeadSprite*)getChildByTag(var.first);
				if (monster->getBoundingBox().containsPoint(touch->getLocation())) {
					if (monster->getHpPercent() > 0.3)
						continue;
					else {
						magicPointer->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey(MAGIC_AVA));
						magicPointer->runAction(RepeatForever::create(RotateBy::create(0.5, 90.0)));
						return;
					}
				}
			}
			magicPointer->cleanup();
			magicPointer->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey(MAGIC_UNAVA));
		}
	};
	listener1->onTouchEnded = [this](Touch* touch, Event* event) {
		if (_status == SPECIAL_ATTACK_PRE) {
			Sprite* magicPointer = (Sprite*)getChildByName("magicPointer");
			magicPointer->setPosition(touch->getLocation());
			for each (pair<int, string> var in _heads) {
				MonsterHeadSprite *monster = (MonsterHeadSprite*)getChildByTag(var.first);
				if (monster->getBoundingBox().containsPoint(touch->getLocation())) {
					if (monster->getHpPercent() > 0.3)
						continue;
					else {
						magicPointer->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey(MAGIC_AVA));
						initSpecialAttack(var.first);
						CCLOG("Target is %d", var.first);
						_target = var.first;
						setStatus(SPECIAL_ATTACK);
						return;
					}
				}
			}
			magicPointer->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey(MAGIC_UNAVA));
			magicPointer->runAction(Sequence::create(
				Spawn::create(MoveTo::create(0.2f, Vec2(750, 550)), ScaleTo::create(0.2f, 0.5), NULL),
				FadeOut::create(0.1f), NULL));
			this->setStatus(WAIT_TARGET);
		}
	};
	return true;
}

MonsterLayer* MonsterLayer::createWithNames(const map<int, string>* names)
{
	MonsterLayer *layer = new MonsterLayer(names);
	if (layer && layer->init()) {
		layer->autorelease();
		return layer;
	}
	else {
		CC_SAFE_DELETE(layer);
		return NULL;
	}
}

void MonsterLayer::onMagicMatrixAvailable()
{
	_isMagicMatrixAvailable = true;
	auto magicTag = getChildByName("magicTag");
	if (magicTag->getOpacity() == 0)
		magicTag->runAction(FadeIn::create(0.1f));
}

void MonsterLayer::onMagicMatrixUnavailable()
{
	_isMagicMatrixAvailable = false;
	auto magicTag = getChildByName("magicTag");
	if (magicTag->getOpacity() > 0)
		magicTag->runAction(FadeOut::create(0.1f));
}


void MonsterLayer::onAttacked(int target, int deltaValue, float deltaPercent, bool isDead) {
	MonsterHeadSprite *monster = dynamic_cast<MonsterHeadSprite*>(this->getChildByTag(target));
	monster->onHPModified(deltaValue, deltaPercent, isDead);
	if (isDead) {
		monster->runAction(FadeOut::create(0.5f));
		removeChildByTag(target);
		_heads.erase(target);
	}
}

void MonsterLayer::initSpecialAttack(int monsterNo)
{
	auto magicPointer = getChildByName("magicPointer");
	magicPointer->cleanup();
	magicPointer->runAction(FadeOut::create(0.2f));
	magicPointer->setPosition(Vec2(750, 550));

	ProgressTimer *longHPBar = (ProgressTimer*)getChildByName("hpbar");
	ProgressTimer *timeBarFull = (ProgressTimer*)getChildByName("timebar_full");
	auto timeBarEmpty = getChildByName("timebar_empty");
	timeBarFull->setPercentage(100.0f);
	MonsterHeadSprite *monster = (MonsterHeadSprite*)getChildByTag(monsterNo);

	int monsterCount = _heads.size();
	for (int i = 0; i < monsterCount; i++) {
		if (i != monsterNo)
			getChildByTag(i)->runAction(FadeOut::create(0.1f));
	}
	float screenWidth = Director::getInstance()->getVisibleSize().width;
	float screenHeight = Director::getInstance()->getVisibleSize().height;
	monster->runAction(MoveTo::create(0.5f, Vec2(screenWidth*0.5, screenHeight*0.5)));
	timeBarEmpty->runAction(FadeIn::create(0.1f));
	timeBarFull->runAction(FadeIn::create(0.1f));
	longHPBar->runAction(FadeIn::create(0.1f));
	longHPBar->runAction(ProgressFromTo::create(SPECIAL_ATTACK_DURATION, 100.0, 0.0));

	Size monsterSize = monster->getContentSize();
	Point middlePoint = Vec2(screenWidth / 2, screenHeight / 2);
	float bottomBorder = middlePoint.y - monsterSize.height*0.5;
	float leftBorder = middlePoint.x - monsterSize.width*0.5;
	float rightBorder = middlePoint.x + monsterSize.width*0.5;

	//initRandomSeed
	struct timeval psv;
	gettimeofday(&psv, NULL);
	unsigned long int rand_seed = psv.tv_sec * 1000 + psv.tv_usec / 1000;
	srand(rand_seed);
	while (_bubbles.size() < BUBBLE_MAX_COUNT) {
		Sprite *bubble = Sprite::createWithSpriteFrameName("paopao_m1");
		float xpos = leftBorder + CCRANDOM_0_1() * monster->getContentSize().width;
		bubble->setPosition(Vec2(xpos, bottomBorder));
		bubble->setOpacity(0);
		addChild(bubble, 3);
		float delayTime = CCRANDOM_0_1() * monsterSize.height / BUBBLE_SPEED;
		SpriteFrameCache *cache = SpriteFrameCache::getInstance();
		Animation *breakAnimation = Animation::create();
		breakAnimation->addSpriteFrame(cache->getSpriteFrameByName("paopao_m1"));
		breakAnimation->addSpriteFrame(cache->getSpriteFrameByName("paopao_m2"));
		breakAnimation->addSpriteFrame(cache->getSpriteFrameByName("paopao_m3"));
		breakAnimation->addSpriteFrame(cache->getSpriteFrameByName("paopao_m4"));
		breakAnimation->addSpriteFrame(cache->getSpriteFrameByName("paopao_m5"));
		breakAnimation->setLoops(-1);
		breakAnimation->setRestoreOriginalFrame(true);
		breakAnimation->setDelayPerUnit(0.1f);
		ActionInterval *moveAction = Sequence::create(FadeIn::create(0.1f),
			MoveBy::create(monsterSize.height / BUBBLE_SPEED, Vec2(0, monsterSize.height)),
			FadeOut::create(0.1f),
			MoveBy::create(0.01f, Vec2(0, -monsterSize.height)), NULL);
		moveAction->setTag(10);
		bubble->runAction(Animate::create(breakAnimation));
		bubble->runAction(DelayTime::create(delayTime));
		bubble->runAction(RepeatForever::create(moveAction));
		_bubbles.pushBack(bubble);
	}

	_BubbleHit = 0;
	_isBubbleFailed = true;
	schedule(SEL_SCHEDULE(&MonsterLayer::onSpecialAttack), 0.1f);
}

void MonsterLayer::onSpecialAttack(float ft)
{
	ProgressTimer *longHPBar = (ProgressTimer*)getChildByName("hpbar");
	ProgressTimer *timeBarFull = (ProgressTimer*)getChildByName("timebar_full");
	auto timeBarEmpty = getChildByName("timebar_empty");
	if (timeBarFull->getPercentage() < 0.1 || _BubbleHit >= BUBBLE_SUCCESS_HIT) {
		timeBarEmpty->runAction(FadeOut::create(0.1f));
		timeBarFull->cleanup();
		timeBarFull->runAction(FadeOut::create(0.1f));
		longHPBar->runAction(FadeOut::create(0.1f));
		for each (Sprite* bubble in _bubbles)
		{
			bubble->cleanup();
			_bubbles.eraseObject(bubble);
			removeChild(bubble, true);
		}
		this->unschedule(SEL_SCHEDULE(&MonsterLayer::onSpecialAttack));
		if (_BubbleHit >= BUBBLE_SUCCESS_HIT) {
			this->getChildByTag(_target)->runAction(FadeOut::create(0.2f));
			_isBubbleFailed = false;
		}
		else {
			_isBubbleFailed = true;
		}
		for (int i = 0; i<_heads.size(); ++i)
			if ( i != _target)
				this->getChildByTag(i)->runAction(FadeIn::create(0.1f));
		_status = SPECIAL_ATTACK_FINISHED;
	}
}

bool MonsterLayer::isSpecialAttackSuccess() 
{
	if (_status == SPECIAL_ATTACK_FINISHED) {
		return !_isBubbleFailed;
	}
	else {
		CCLOG("Not the correct time to call this function!");
		return false;
	}
}
