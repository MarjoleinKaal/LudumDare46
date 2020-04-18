#pragma once
#include "Core/Grid3d.h"
#include "Core/BasicTypes.h"

struct WaterCell
{
	int dyeAmount;

	Vec3 velocity;
};

void DebugDrawWaterGrid(const Grid3d<WaterCell>& grid, Vec3 offset = {0, 0, 0});
