#ifndef __LIST_LAYER_H__
#define __LIST_LAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

	enum LIST_TYPE {
		ITEM_LIST,
		SKILL_LIST,
		EMPTY
	};

	class ListLayer : public Layer
	{
	public:
		bool init();
		static ListLayer *createWithDataSource(TableViewDataSource *source);

		void setContentType(LIST_TYPE);
		LIST_TYPE getContentType() const;
		void setDataSource(TableViewDataSource *source){ _datasource = source; }
		void setDelegate(TableViewDelegate *delegate){ _pTableView->setDelegate(delegate); }
		void setTouchEnabled(bool value);

	private:
		LIST_TYPE				_type;
		TableView*				_pTableView;
		Sprite*					_pBackImg;
		Label*					_pLabel;
		TableViewDataSource*	_datasource;
	};


#endif