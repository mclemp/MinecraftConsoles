#pragma once

#include "CommonMasterGameMode.h"

enum EGameModeState
{
	GAMEMODE_STATE_INIT = 0,
	GAMEMODE_STATE_ROUND_ENDING_TO_LOBBY = 2,
	GAMEMODE_STATE_FINISH_VOTING = 3,
	GAMEMODE_STATE_ROUND_WAITING_TO_START = 5,
	GAMEMODE_STATE_ROUND_START = 6,
	GAMEMODE_STATE_ROUND_PLAY = 7,
	GAMEMODE_STATE_ROUND_ENDING = 9,
	GAMEMODE_STATE_NEXT_ROUND = 10
};

class ClientMasterGameMode : public CommonMasterGameMode
{
public:
	ClientMasterGameMode();
	~ClientMasterGameMode();

	void Tick();
	void OnExitedGame();
	void GetGameModeState() const;
	Level *GeneratorTargetLevel() const;
	void IsRoundPlaying() const;
	void getScoreboard() const;
	void ResetMapDistances();
	void GetSweptVolumeFromLastKnownPosition(shared_ptr<Player> player);
	void GetLastCheckpointID(int statsUID);
	void OnProgressMade(const shared_ptr<Player> &player, double progress);

	bool IsRoundRestarting();

	EGameModeState m_gameModeState;
	bool m_roundRestarting;
};
