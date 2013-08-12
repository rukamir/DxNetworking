#pragma once

#include "Entity.h"
#include <stdio.h>

class Water : public Entity
{
private:
	struct NoiseMapType 
	{ 
		float x, y, z;
	};
	int m_waterWidth, m_waterHeight;
	NoiseMapType* m_noiseMap;
public:
	Water(int id);
	~Water(){}

	void NormalizeHeightMap();
	bool LoadHeightMap(char* filename);
};