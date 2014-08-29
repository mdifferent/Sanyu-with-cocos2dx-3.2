#ifndef __MAIN_MENU_SCENE_H__
#define __MAIN_MENU_SCENE_H__

#include "cocos2d.h"
#include "Resources.h"
#include <string>

USING_NS_CC;
using namespace std;

class MainMenuScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(MainMenuScene);

	void onEnter();
	void onEnterTransitionDidFinish();

	//Menu Button callback
	void startCallback(Ref* pSender);
	void loadCallback(Ref* pSender);
	void extraCallback(Ref* pSender);
	void systemCallback(Ref* pSender);
	void exitCallback(Ref* pSender);
	void cgCallback(Ref* pSender);
	void musicCallback(Ref* pSender);
	void rewardCallback(Ref* pSender);
	void unknownCallback(Ref* pSender);

private:
	bool _isRewardOpened;
};

#endif