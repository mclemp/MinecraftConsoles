#pragma once

#include "GameRuleDefinition.h"
#include <vector>

using namespace std;

class DegradationSequenceRuleDefinition : public GameRuleDefinition
{
public:
	DegradationSequenceRuleDefinition();
	~DegradationSequenceRuleDefinition();

	virtual int getActionType() const { return 33; }

	void getChildrenByType(int type, vector<GameRuleDefinition *> &out);

	vector<GameRuleDefinition *> m_children;
};
