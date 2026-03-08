#include "stdafx.h"
#include "TumbleGenerator.h"

const int TumbleGenerator::LAYER_HEIGHTS[9] = { 4, 4, 4, 4, 3, 3, 2, 2, 1 };

TumbleGenerator::TumbleGenerator(Random random, vector<LayerGenerator *> &layers)
	: MapGenerator(random)
	, m_layers(layers)
	, m_spawnArea(NULL)
{
}

TumbleGenerator::~TumbleGenerator()
{
}

void TumbleGenerator::StartGeneration(Level *level)
{
	m_layerBBs.clear();
	m_blockCounts.clear();

	int totalHeight = 0;
	unsigned int layerCount = (unsigned int)m_layers.size();

	for(unsigned int i = 0; i < layerCount; i++)
	{
		AABB *bb = AABB::newPermanent(-16.0, (double)totalHeight, -16.0, 16.0, (double)(totalHeight + 1), 16.0);

		m_layerBBs.push_back(bb);
		m_blockCounts.push_back(0);

		unsigned int idx = layerCount < 9 ? layerCount : 9;
		int spacing = LAYER_HEIGHTS[idx > 0 ? idx - 1 : 0];
		totalHeight += spacing;
	}

	double halfHeight = (double)(totalHeight / 2);
	for(unsigned int i = 0; i < m_layerBBs.size(); i++)
	{
		m_layerBBs[i]->y0 -= halfHeight;
		m_layerBBs[i]->y1 -= halfHeight;
	}

	if(!m_layerBBs.empty())
	{
		m_spawnArea = AABB::newPermanent(m_layerBBs[0]->x0, m_layerBBs[0]->y0, m_layerBBs[0]->z0, m_layerBBs[0]->x1, m_layerBBs[0]->y1, m_layerBBs[0]->z1);
		for(unsigned int i = 1; i < m_layerBBs.size(); i++)
		{
			if(m_layerBBs[i]->y0 < m_spawnArea->y0)
				m_spawnArea->y0 = m_layerBBs[i]->y0;
			if(m_layerBBs[i]->y1 > m_spawnArea->y1)
				m_spawnArea->y1 = m_layerBBs[i]->y1;
		}
	}
}

const AABB *TumbleGenerator::GetSpawnArea() const
{
	return m_spawnArea;
}

void TumbleGenerator::CleanUp(Level *level)
{
	m_layers.clear();
	m_layerBBs.clear();
	m_blockCounts.clear();
}

const AABB *TumbleGenerator::GetLayerBB(unsigned int layer)
{
	if(layer >= m_layerBBs.size() || layer > 8)
		return NULL;
	return m_layerBBs[layer];
}

unsigned int TumbleGenerator::GetNumberOfLayers()
{
	return (unsigned int)m_layerBBs.size();
}

void TumbleGenerator::GetLayerExtents(unsigned int layer, float *min, float *max)
{
	if(layer >= m_layerBBs.size() || layer > 8)
		return;

	*min = (float)m_layerBBs[layer]->y0;
	*max = (float)m_layerBBs[layer]->y1;
}

int TumbleGenerator::GetBlockCountOnLayer(unsigned int layer)
{
	if(layer >= m_blockCounts.size())
		return 0;
	return m_blockCounts[layer];
}
