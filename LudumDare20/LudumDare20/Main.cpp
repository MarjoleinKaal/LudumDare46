// LudumDare20.cpp : Defines the entry point for the application.
//

#include "Main.h"
#include "raylib.h"
#include "Core/HeightMap.h"
#include "Water/WaterGrid.h"

#include <filesystem>

using namespace std;

int main()
{
	std::cout << "Running from: " << std::filesystem::current_path() << "\n\n";

	
	const int screenWidth = 1600;
	const int screenHeight = 900;

	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	Camera camera = { { 18.0f, 18.0f, 18.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }, 45.0f, 0 };



	Vector3 mapPosition = { -8.0f, 0.0f, -8.0f };
	Vector3 size = { 16,8,16 };
	HeightMap* map = new HeightMap("resources/heightMap.png", mapPosition, size);

	SetCameraMode(camera, CAMERA_FREE);  // Set an orbital camera mode
	SetTargetFPS(60);

	Grid3d<WaterCell> waterGrid{ 8, 8, 8 };

	while (!WindowShouldClose())
	{
		UpdateCamera(&camera);

		BeginDrawing();

			ClearBackground(RAYWHITE);

			BeginMode3D(camera);

				map->DrawHeightMap();
				DrawGrid(20, 1.0f);

				DebugDrawWaterGrid(waterGrid);
	
			EndMode3D();

			DrawFPS(10, 10);
		EndDrawing();
	}

	map->UnloadHeightMap();

	CloseWindow();

	return 0;
}
