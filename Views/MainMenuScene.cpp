#include "MainMenuScene.h"
#include "BattleFieldScene.h"

Scene* MainMenuScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MainMenuScene::init()
{
	if ( !Layer::init() )
		return false;

	do {
		Size size = Director::getInstance()->getWinSize();
		Sprite *bgImg = Sprite::create(MAIN_MENU_BG);
		CC_BREAK_IF(!bgImg);
		bgImg->setPosition(size.width * 0.5, size.height * 0.5);
		this->addChild(bgImg, 0, "bg");

		auto *startBtn = MenuItemImage::create(MAINMENU_BTN_START, MAINMENU_BTN_START_PRESSED, CC_CALLBACK_1(MainMenuScene::startCallback, this));
		auto *loadBtn = MenuItemImage::create(MAINMENU_BTN_LOAD, MAINMENU_BTN_LOAD_PRESSED, CC_CALLBACK_1(MainMenuScene::loadCallback, this));
		auto *exBtn = MenuItemImage::create(MAINMENU_BTN_EXTRA, MAINMENU_BTN_EXTRA_PRESSED, CC_CALLBACK_1(MainMenuScene::extraCallback, this));
		auto *systemBtn = MenuItemImage::create(MAINMENU_BTN_SYSTEM, MAINMENU_BTN_SYSTEM_PRESSED, CC_CALLBACK_1(MainMenuScene::systemCallback, this));
		auto *exitBtn = MenuItemImage::create(MAINMENU_BTN_EXIT, MAINMENU_BTN_EXIT_PRESSED, CC_CALLBACK_1(MainMenuScene::exitCallback, this));
		auto *cgBtn = MenuItemImage::create(MAINMENU_BTN_CG, MAINMENU_BTN_CG_PRESSED, CC_CALLBACK_1(MainMenuScene::cgCallback, this));
		auto *musicBtn = MenuItemImage::create(MAINMENU_BTN_MUSIC, MAINMENU_BTN_MUSIC_PRESSED, CC_CALLBACK_1(MainMenuScene::musicCallback, this));
		auto *rewardBtn = MenuItemImage::create(MAINMENU_BTN_REWARD, MAINMENU_BTN_REWARD_PRESSED, CC_CALLBACK_1(MainMenuScene::rewardCallback, this));
		auto *unknownBtn = MenuItemImage::create(MAINMENU_BTN_UNKNOWN, MAINMENU_BTN_UNKNOWN_PRESSED, CC_CALLBACK_1(MainMenuScene::unknownCallback, this));

		auto *mainmenu = Menu::create(startBtn, loadBtn, exBtn, systemBtn, exitBtn, NULL);
		auto *exMenu = Menu::create(musicBtn, cgBtn, NULL);
		if (_isRewardOpened)
			exMenu->addChild(rewardBtn);
		else
			exMenu->addChild(unknownBtn);

		mainmenu->alignItemsHorizontallyWithPadding(50);
		mainmenu->setPosition(400, 70);
		mainmenu->setEnabled(true);
		this->addChild(mainmenu, 1, "mainmenu");

		exMenu->alignItemsVerticallyWithPadding(2);
		exMenu->setPosition(500, 140);
		exMenu->setOpacity(0);
		exMenu->setEnabled(false);
		this->addChild(exMenu, 1, "exmenu");

		return true;

	} while (0);

	return false;
}

void MainMenuScene::onEnter()
{
	CCLayer::onEnter();
	this->getChildByName("bg")->runAction(FadeIn::create(1.0f));
	this->getChildByName("mainmenu")->runAction(Sequence::createWithTwoActions(DelayTime::create(1.0f), FadeIn::create(1.0f)));
}

void MainMenuScene::onEnterTransitionDidFinish()
{
	CCLayer::onEnterTransitionDidFinish();
}

void MainMenuScene::startCallback(Ref* pSender)
{
	CCLOG("Start");
	Menu* exMenu = (Menu *)this->getChildByName("exmenu");
	if (exMenu->isEnabled()) {
		exMenu->setEnabled(false);
		exMenu->runAction(FadeOut::create(0.5f));
	}
	Director::getInstance()->replaceScene(BattleFieldScene::scene(1));
}

void MainMenuScene::loadCallback(Ref* pSender)
{
	CCLOG("Load");
	Menu* exMenu = (Menu *)this->getChildByName("exmenu");
	if (exMenu->isEnabled()) {
		exMenu->setEnabled(false);
		exMenu->runAction(FadeOut::create(0.5f));
	}

	//TODO:Load scene
}

void MainMenuScene::extraCallback(Ref* pSender)
{
	Menu* exMenu = (Menu *)this->getChildByName("exmenu");
	if (exMenu->isEnabled()) {
		exMenu->runAction(FadeOut::create(0.5f));
		exMenu->setEnabled(false);
	}
	else {
		exMenu->runAction(FadeIn::create(0.5f));
		exMenu->setEnabled(true);
	}
}

void MainMenuScene::systemCallback(Ref* pSender)
{
	CCLOG("System");
	Menu* exMenu = (Menu *)this->getChildByName("exmenu");
	if (exMenu->isEnabled()) {
		exMenu->setEnabled(false);
		exMenu->runAction(FadeOut::create(0.5f));
	}
	//TODO:System scene
}

void MainMenuScene::exitCallback(Ref* pSender)
{
	CCLOG("Exit");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MainMenuScene::cgCallback(Ref* pSender){}
void MainMenuScene::musicCallback(Ref* pSender){}
void MainMenuScene::rewardCallback(Ref* pSender){}
void MainMenuScene::unknownCallback(Ref* pSender){}