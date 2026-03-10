#pragma once

#include "MapGenerator.h"
#include "AABB.h"
#include <vector>

class LayerGenerator;

class TumbleGenerator : public MapGenerator
{
public:
	TumbleGenerator(Random random, vector<LayerGenerator *> &layers);

	~TumbleGenerator();
	void StartGeneration(Level *level);
	const AABB *GetSpawnArea() const;
	void CleanUp(Level *level);
	const AABB *GetLayerBB(unsigned int layer);
	unsigned int GetNumberOfLayers();
	void GetLayerExtents(unsigned int layer, float *min, float *max);
	int GetBlockCountOnLayer(unsigned int layer);

	static const int LAYER_HEIGHTS[9];

	vector<LayerGenerator *> m_layers;
	vector<AABB *> m_layerBBs;
	vector<int> m_blockCounts;
	AABB *m_spawnArea;
};
