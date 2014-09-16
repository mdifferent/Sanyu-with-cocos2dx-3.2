#ifndef __ITEM_DATA_H__
#define __ITEM_DATA_H__

#include "AbstractListItemData.h"

	enum class ITEM_TYPE {
		CONSUME,
		ATTRIBUTE,
		SPECIAL
	};

	class ItemData : public AbstractListItemData
	{
	public:
		ItemData(int id, string name, TARGET_TYPE target, bool multi, ITEM_TYPE type)
			:AbstractListItemData(id, name, target, multi), _type(type) {}
		~ItemData(){}

		ITEM_TYPE getItemType() const { return _type; }
		virtual int getCost() { return 1; }
	private:
		ITEM_TYPE _type;
	};


#endif