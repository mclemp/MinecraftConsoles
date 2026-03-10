#pragma once

class Level;
class Player;
class Minecraft;

class GhostGameMode
{
public:
	GhostGameMode(Minecraft *minecraft);
	~GhostGameMode();

	void initLevel(Level *level);
	void tick();

	void RecordLastCheckpoint(shared_ptr<Player> player, unsigned int checkpointId);
	void RecordLapCompleted(shared_ptr<Player> player);
	void RecordProgress(shared_ptr<Player> player, double progress);

	bool isGhostMode() const { return m_isGhostMode; }
	void setGhostMode(bool ghost) { m_isGhostMode = ghost; }

	Minecraft *m_minecraft;
	bool m_isGhostMode;
};
