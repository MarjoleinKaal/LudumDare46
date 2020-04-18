// LudumDare20.cpp : Defines the entry point for the application.
//

#include "Main.h"
#include "raylib.h"

using namespace std;

int main()
{
	const int screenWidth = 1600;
	const int screenHeight = 900;

	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
			ClearBackground(RAYWHITE);
			DrawText("Yeeh a window", 190, 200, 60, LIGHTGRAY);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}
