#pragma once

class ServerLevel;
class DegradationSequenceRuleDefinition;

class BlockDegradeRoutine
{
public:
	BlockDegradeRoutine(ServerLevel *level, DegradationSequenceRuleDefinition *degradeRule);
	~BlockDegradeRoutine();

	void tick();
	bool isActive() const { return m_active; }

	ServerLevel *m_level;
	DegradationSequenceRuleDefinition *m_degradeRule;
	bool m_active;
	int m_tickCount;
};
