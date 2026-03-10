#pragma once

//#include "

class ConsoleGameRules
{
public:
	enum EGameRuleType
	{
		eGameRuleType_Invalid = -1,
		eGameRuleType_Root = 0,

		eGameRuleType_LevelGenerationOptions = 1,
		eGameRuleType_ApplySchematic = 2,
		eGameRuleType_GenerateStructure = 3,
		eGameRuleType_GenerateBox = 4,
		eGameRuleType_PlaceBlock = 5,
		eGameRuleType_PlaceContainer = 6,
		eGameRuleType_PlaceSpawner = 7,
		eGameRuleType_BiomeOverride = 8,
		eGameRuleType_StartFeature = 9,

		eGameRuleType_AddItem = 10,
		eGameRuleType_AddEnchantment = 11,
		eGameRuleType_WeighedTreasureItem = 12,
		eGameRuleType_RandomItemSet = 13,
		eGameRuleType_DistributeItems = 14,

		eGameRuleType_WorldPosition = 15,
		eGameRuleType_LevelRules = 16,
		eGameRuleType_NamedArea = 17,
		eGameRuleType_ActiveChunkArea = 18,
		eGameRuleType_TargetArea = 19,
		eGameRuleType_ScoreRing = 20,
		eGameRuleType_ThermalArea = 21,
		eGameRuleType_PlayerBoundsVolume = 22,
		eGameRuleType_Killbox = 23,
		eGameRuleType_BlockLayer = 24,

		eGameRuleType_UseTileRule = 25,
		eGameRuleType_CollectItemRule = 26,
		eGameRuleType_CompleteAllRule = 27,
		eGameRuleType_UpdatePlayerRule = 28,

		eGameRuleType_OnGameStartSpawnPositions = 29,
		eGameRuleType_OnInitialiseWorld = 30,
		eGameRuleType_SpawnPositionSet = 31,
		eGameRuleType_PopulateContainer = 32,

		eGameRuleType_DegradationSequence = 33,
		eGameRuleType_RandomDissolveDegrade = 34,
		eGameRuleType_DirectionalDegrade = 35,

		eGameRuleType_GrantPermissions = 36,
		eGameRuleType_AllowIn = 37,

		eGameRuleType_LayerGeneration = 38,
		eGameRuleType_LayerAsset = 39,
		eGameRuleType_AnyCombinationOf = 40,
		eGameRuleType_CombinationDefinition = 41,
		eGameRuleType_Variations = 42,
		eGameRuleType_BlockDef = 43,
		eGameRuleType_LayerSize = 44,
		eGameRuleType_UniformSize = 45,
		eGameRuleType_RandomizeSize = 46,
		eGameRuleType_LinearBlendSize = 47,
		eGameRuleType_LayerShape = 48,
		eGameRuleType_BasicShape = 49,
		eGameRuleType_StarShape = 50,
		eGameRuleType_PatchyShape = 51,
		eGameRuleType_RingShape = 52,
		eGameRuleType_SpiralShape = 53,
		eGameRuleType_LayerFill = 54,
		eGameRuleType_BasicLayerFill = 55,
		eGameRuleType_CurvedLayerFill = 56,
		eGameRuleType_WarpedLayerFill = 57,
		eGameRuleType_LayerTheme = 58,
		eGameRuleType_NullTheme = 59,
		eGameRuleType_FilterTheme = 60,
		eGameRuleType_ShaftsTheme = 61,
		eGameRuleType_BasicPatchesTheme = 62,
		eGameRuleType_BlockStackTheme = 63,
		eGameRuleType_RainbowTheme = 64,
		eGameRuleType_TerracottaTheme = 65,
		eGameRuleType_FunctionPatchesTheme = 66,
		eGameRuleType_SimplePatchesTheme = 67,
		eGameRuleType_CarpetTrapTheme = 68,
		eGameRuleType_MushroomBlockTheme = 69,
		eGameRuleType_TextureTheme = 70,
		eGameRuleType_SchematicTheme = 71,
		eGameRuleType_BlockCollisionException = 72,

		eGameRuleType_Powerup = 73,
		eGameRuleType_Checkpoint = 74,
		eGameRuleType_CustomBeacon = 75,

		eGameRuleType_Count
	};

	enum EGameRuleAttr
	{
		eGameRuleAttr_Invalid = -1,

		eGameRuleAttr_descriptionName = 0,
		eGameRuleAttr_promptName,
		eGameRuleAttr_dataTag,

		eGameRuleAttr_enchantmentId,
		eGameRuleAttr_enchantmentLevel,

		eGameRuleAttr_itemId,
		eGameRuleAttr_quantity,
		eGameRuleAttr_auxValue,
		eGameRuleAttr_slot,

		eGameRuleAttr_name,

		eGameRuleAttr_food,
		eGameRuleAttr_health,

		eGameRuleAttr_tileId,
		eGameRuleAttr_useCoords,

		eGameRuleAttr_seed,
		eGameRuleAttr_flatworld,

		eGameRuleAttr_filename,
		eGameRuleAttr_rot,

		eGameRuleAttr_data,
		eGameRuleAttr_block,
		eGameRuleAttr_entity,

		eGameRuleAttr_facing,

		eGameRuleAttr_edgeTile,
		eGameRuleAttr_fillTile,
		eGameRuleAttr_skipAir,

		eGameRuleAttr_x,
		eGameRuleAttr_x0,
		eGameRuleAttr_x1,
		
		eGameRuleAttr_y,
		eGameRuleAttr_y0,
		eGameRuleAttr_y1,

		eGameRuleAttr_z,
		eGameRuleAttr_z0,
		eGameRuleAttr_z1,

		eGameRuleAttr_chunkX,
		eGameRuleAttr_chunkZ,

		eGameRuleAttr_yRot,

		eGameRuleAttr_spawnX,
		eGameRuleAttr_spawnY,
		eGameRuleAttr_spawnZ,

		eGameRuleAttr_orientation,
		eGameRuleAttr_dimension,

		eGameRuleAttr_topTileId,
		eGameRuleAttr_biomeId,

		eGameRuleAttr_feature,

		eGameRuleAttr_Count
	};

	static void write(DataOutputStream *dos, ConsoleGameRules::EGameRuleType eType)
	{
		dos->writeInt(eType);
	}

	static void write(DataOutputStream *dos, ConsoleGameRules::EGameRuleAttr eAttr)
	{
		dos->writeInt( eGameRuleType_Count + eAttr );
	}

};