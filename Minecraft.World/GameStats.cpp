#include "stdafx.h"
#include "GameStats.h"

GameStats::GameStats()
	: m_roundNumber(0)
	, m_totalKills(0)
	, m_totalDeaths(0)
{
}

void GameStats::OnRoundStart()
{
	m_roundNumber++;
}

void GameStats::RecordTimeSpentInPosition(bool first)
{
}
