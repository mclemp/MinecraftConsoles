#include "stdafx.h"
#include "MasterGameMode.h"
#include "MiniGameDef.h"
#include "EMiniGameId.h"
#include "..\Minecraft.Client\Common\GameRules\LevelRuleset.h"
#include "..\Minecraft.Client\Common\GameRules\CheckpointRuleDefinition.h"
#include "..\Minecraft.Client\Common\GameRules\TargetAreaRuleDefinition.h"
#include "..\Minecraft.Client\Common\GameRules\PowerupRuleDefinition.h"
#include "BlockDegradeRoutine.h"
#include "GameStats.h"
#include "..\Minecraft.Client\Common\GameRules\DegradationSequenceRuleDefinition.h"
#include "..\Minecraft.Client\Common\GameRules\ConsoleGameRulesConstants.h"

MasterGameMode::CountdownInfo::CountdownInfo()
{
	m_int0 = 0;
	m_onTimerFunc = NULL;
	m_onTimerFunc1 = NULL;
}

void MasterGameMode::StaticCtor()
{
}

MasterGameMode::~MasterGameMode()
{
	delete m_degradeRoutine;
	delete m_gameStats;
}

void MasterGameMode::Tick()
{
	CommonMasterGameMode::Tick();
}

long long MasterGameMode::RestartMapGenerator()
{
	long long result = CommonMasterGameMode::RestartMapGenerator();

	// broadcast seed to clients via packet type 25
	// TODO: send MapSelectInfoPacket with new seed

	return result;
}

void MasterGameMode::GetGameModeState() const
{
}

Level *MasterGameMode::GeneratorTargetLevel() const
{
	return NULL; // TODO: return MinecraftServer::getInstance()->getLevel(0)
}

void MasterGameMode::setChosenThemeWordId(int wordId)
{
	CommonMasterGameMode::setChosenThemeWordId(wordId);
}

void MasterGameMode::IsRoundPlaying() const
{
}

void MasterGameMode::getScoreboard() const
{
}

void MasterGameMode::GetSweptVolumeFromLastKnownPosition(shared_ptr<Player> player)
{
}

void MasterGameMode::GetLastCheckpointID(int statsUID)
{
}

void MasterGameMode::OnCheckpointEnter(const shared_ptr<Player> &player, unsigned int checkpointId, CheckpointRuleDefinition *checkpoint)
{
	CommonMasterGameMode::OnCheckpointEnter(player, checkpointId, checkpoint);
}

void MasterGameMode::OnPrimaryTargetEnter(const shared_ptr<Player> &player, TargetAreaRuleDefinition *target)
{
	CommonMasterGameMode::OnPrimaryTargetEnter(player, target);
}

void MasterGameMode::OnSecondaryTargetEnter(const shared_ptr<Player> &player, TargetAreaRuleDefinition *target)
{
	CommonMasterGameMode::OnSecondaryTargetEnter(player, target);
}

void MasterGameMode::OnPowerupEnter(const shared_ptr<Player> &player, unsigned int powerupId, PowerupRuleDefinition *powerup)
{
	CommonMasterGameMode::OnPowerupEnter(player, powerupId, powerup);
}

void MasterGameMode::PopulateChests()
{
	LevelRuleset *rules = NULL; // TODO: CConsoleMinecraftApp::sInstance.getGameRuleDefinitions()
	if(!rules)
		return;

	vector<GameRuleDefinition *> children;
	rules->getChildren(&children);

	// find OnInitialiseWorld rule
	GameRuleDefinition *initWorld = NULL;
	for(auto it = children.begin(); it != children.end(); it++)
	{
		// OnInitialiseWorld type is 30 in reference enum
		// but in this project it would need to be in ConsoleGameRulesConstants
		// For now just check through children for container placement rules
	}

	// evaluate PlaceContainer, DistributeItems, PopulateContainer rules
	for(auto it = children.begin(); it != children.end(); it++)
	{
		if((*it)->getActionType() == ConsoleGameRules::eGameRuleType_PlaceContainer)
		{
			// evaluate placement rule
		}
	}
}

void MasterGameMode::SetLockPlayerPositions(bool lock)
{
	// TODO: broadcast GameModePacket::LockPlayerLocation to all players
	// TODO: set SetPositionLocked on all ServerPlayers
}

void MasterGameMode::SetState(EInternalGameModeState state)
{
	// TODO: store state and broadcast to clients
}

void MasterGameMode::SetPlayersInvulnerable(bool invulnerable)
{
	m_playersInvulnerable = invulnerable;
}

void MasterGameMode::SelectNewGameRules()
{
	ChooseNextGameRules(false);
}

void MasterGameMode::ChooseNextGameRules(bool forceNew)
{
	// TODO: load base save data, get game rules, choose item set
}

int MasterGameMode::ChooseItemSet(const MiniGameDef &def, bool useRandom)
{
	return 0;
}

void MasterGameMode::SetupTeams()
{
	// TODO: assign players to teams based on minigame type
}

void MasterGameMode::GeneratePlaylistSyncInfo()
{
	// TODO: generate sync info for clients
}

void MasterGameMode::OnGameStart(MasterGameMode *_this, void *data)
{
	const MiniGameDef *minigame = CommonMasterGameMode::GetMiniGame();
	if(!minigame)
		return;

	_this->PopulateChests();

	if(minigame->GetId() == MINIGAME_GLIDE)
	{
		// setup elytra, checkpoints, targets for glide
		// TODO: get Level, spawn EnderCrystals at powerup locations if powerups active
		// TODO: start fall flying for players with elytra
		// TODO: process checkpoints and beacons
		// TODO: setup glide targets from TargetAreaRuleDefinitions

		_this->m_glideTargets.clear();
	}

	_this->SetLockPlayerPositions(false);

	// TODO: send GameModePacket with player bounds to all players
	// TODO: setup area bounds per team for BuildOff

	_this->SetState((MasterGameMode::EInternalGameModeState)10);

	if(minigame->GetId() == MINIGAME_BATTLE)
	{
		// TODO: add chest refill timer (30 second interval)
	}

	LevelRuleset *gameRules = NULL; // TODO: CConsoleMinecraftApp::sInstance.getGameRuleDefinitions()
	if(gameRules)
	{
		vector<GameRuleDefinition *> ruleChildren;
		gameRules->getChildren(&ruleChildren);

		for(auto it = ruleChildren.begin(); it != ruleChildren.end(); it++)
		{
			if((*it)->getActionType() == ConsoleGameRules::eGameRuleType_DegradationSequence)
			{
				DegradationSequenceRuleDefinition *degradeRule = (DegradationSequenceRuleDefinition *)(*it);
				_this->m_degradeRoutine = new BlockDegradeRoutine(NULL, degradeRule);
				break;
			}
		}
	}

	// start grace period timer
	_this->SetPlayersInvulnerable(false);

	if(_this->m_gameStats)
		_this->m_gameStats->OnRoundStart();
}

void MasterGameMode::OnRefillChestTimer(MasterGameMode *_this, void *data)
{
	_this->PopulateChests();
}

void MasterGameMode::OnGracePeriodEnd(MasterGameMode *_this, void *data)
{
	_this->SetPlayersInvulnerable(false);
}
