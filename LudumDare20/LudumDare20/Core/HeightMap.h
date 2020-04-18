#pragma once
#include "Raylib.h"
//#include "BasicTypes.h"

class HeightMap
{
public:
	HeightMap(const char* path, Vector3 position, Vector3 size);
	~HeightMap();

	Vector3 GetPosition();

	void DrawHeightMap();
	void UnloadHeightMap();
private:
	Vector3 mapPosition;
	Model model;
	Texture2D texture;
};

