#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "Views/MainMenuScene.h"
#include "Views\ConversationScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)  
#include "../proj.win32/WIN32Utils.h"
#endif 

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		string windowTile = "É¢Óð";
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		GBKToUTF(windowTile);
#endif
		glview = GLView::create(windowTile);
		glview->setFrameSize(800, 600);
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //auto scene = HelloWorld::createScene();
	//auto scene = MainMenuScene::createScene();
	auto scene = ConversationScene::create();
	scene->speaking("Î÷ÑÅÂå", "ABCÎ÷ÑÅÂåABCÎ÷ÑÅÂåABCÎ÷ÑÅÂåABCÎ÷ÑÅÂåABCÎ÷ÑÅÂåABC\nÎ÷ÑÅÂåABCÎ÷ÑÅÂåABCÎ÷ÑÅÂåABCÎ÷ÑÅÂåABCÎ÷ÑÅÂåABCÎ÷ÑÅÂåABCÎ÷ÑÅÂå");
	// run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
