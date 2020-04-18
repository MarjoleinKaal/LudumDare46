#pragma once
#include "Core/Grid3d.h"

struct WaterCell
{
	int dyeAmount;

	Vec3 velocity;
};

void DebugDrawWaterGrid(const Grid3d<WaterCell>& grid);
