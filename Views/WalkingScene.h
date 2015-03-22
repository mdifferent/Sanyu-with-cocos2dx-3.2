#ifndef __WALKING_SCENE_H__
#define __WALKING_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>

USING_NS_CC;
using namespace std;

class WalkingScene : public Scene
{
public:
	WalkingScene(string walkerNamePrefix, int walkerFrameCount, string backgroundPrefix, int backgroundFrameCount);
	~WalkingScene(void);

	virtual bool init();
	void updateGame(float ft);		//Main loop

private:
	string	_bgPrefix;				
	int		_bgFrameCount;			
	string	_walkerNamePrefix;		
	int		_walkerFrameCount;

};


#endif