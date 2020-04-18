#include "HeightMap.h"
#include "Raylib.h"

HeightMap::HeightMap(const char* path, Vector3 position, Vector3 size)
{
	Image image = LoadImage(path);
	if (image.data == NULL) return;
	texture = LoadTextureFromImage(image);

	Mesh mesh = GenMeshHeightmap(image, size);
	model = LoadModelFromMesh(mesh);

	model.materials[0].maps[MAP_DIFFUSE].texture = texture;
	mapPosition = position;

	UnloadImage(image);
}

HeightMap::~HeightMap()
{
}


Vector3 HeightMap::GetPosition()
{
	return mapPosition;
}

void HeightMap::DrawHeightMap()
{
	DrawModel(model, mapPosition, 1.0f, RED);
}

void HeightMap::UnloadHeightMap()
{
	UnloadTexture(texture);
	UnloadModel(model);
}
