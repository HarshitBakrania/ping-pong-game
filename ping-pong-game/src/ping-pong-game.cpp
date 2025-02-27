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

		if (y + radius >= GetScreenHeight() || y - radius <= 0) {
			speedY *= -1;
		}

		if (x + radius >= GetScreenWidth() || x - radius <= 0) {
			speedX *= -1;
		} 
	}
};

class Paddle {
public:
	float x, y;
	float width, height;
	int speed;

	void Draw() {
		DrawRectangle(x, y, width, height, BLUE);
	}

	void Update() {
		if (y <= 0) {
			y = 0;
		}
		else if (y + height >= GetScreenHeight()) {
			y = GetScreenHeight() - height;
		}

		if (IsKeyDown(KEY_UP)) {
			y = y - speed;
		}
		else if (IsKeyDown(KEY_DOWN)) {
			y = y + speed;
		}
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

	Paddle player;
	player.width = 25;
	player.height = 120;
	player.x = screen_width - player.width - 10;
	player.y = screen_height / 2 - player.height / 2;
	player.speed = 6;

	while (WindowShouldClose() == false) {
		BeginDrawing();

		// Updating position
		ball.Upate();
		player.Update();

		// Drawing ball and paddles
		ClearBackground(BLACK);
		DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
		ball.Draw();
		DrawRectangle(10, screen_height / 2 - 60, 25, 120, WHITE);
		player.Draw();
		EndDrawing();
	}

	CloseWindow();
	return 0;
};