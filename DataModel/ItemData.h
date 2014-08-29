#ifndef __ITEM_DATA_H__
#define __ITEM_DATA_H__

#include "AbstractListItemData.h"

namespace listdata
{
	enum ITEM_TYPE {
		CONSUME,
		ATTRIBUTE,
		SPECIAL
	};

	class ItemData : public AbstractListItemData
	{
	public:
		ItemData(int id, string name, TargetType target, bool multi, ITEM_TYPE type)
			:AbstractListItemData(id, name, target, multi), _type(type) {}
		~ItemData(){}

		ITEM_TYPE getItemType() const { return _type; }
	private:
		ITEM_TYPE _type;
	};
}


#endif