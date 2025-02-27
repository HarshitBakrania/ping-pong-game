#include <iostream>
#include <raylib.h>

class Ball {
public:
	float x, y;
	int speedX, speedY;
	int radius;

	void Draw() {
		DrawCircle(x, y, radius, WHITE);
	}

	void Upate() {
		x += speedX;
		y += speedY;
	}
};

int main() {
	std::cout << "Starting game!" << std::endl;
	const int screen_height = 800;
	const int screen_width = 1280;
	InitWindow(screen_width, screen_height, "Ping Pong Game");
	SetTargetFPS(60);

	Ball ball;
	ball.x = screen_width / 2;
	ball.y = screen_height / 2;
	ball.radius = 20;
	ball.speedX = 7;
	ball.speedY = 7;

	while (WindowShouldClose() == false) {
		BeginDrawing();

		ball.Draw();
		ball.Upate();

		ClearBackground(BLACK);
		DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
		DrawRectangle(10, screen_height / 2 - 60, 25, 120, WHITE);
		DrawRectangle(screen_width - 35, screen_height / 2 - 60, 25, 120, WHITE);
		EndDrawing();
	}

	CloseWindow();
	return 0;
};