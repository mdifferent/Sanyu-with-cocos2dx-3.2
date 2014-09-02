#ifndef __BATTLE_DATA_H__
#define __BATTLE_DATA_H__

#include "AbstractBattlerData.h"
#include <map>
#include <string>

using namespace std;
using namespace battledata;
namespace battledata {

	class PlayerData;
	class MonsterData;

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
		
		int getPlayerProperty(int i, PLAYER_PROP_TYPE prop);
		int getMonsterProperty(int i, PLAYER_PROP_TYPE prop);
		int getPlayerCount() { return _players.size(); }
		int getMonsterCount() { return _monsters.size(); }
		
		map<int, string>* getPlayerNames();
		map<int, string>* getMonsterNames();

		string getMapName() const { return _mapName; }
		string getBgmName() const { return _mapBgm; }

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