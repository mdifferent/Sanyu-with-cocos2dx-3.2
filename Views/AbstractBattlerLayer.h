#ifndef __ABSTRACT_BATTLER_LAYER_H__
#define __ABSTRACT_BATTLER_LAYER_H__

#include "cocos2d.h"
#include <map>
#include <string>

USING_NS_CC;
using namespace std;

class AbstractBattlerLayer: public Layer
{
public:
	AbstractBattlerLayer();
	~AbstractBattlerLayer();

	virtual bool init() = 0;

protected:
	map<int, string> _heads;
}
#endif