#pragma once

class GameStats
{
public:
	GameStats();

	void OnRoundStart();
	void RecordTimeSpentInPosition(bool first);

	int m_roundNumber;
	int m_totalKills;
	int m_totalDeaths;
};
