#ifndef __BATTLE_DATA_H__
#define __BATTLE_DATA_H__

#include "AbstractBattlerData.h"
#include <map>
#include <string>
#include "PlayerData.h"
#include "MonsterData.h"

using namespace std;
	enum class WINNING_CONDITIONS {
		KILL_ALL,
		KILL_SPEC,
		KEEP_ALIVE,
		NEVER
	};

	enum class LOSE_CONDITION {
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
		void setMapName(string name) { _mapName = name; }
		LOSE_CONDITION getLoseCondition() { return _loseCon; }
		WINNING_CONDITIONS getWinCondition() { return _winCon; }
		int getRoundLimit() { return _roundLimit; }
		list<int> getVipList() { return _vips; }

		map<int, string>* getPlayerNames();
		map<int, string> getMonsterNames();
		int getPlayerCount() { return _players.size(); }
		int getMonsterCount() { return _monsters.size(); }

		int getPlayerProperty(int i, PLAYER_PROP_TYPE prop) { return _players.at(i)->getProperty(prop); }
		int getMonsterProperty(int i, PLAYER_PROP_TYPE prop) { return _monsters.at(i)->getProperty(prop); }
		BATTLER_STATUS getPlayerStatusAt(int num) const { return _players.at(num)->getStatus(); }
		BATTLER_STATUS getMonsterStatusAt(int num) const { return _monsters.at(num)->getStatus(); }
		void setPlayerStatusAt(int num, BATTLER_STATUS status) { _players.at(num)->setStatus(status); }
		void setMonsterStatusAt(int num, BATTLER_STATUS status) { _monsters.at(num)->setStatus(status); }
		void setPlayerProperty(int num, PLAYER_PROP_TYPE prop, int value) { _players.at(num)->setProperty(prop, value); }
		void setMonsterProperty(int num, PLAYER_PROP_TYPE prop, int value) { _monsters.at(num)->setProperty(prop, value); }

		pair<int, int> getPlayerItem(int playerNum, int itemSeq) { return _players.at(playerNum)->getItem(itemSeq); }
		pair<int, int> getPlayerSkill(int playerNum, int skillSeq) { return _players.at(playerNum)->getSkill(skillSeq); }
		int getPlayerItemCount(int playerNum) { return _players.at(playerNum)->getItemCount(); }
		int getPlayerSkillCount(int playerNum) { return _players.at(playerNum)->getSkillCount(); }

		void playerUseItem(int playerNum, int itemId) { _players.at(playerNum)->useItem(itemId); }
		void playerUseSkill(int playerNum, int skillId) { _players.at(playerNum)->useSkill(skillId); }

	private:
		string						_mapName;
		string						_mapBgm;
		map<int, PlayerData*>		_players;
		map<int, MonsterData*>		_monsters;
		WINNING_CONDITIONS			_winCon;
		LOSE_CONDITION				_loseCon;

		int							_roundLimit;		//Useful when winning/lose condition has round limit
		list<int>					_vips;				//Useful when winning condition has some keep alive
	};
#endif