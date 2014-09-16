#ifndef __LIST_ITEM_CELL_H__
#define __LIST_ITEM_CELL_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <string>

USING_NS_CC_EXT;
USING_NS_CC;
using namespace std;

class ListItemCell : public TableViewCell
{
public:
	static ListItemCell *create(const string name, const string target, const int amount);
	bool init(void);
	void updateLabels(const string name, const string target, const int amount);

	void onSelected() { _bg->setOpacity(200); }
	void onDeselected(){ _bg->setOpacity(0); }
	bool isSelected() { return _bg->getOpacity() > 0 ? true : false; }

private:
	Label *_pItemName;
	Label *_pTarget;
	Label *_pAmount;
	Sprite *_bg;
};

#endif