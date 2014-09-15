#ifndef __INSTANCE_DATABASE_H__
#define __INSTANCE_DATABASE_H__

#include <map>
#include <list>
#include "SkillData.h"
#include "ItemData.h"
using namespace std;
using namespace listdata;
class InstanceDatabase
{
public:
	static InstanceDatabase* getDatabaseInstance();
	static void releaseDatabase();

	bool initSkillSetByIds(list<int>);
	bool initItemSetByIds(list<int>);

	AbstractListItemData& getSkillById(int id);
	AbstractListItemData& getItemById(int id);
private:
	InstanceDatabase(){};
	~InstanceDatabase(){};

	static InstanceDatabase*		instance;
	map<int, SkillData*>			_skillDataset;
	map<int, ItemData*>				_itemDataset;
};
#endif