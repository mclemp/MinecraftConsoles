#include "stdafx.h"
#include "GhostGameMode.h"

GhostGameMode::GhostGameMode(Minecraft *minecraft)
{
	m_minecraft = minecraft;
	m_isGhostMode = false;
}

GhostGameMode::~GhostGameMode()
{
}

void GhostGameMode::initLevel(Level *level)
{
}

void GhostGameMode::tick()
{
}

void GhostGameMode::RecordLastCheckpoint(shared_ptr<Player> player, unsigned int checkpointId)
{
}

void GhostGameMode::RecordLapCompleted(shared_ptr<Player> player)
{
}

void GhostGameMode::RecordProgress(shared_ptr<Player> player, double progress)
{
}
