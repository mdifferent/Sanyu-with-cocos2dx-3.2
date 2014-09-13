#ifndef __MONSTER_LAYER_H__
#define __MONSTER_LAYER_H__

#include "cocos2d.h"
#include <map>
#include <string>

USING_NS_CC;
using namespace std;



class MonsterLayer : public Layer
{
public:
	enum MONSTER_LAYER_STATUS {
		WAIT_TARGET,
		TARGET_SELECTED,
		SPECIAL_ATTACK_PRE,
		SPECIAL_ATTACK,
		SPECIAL_ATTACK_FINISHED,
		SLEEP,
	};

	MonsterLayer(const map<int, string>* names) { _heads = *names; }
	~MonsterLayer() { delete &_heads; }

	bool init();
	static MonsterLayer* createWithNames(const map<int, string>*);

	void onMagicMatrixAvailable();
	void onMagicMatrixUnavailable();
	void initSpecialAttack(int monsterNo);
	void onSpecialAttack(float monsterNo);
	bool isSpecialAttackSuccess();
	void resetTarget() { _target = -1; }
	int getTarget() { return _target; }
	void setStatus(MONSTER_LAYER_STATUS status){ _status = status; }
	MONSTER_LAYER_STATUS getStatus() const { return _status; }

	void onAttacked(int target, int value, float percent, bool isDead);

private:
	bool initTouchListener();

	map<int, string> _heads;
	int _target;
	bool _isMagicMatrixAvailable;
	bool _isBubbleFailed;
	int _BubbleHit;
	MONSTER_LAYER_STATUS _status;

	Vector<Sprite*> _bubbles;
};
#endif