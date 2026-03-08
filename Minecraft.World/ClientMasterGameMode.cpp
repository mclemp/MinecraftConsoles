#include "stdafx.h"
#include "ClientMasterGameMode.h"
#include "MiniGameDef.h"

ClientMasterGameMode::ClientMasterGameMode()
{
	m_gameModeState = GAMEMODE_STATE_INIT;
	m_roundRestarting = false;
}

ClientMasterGameMode::~ClientMasterGameMode()
{
}

void ClientMasterGameMode::Tick()
{
	CommonMasterGameMode::Tick();
}

void ClientMasterGameMode::OnExitedGame()
{
	CommonMasterGameMode::OnExitedGame();
	m_gameModeState = GAMEMODE_STATE_INIT;
	m_roundRestarting = false;
}

void ClientMasterGameMode::GetGameModeState() const
{
}

Level *ClientMasterGameMode::GeneratorTargetLevel() const
{
	return NULL;
}

void ClientMasterGameMode::IsRoundPlaying() const
{
}

void ClientMasterGameMode::getScoreboard() const
{
}

void ClientMasterGameMode::ResetMapDistances()
{
	CommonMasterGameMode::ResetMapDistances();
}

void ClientMasterGameMode::GetSweptVolumeFromLastKnownPosition(shared_ptr<Player> player)
{
}

void ClientMasterGameMode::GetLastCheckpointID(int statsUID)
{
}

void ClientMasterGameMode::OnProgressMade(const shared_ptr<Player> &player, double progress)
{
	CommonMasterGameMode::OnProgressMade(player, progress);
}

bool ClientMasterGameMode::IsRoundRestarting()
{
	return m_roundRestarting;
}
