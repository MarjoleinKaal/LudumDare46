// LudumDare20.cpp : Defines the entry point for the application.
//

#include "Main.h"
#include "raylib.h"
#include "reactphysics3d.h"
#include "Core/HeightMap.h"
#include "Core/SkyBox.h"
#include "Water/WaterGrid.h"


#include <filesystem>

using namespace std;

int main()
{
	std::cout << "Running from: " << std::filesystem::current_path() << "\n\n";

	
	const int screenWidth = 1600;
	const int screenHeight = 900;

	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "yeeh its a window");

	Camera camera = { { 18.0f, 18.0f, 18.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };


	Vector3 mapPosition = { -8.0f, 0.0f, -8.0f };
	Vector3 size = { 16,8,16 };
	HeightMap* map = new HeightMap("resources/heightMap.png", mapPosition, size);
	SkyBox* skybox = new SkyBox("resources/dresden_square.hdr");


	rp3d::Vector3 gravity(0.0, -9.81, 0.0);
	rp3d::DynamicsWorld world(gravity);
	world.setNbIterationsPositionSolver(8);
	world.setNbIterationsVelocitySolver(15);

	SetCameraMode(camera, CAMERA_FREE);  // Set an orbital camera mode
	SetTargetFPS(60);

	Grid3d<WaterCell> waterGrid{ 8, 8, 8 };

	//
	rp3d::Vector3 initPosition(0.0, 8.0, 0.0);
	rp3d::Quaternion initOrientation = rp3d::Quaternion ::
		identity();
	rp3d::Transform transform(initPosition, initOrientation);
	// Create a rigid body in the world
	rp3d::RigidBody* body;
	body = world.createRigidBody(transform);

	rp3d::decimal radius = rp3d::decimal(3.0);
	rp3d::SphereShape shape(radius);
	
	rp3d::Transform transform_ = rp3d::Transform::identity();
	rp3d::decimal mass = rp3d::decimal(4.0);

	rp3d::ProxyShape* proxyShape;
	proxyShape = body->addCollisionShape(&shape, transform_, mass);
	
	//

	float accumulator = 0;
	long double previousFrameTime = 0;

	while (!WindowShouldClose())
	{
		const float timeStep = 1.0 / 60.0f;

		long double currentFrameTime = GetFrameTime();
		long double deltaTime = currentFrameTime - previousFrameTime;
		previousFrameTime = currentFrameTime;
		accumulator = deltaTime;

		while (accumulator >= timeStep)
		{
			world.update(timeStep);
			accumulator -= timeStep;
		}

		UpdateCamera(&camera);

		BeginDrawing();

			ClearBackground(RAYWHITE);

			BeginMode3D(camera);
				
				map->DrawHeightMap();
				
				DrawGrid(20, 1.0f);

				DebugDrawWaterGrid(waterGrid);
				skybox->DrawSkyBox();
			EndMode3D();

			DrawFPS(10, 10);
		EndDrawing();
	}

	map->UnloadHeightMap();
	skybox->UnloadSkyBox();
	delete map;
	delete skybox;

	CloseWindow();

	return 0;
}
