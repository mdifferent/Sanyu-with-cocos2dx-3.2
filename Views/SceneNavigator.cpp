#include "SceneNavigator.h"

SceneNavigator* SceneNavigator::_sharedInstance = new SceneNavigator();
SceneNavigator* SceneNavigator::getInstance()
{
	if (_sharedInstance == NULL)
		_sharedInstance = new SceneNavigator();
	return _sharedInstance;
}

void SceneNavigator::destroyInstance()
{
	if (_sharedInstance != NULL)
		delete _sharedInstance;
}

void SceneNavigator::naviTotScene(SCENE_TYPE type)
{
	switch (type)
	{
	case SCENE_TYPE::MAIN_MENU:
		break;
	case SCENE_TYPE::SAVE:
		break;
	case SCENE_TYPE::LOAD:
		break;
	case SCENE_TYPE::SYSTEM:
		break;
	case SCENE_TYPE::DIALOG:
		break;
	case SCENE_TYPE::BATTLE:
		//Director::getInstance()->replaceScene(BattleFieldScene::scene(1));
		break;
	default:
		break;
	}
}