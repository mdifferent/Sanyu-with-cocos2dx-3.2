#include "InstanceDatabase.h"

InstanceDatabase *InstanceDatabase::instance = new InstanceDatabase();
InstanceDatabase* InstanceDatabase::getDatabaseInstance() {
	if (instance == NULL) {
		instance = new InstanceDatabase();
	}
	return InstanceDatabase::instance;
}

void InstanceDatabase::releaseDatabase() {
	if (instance != NULL) {
		map<int, SkillData*>::iterator skillit = instance->_skillDataset.begin();
		while (skillit != instance->_skillDataset.end()) {
			delete skillit->second;
		}
		instance->_skillDataset.clear();
		map<int, ItemData*>::iterator itemit = instance->_itemDataset.begin();
		while (itemit != instance->_itemDataset.end()) {
			delete itemit->second;
		}
		instance->_itemDataset.clear();
	}
	delete instance;
	instance = NULL;
}

SkillData& InstanceDatabase::getSkillById(int id) {
	if (instance->_skillDataset.find(id) != instance->_skillDataset.end())
		return *instance->_skillDataset.at(id);
}

ItemData& InstanceDatabase::getItemById(int id) {
	if (instance->_itemDataset.find(id) != instance->_itemDataset.end())
		return *instance->_itemDataset.at(id);
}

bool InstanceDatabase::initSkillSetByIds(list<int>) {
	//TODO: stub data here
	SkillData *p1 = new SkillData(1, "»ðÇò", listdata::ENEMY, false, 50, listdata::ATTACK);
	p1->setEffect(make_pair<listdata::EffectAttribute, int>(listdata::CURRENT_HP, 100));
	_skillDataset.insert(make_pair(1, p1));
	
	SkillData *p2 = new SkillData(2, "±©·çÑ©", listdata::ENEMY, true, 150, listdata::ATTACK);
	p2->setEffect(make_pair<listdata::EffectAttribute, int>(listdata::CURRENT_HP, 100));
	_skillDataset.insert(make_pair(2, p2));
	SkillData *p3 = new SkillData(3, "Äþ¾²Ö®Óê", listdata::FRIEND, true, 200, listdata::RECOVER);
	p3->setEffect(make_pair<listdata::EffectAttribute, int>(listdata::CURRENT_HP, 100));
	_skillDataset.insert(make_pair(3, p3));
	return true;
}

bool InstanceDatabase::initItemSetByIds(list<int>) {
	//TODO: stub data here
	ItemData *p1 = new ItemData(1, "Æ»¹û", listdata::FRIEND, false, listdata::CONSUME);
	p1->setEffect(make_pair<listdata::EffectAttribute, int>(listdata::CURRENT_HP, 10));
	_itemDataset.insert(make_pair(1, p1));

	ItemData *p2 = new ItemData(2, "Ñ¸½£", listdata::ENEMY, false, listdata::CONSUME);
	p2->setEffect(make_pair<listdata::EffectAttribute, int>(listdata::CURRENT_HP, 10));
	_itemDataset.insert(make_pair(2, p2));

	return true;
}