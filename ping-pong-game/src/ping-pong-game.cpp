#include <iostream>
#include <raylib.h>

int main() {
	std::cout << "Starting game!" << std::endl;
	const int screen_height = 800;
	const int screen_width = 1280;
	InitWindow(screen_width, screen_height, "Ping Pong Game");
	SetTargetFPS(60);

	while(WindowShouldClose() == false) {
		BeginDrawing();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}