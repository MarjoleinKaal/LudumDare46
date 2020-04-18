#include "WaterGrid.h"
#include "Core/BasicTypes.h"
#include "raymath.h"

void DebugDrawWaterGrid(const Grid3d<WaterCell>& grid, Vec3 offset)
{
	Vec3I size = grid.GetSize();

	const Vec3 boxSize{ 1,1,1 };
	
	for (int y = 0; y < size.y; ++y)
	{
		for (int z = 0; z < size.z; ++z)
		{
			for (int x = 0; x < size.x; ++x)
			{
				Vector3 position = ConvertVector3(offset + Vec3{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) } * boxSize);
				//Vector3 position{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(z) };
				DrawCubeWires(position, boxSize.x, boxSize.y, boxSize.z, BLACK);
			}
		}
	}
}
