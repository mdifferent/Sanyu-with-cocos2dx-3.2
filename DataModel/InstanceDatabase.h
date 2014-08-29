#ifndef __INSTANCE_DATABASE_H__
#define __INSTANCE_DATABASE_H__

#include <map>
#include <list>

using namespace std;

class SkillData;
class ItemData;

class InstanceDatabase
{
public:
	static InstanceDatabase* getDatabaseInstance();
	static void releaseDatabase();

	bool initSkillSetByIds(list<int>);
	bool initItemSetByIds(list<int>);

	SkillData& getSkillById(int id);
	ItemData& getItemById(int id);
private:
	InstanceDatabase(){};
	~InstanceDatabase(){};

	static InstanceDatabase*		instance;
	map<int, SkillData*>			m_skillDataset;
	map<int, ItemData*>				m_itemDataset;
};
#endif