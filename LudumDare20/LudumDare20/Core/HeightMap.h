#pragma once
#include "raylib.h"
#include "BasicTypes.h"
#include "reactphysics3d.h"

class HeightMap
{
public:
	HeightMap(const char* path, Vector3 position, Vector3 size, rp3d::DynamicsWorld &world);
	~HeightMap();

	Vector3 GetPosition();

	void DrawHeightMap();
	void UnloadHeightMap();
private:
	Vector3 mapPosition = Vector3{ 0 };
	Model model = Model();
	Texture2D texture = Texture2D();
	rp3d::ProxyShape* proxyShape;
	rp3d::RigidBody* body;
	rp3d::HeightFieldShape* shape;
	float minHeight = 0.0f;
	float maxHeight = 100.0f;

	float heightValues[40 * 50] = {};
};

