#include "stdafx.h"
#include "BlockDegradeRoutine.h"

BlockDegradeRoutine::BlockDegradeRoutine(ServerLevel *level, DegradationSequenceRuleDefinition *degradeRule)
	: m_level(level)
	, m_degradeRule(degradeRule)
	, m_active(false)
	, m_tickCount(0)
{
}

BlockDegradeRoutine::~BlockDegradeRoutine()
{
}

void BlockDegradeRoutine::tick()
{
	if(!m_active)
		return;

	m_tickCount++;
}
