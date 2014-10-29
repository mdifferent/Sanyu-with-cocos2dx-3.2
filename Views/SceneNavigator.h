#ifndef __SCENE_NAVIGATOR_H__
#define __SCENE_NAVIGATOR_H__

#include "MainMenuScene.h"
#include "BattleFieldScene.h"
#include "cocos2d.h"

USING_NS_CC;

enum class SCENE_TYPE {
	MAIN_MENU,
	SAVE,
	LOAD,
	SYSTEM,
	DIALOG,
	BATTLE
};

class SceneNavigator
{
public:
	static SceneNavigator* getInstance();
	static void destroyInstance();
	void naviTotScene(SCENE_TYPE);

private:
	SceneNavigator();
	~SceneNavigator();

	static SceneNavigator* _sharedInstance;

};

SceneNavigator::SceneNavigator()
{
}

SceneNavigator::~SceneNavigator()
{
}
#endif