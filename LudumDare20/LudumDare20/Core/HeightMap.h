#pragma once
#include "raylib.h"
#include "BasicTypes.h"

class HeightMap
{
public:
	HeightMap(const char* path, Vector3 position, Vector3 size);
	~HeightMap();

	Vector3 GetPosition();

	void DrawHeightMap();
	void UnloadHeightMap();
private:
	Vector3 mapPosition = Vector3{ 0 };
	Model model = Model();
	Texture2D texture = Texture2D();
};

