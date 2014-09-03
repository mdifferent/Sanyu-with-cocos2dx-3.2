#ifndef __PLAYER_LAYER_H__
#define __PLAYER_LAYER_H__

#include "cocos2d.h"
#include <map>
#include <string>
using namespace std;
USING_NS_CC;

enum PLAYER_LAYER_STATUS {
	WAIT_COMMAND,
	MENU_OPEN,
	MENU_SELECTED,
	WAIT_TARGET,
	TARGET_SELECTED,
	FINISHED
};


enum PLAYER_CMD {
	NONE,
	ATTACK,
	SKILL,
	GUARD,
	ITEM,
	ESCAPE
};

class PlayerLayer : public Layer
{
public:
	PlayerLayer(const map<int, string>* names) { _heads = *names; }
	~PlayerLayer() { delete &_heads; }

	bool init();
	static PlayerLayer* createWithNames(const map<int, string>*);

	void openMenu(int);
	void closeMenu(void);

	void playerAttackCallback(Ref* pSender);
	void playerSkillCallback(Ref* pSender);
	void playerGuardCallback(Ref* pSender);
	void playerEscapeCallback(Ref* pSender);
	void playerItemCallback(Ref* pSender);

	PLAYER_LAYER_STATUS getStatus() { return _status; }
	void setStatus(const PLAYER_LAYER_STATUS status) { _status = status; }
	int getSelectedPlayer() { CCLOG("Selected Player:%d", _selectedPlayer); return _selectedPlayer; }
	void resetSelectedPlayer() { _selectedPlayer = -1; }
	PLAYER_CMD getSelectedMenu() const { return _cmd; }
	void resetSelectedMenu() { _cmd = NONE; }
	int getTarget() { return _target; }
	void resetTarget() { _target = -1; }

	void onPlayerPropModified(int type, int target, int value);	//type 1:HP 2:SP
	void beforeSpecialAttack(int num = 0);
	void afterSpecialAttack(int num = 0);

private:
	map<int, string>		_heads;
	PLAYER_LAYER_STATUS		_status;
	PLAYER_CMD				_cmd;
	int						_selectedPlayer;
	int						_target;
};
#endif