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

AbstractListItemData* InstanceDatabase::getSkillById(int id) {
	if (instance->_skillDataset.find(id) != instance->_skillDataset.end())
		return instance->_skillDataset.at(id);
}

AbstractListItemData* InstanceDatabase::getItemById(int id) {
	if (instance->_itemDataset.find(id) != instance->_itemDataset.end())
		return instance->_itemDataset.at(id);
}

bool InstanceDatabase::initSkillSetByIds(list<int>) {
	//TODO: stub data here
	SkillData *p1 = new SkillData(1, "»ðÇò", TARGET_TYPE::ENEMY, false, 50, SKILL_TYPE::ATTACK);
	p1->setEffect(make_pair<EFFECT_ATTRIBUTE, int>(EFFECT_ATTRIBUTE::CURRENT_HP, 100));
	_skillDataset.insert(make_pair(1, p1));
	
	SkillData *p2 = new SkillData(2, "±©·çÑ©", TARGET_TYPE::ENEMY, true, 150, SKILL_TYPE::ATTACK);
	p2->setEffect(make_pair<EFFECT_ATTRIBUTE, int>(EFFECT_ATTRIBUTE::CURRENT_HP, 100));
	_skillDataset.insert(make_pair(2, p2));
	SkillData *p3 = new SkillData(3, "Äþ¾²Ö®Óê", TARGET_TYPE::FRIEND, true, 200, SKILL_TYPE::RECOVER);
	p3->setEffect(make_pair<EFFECT_ATTRIBUTE, int>(EFFECT_ATTRIBUTE::CURRENT_HP, 100));
	_skillDataset.insert(make_pair(3, p3));
	return true;
}

bool InstanceDatabase::initItemSetByIds(list<int>) {
	//TODO: stub data here
	ItemData *p1 = new ItemData(1, "Æ»¹û", TARGET_TYPE::FRIEND, false, ITEM_TYPE::CONSUME);
	p1->setEffect(make_pair<EFFECT_ATTRIBUTE, int>(EFFECT_ATTRIBUTE::CURRENT_HP, 10));
	_itemDataset.insert(make_pair(1, p1));

	ItemData *p2 = new ItemData(2, "Ñ¸½£", TARGET_TYPE::ENEMY, false, ITEM_TYPE::CONSUME);
	p2->setEffect(make_pair<EFFECT_ATTRIBUTE, int>(EFFECT_ATTRIBUTE::CURRENT_HP, 10));
	_itemDataset.insert(make_pair(2, p2));

	return true;
}