#include "WaterGrid.h"
#include "raylib.h"

void DebugDrawWaterGrid(const Grid3d<WaterCell>& grid)
{
	Vec3I size = grid.GetSize();
	
	for (int y = 0; y < size.y; ++y)
	{
		for (int z = 0; z < size.z; ++z)
		{
			for (int x = 0; x < size.x; ++x)
			{
				//TODO: Draw cubes
			}
		}
	}
}
