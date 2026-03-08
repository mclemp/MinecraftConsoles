#include "stdafx.h"

#include "Scoreboard.h"
#include "Objective.h"
#include "ObjectiveCriteria.h"
#include "Score.h"
#include "PlayerTeam.h"

Objective *Scoreboard::getObjective(const wstring &name)
{
	auto it = objectivesByName.find(name);
	if(it != objectivesByName.end())
		return it->second;
	return NULL;
}

Objective *Scoreboard::addObjective(const wstring &name, ObjectiveCriteria *criteria)
{
	Objective *objective = getObjective(name);
	if(objective != NULL)
		return objective;

	objective = new Objective(this, name, criteria);

	auto it = objectivesByCriteria.find(criteria);
	vector<Objective *> *criteriaList;

	if(it == objectivesByCriteria.end())
	{
		criteriaList = new vector<Objective *>();
		objectivesByCriteria[criteria] = criteriaList;
	}
	else
	{
		criteriaList = it->second;
	}

	criteriaList->push_back(objective);
	objectivesByName[name] = objective;
	onObjectiveAdded(objective);

	return objective;
}

vector<Objective *> *Scoreboard::findObjectiveFor(ObjectiveCriteria *criteria)
{
	auto it = objectivesByCriteria.find(criteria);
	if(it != objectivesByCriteria.end())
		return new vector<Objective *>(*it->second);
	return new vector<Objective *>();
}

Score *Scoreboard::getPlayerScore(const wstring &name, Objective *objective)
{
	auto playerIt = playerScores.find(name);
	unordered_map<Objective *, Score *> *scores;

	if(playerIt == playerScores.end())
	{
		playerScores[name] = unordered_map<Objective *, Score *>();
		scores = &playerScores[name];
	}
	else
	{
		scores = &playerIt->second;
	}

	auto scoreIt = scores->find(objective);
	if(scoreIt == scores->end())
	{
		Score *score = new Score(this, objective, name);
		(*scores)[objective] = score;
		return score;
	}

	return scoreIt->second;
}

vector<Score *> *Scoreboard::getPlayerScores(Objective *objective)
{
	vector<Score *> *result = new vector<Score *>();

	for(auto it = playerScores.begin(); it != playerScores.end(); it++)
	{
		auto scoreIt = it->second.find(objective);
		if(scoreIt != it->second.end())
			result->push_back(scoreIt->second);
	}

	return result;
}

vector<Objective *> *Scoreboard::getObjectives()
{
	vector<Objective *> *result = new vector<Objective *>();
	for(auto it = objectivesByName.begin(); it != objectivesByName.end(); it++)
		result->push_back(it->second);
	return result;
}

vector<wstring> *Scoreboard::getTrackedPlayers()
{
	vector<wstring> *result = new vector<wstring>();
	for(auto it = playerScores.begin(); it != playerScores.end(); it++)
		result->push_back(it->first);
	return result;
}

void Scoreboard::resetPlayerScore(const wstring &player)
{
	auto it = playerScores.find(player);
	if(it != playerScores.end())
	{
		playerScores.erase(it);
		onPlayerRemoved(player);
	}
}

vector<Score *> *Scoreboard::getScores()
{
	vector<Score *> *result = new vector<Score *>();

	for(auto it = playerScores.begin(); it != playerScores.end(); it++)
	{
		for(auto scoreIt = it->second.begin(); scoreIt != it->second.end(); scoreIt++)
		{
			result->push_back(scoreIt->second);
		}
	}

	return result;
}

vector<Score *> *Scoreboard::getScores(Objective *objective)
{
	vector<Score *> *result = new vector<Score *>();

	for(auto it = playerScores.begin(); it != playerScores.end(); it++)
	{
		auto scoreIt = it->second.find(objective);
		if(scoreIt != it->second.end())
			result->push_back(scoreIt->second);
	}

	return result;
}

unordered_map<Objective *, Score *> *Scoreboard::getPlayerScores(const wstring &player)
{
	auto it = playerScores.find(player);
	if(it != playerScores.end())
		return &it->second;

	playerScores[player] = unordered_map<Objective *, Score *>();
	return &playerScores[player];
}

void Scoreboard::removeObjective(Objective *objective)
{
	objectivesByName.erase(objective->getName());

	for(int i = 0; i < DISPLAY_SLOTS; i++)
	{
		if(getDisplayObjective(i) == objective)
			setDisplayObjective(i, NULL);
	}

	auto critIt = objectivesByCriteria.find(objective->getCriteria());
	if(critIt != objectivesByCriteria.end())
	{
		auto &objectives = *critIt->second;
		for(auto it = objectives.begin(); it != objectives.end(); it++)
		{
			if(*it == objective)
			{
				objectives.erase(it);
				break;
			}
		}
	}

	for(auto it = playerScores.begin(); it != playerScores.end(); it++)
	{
		it->second.erase(objective);
	}

	onObjectiveRemoved(objective);
}

void Scoreboard::setDisplayObjective(int slot, Objective *objective)
{
	if(slot >= 0 && slot < DISPLAY_SLOTS)
		displayObjectives[slot] = objective;
}

Objective *Scoreboard::getDisplayObjective(int slot)
{
	if(slot >= 0 && slot < DISPLAY_SLOTS)
		return displayObjectives[slot];
	return NULL;
}

PlayerTeam *Scoreboard::getPlayerTeam(const wstring &name)
{
	auto it = teamsByName.find(name);
	if(it != teamsByName.end())
		return it->second;
	return NULL;
}

PlayerTeam *Scoreboard::addPlayerTeam(const wstring &name)
{
	PlayerTeam *team = getPlayerTeam(name);
	if(team != NULL)
		return team;

	team = new PlayerTeam(this, name);
	teamsByName[name] = team;
	onTeamAdded(team);

	return team;
}

void Scoreboard::removePlayerTeam(PlayerTeam *team)
{
	teamsByName.erase(team->getName());

	unordered_set<wstring> *players = team->getPlayers();
	for(auto it = players->begin(); it != players->end(); it++)
	{
		teamsByPlayer.erase(*it);
	}

	onTeamRemoved(team);
}

void Scoreboard::addPlayerToTeam(const wstring &player, PlayerTeam *team)
{
	if(getPlayersTeam(player) != NULL)
		removePlayerFromTeam(player);

	teamsByPlayer[player] = team;
	team->getPlayers()->insert(player);
}

bool Scoreboard::removePlayerFromTeam(const wstring &player)
{
	PlayerTeam *team = getPlayersTeam(player);
	if(team != NULL)
	{
		removePlayerFromTeam(player, team);
		return true;
	}
	return false;
}

void Scoreboard::removePlayerFromTeam(const wstring &player, PlayerTeam *team)
{
	teamsByPlayer.erase(player);
	team->getPlayers()->erase(player);
}

vector<wstring> *Scoreboard::getTeamNames()
{
	vector<wstring> *result = new vector<wstring>();
	for(auto it = teamsByName.begin(); it != teamsByName.end(); it++)
		result->push_back(it->first);
	return result;
}

vector<PlayerTeam *> *Scoreboard::getPlayerTeams()
{
	vector<PlayerTeam *> *result = new vector<PlayerTeam *>();
	for(auto it = teamsByName.begin(); it != teamsByName.end(); it++)
		result->push_back(it->second);
	return result;
}

shared_ptr<Player> Scoreboard::getPlayer(const wstring &name)
{
	return nullptr;
}

PlayerTeam *Scoreboard::getPlayersTeam(const wstring &name)
{
	auto it = teamsByPlayer.find(name);
	if(it != teamsByPlayer.end())
		return it->second;
	return NULL;
}

void Scoreboard::onObjectiveAdded(Objective *objective)
{
}

void Scoreboard::onObjectiveChanged(Objective *objective)
{
}

void Scoreboard::onObjectiveRemoved(Objective *objective)
{
}

void Scoreboard::onScoreChanged(Score *score)
{
}

void Scoreboard::onPlayerRemoved(const wstring &player)
{
}

void Scoreboard::onTeamAdded(PlayerTeam *team)
{
}

void Scoreboard::onTeamChanged(PlayerTeam *team)
{
}

void Scoreboard::onTeamRemoved(PlayerTeam *team)
{
}

wstring Scoreboard::getDisplaySlotName(int slot)
{
	switch(slot)
	{
	case DISPLAY_SLOT_LIST:
		return L"list";
	case DISPLAY_SLOT_SIDEBAR:
		return L"sidebar";
	case DISPLAY_SLOT_BELOW_NAME:
		return L"belowName";
	default:
		return L"";
	}
}

int Scoreboard::getDisplaySlotByName(const wstring &name)
{
	if(name == L"list")
		return DISPLAY_SLOT_LIST;
	else if(name == L"sidebar")
		return DISPLAY_SLOT_SIDEBAR;
	else if(name == L"belowName")
		return DISPLAY_SLOT_BELOW_NAME;
	return -1;
}