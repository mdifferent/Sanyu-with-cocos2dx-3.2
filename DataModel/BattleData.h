#ifndef __BATTLE_DATA_H__
#define __BATTLE_DATA_H__

#include "AbstractBattlerData.h"
#include <map>
#include <string>
#include "PlayerData.h"
#include "MonsterData.h"

using namespace std;
using namespace battledata;
namespace battledata {

	enum WINNING_CONDITIONS {
		KILL_ALL,
		KILL_SPEC,
		KEEP_ALIVE,
		NEVER
	};

	enum LOSE_CONDITION {
		ALL_DEAD,
		SOMEONE_DEAD,
		ROUNDS_REACH,
		ALWAYS
	};

	class BattleData
	{
	public:
		BattleData(void);
		~BattleData(void);

		static BattleData *loadData(int sceneNo);					//Load battle scene data from config file
		void loadPlayers(int saveNo){};								//Load player data from save file

		void setPlayer(PlayerData *newPlayer){};
		void setMonster(MonsterData *newMonster){};
		
		string getMapName() const { return _mapName; }
		string getBgmName() const { return _mapBgm; }

		map<int, string>* getPlayerNames();
		map<int, string>* getMonsterNames();
		int getPlayerCount() { return _players.size(); }
		int getMonsterCount() { return _monsters.size(); }

		int getPlayerProperty(int i, PLAYER_PROP_TYPE prop);
		int getMonsterProperty(int i, PLAYER_PROP_TYPE prop);
		BATTLER_STATUS getPlayerStatusAt(int num) const { return _players.at(num)->getStatus(); }
		BATTLER_STATUS getMonsterStatusAt(int num) const { return _monsters.at(num)->getStatus(); }
		void setPlayerStatusAt(int num, BATTLER_STATUS status) { _players.at(num)->setStatus(status); }
		void setMonsterStatusAt(int num, BATTLER_STATUS status) { _monsters.at(num)->setStatus(status); }
		void setPlayerProperty(int num, PLAYER_PROP_TYPE prop, int value) { _players.at(num)->setProperty(prop, value); }
		void setMonsterProperty(int num, PLAYER_PROP_TYPE prop, int value) { _monsters.at(num)->setProperty(prop, value); }

	private:
		string						_mapName;
		string						_mapBgm;
		map<int, PlayerData*>		_players;
		map<int, MonsterData*>		_monsters;
		WINNING_CONDITIONS			_winCon;
		LOSE_CONDITION				_loseCon;
	};
}
#endif