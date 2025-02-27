#include <iostream>
#include <raylib.h>
#include <cmath>

class Ball {
public:
    float x, y;
    int speedX, speedY;
    int radius;

    Ball(int screen_width, int screen_height) {
        x = screen_width / 2;
        y = screen_height / 2;
        radius = 20;
        speedX = (GetRandomValue(0, 1) == 0) ? -7 : 7;
        speedY = (GetRandomValue(0, 1) == 0) ? -7 : 7;
    }

    void Update(int& botScore, int& playerScore) {
        x += speedX;
        y += speedY;

        // Bounce off top and bottom walls
        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speedY *= -1;
        }

        // Score handling
        if (x + radius >= GetScreenWidth()) {
            botScore++;
            ResetBall();
        }
        else if (x - radius <= 0) {
            playerScore++;
            ResetBall();
        }
    }

    void ResetBall() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
        speedX = (GetRandomValue(0, 1) == 0) ? -7 : 7;
        speedY = (GetRandomValue(0, 1) == 0) ? -7 : 7;
    }

    void Draw() {
        DrawCircle(x, y, radius, WHITE);
    }
};

class Paddle {
protected:
    void LimitMovement() {
        if (y <= 0) y = 0;
        else if (y + height >= GetScreenHeight()) y = GetScreenHeight() - height;
    }

public:
    float x, y;
    float width, height;
    int speed;

    Paddle(float x, float y) {
        this->x = x;
        this->y = y;
        width = 25;
        height = 120;
        speed = 7;
    }

    void Update() {
        if (IsKeyDown(KEY_UP)) {
            y -= speed;
        }
        else if (IsKeyDown(KEY_DOWN)) {
            y += speed;
        }
        LimitMovement();
    }

    void Draw(Color color) {
        DrawRectangle(x, y, width, height, color);
    }
};

class BotPaddle : public Paddle {
public:
    BotPaddle(float x, float y) : Paddle(x, y) {};

    void Update(int ball_y) {
        if (y + height / 2 > ball_y) {
            y -= speed;
        }
        else if (y + height / 2 < ball_y) {
            y += speed;
        }
        LimitMovement();
    }
};

int main() {
    const int screen_width = 1280;
    const int screen_height = 800;
    InitWindow(screen_width, screen_height, "Ping Pong Game");
    SetTargetFPS(60);

    int playerScore = 0;
    int botScore = 0;

    Ball ball(screen_width, screen_height);
    Paddle player(screen_width - 35, screen_height / 2 - 60);
    BotPaddle bot(10, screen_height / 2 - 60);

    while (!WindowShouldClose()) {
        // Update game objects
        ball.Update(botScore, playerScore);
        player.Update();
        bot.Update(ball.y);

        // Ball-Paddle collision handling
        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ player.x, player.y, player.width, player.height })) {
            ball.speedX *= -1;
            if (abs(ball.speedX) < 15) {
                ball.speedX += (ball.speedX > 0) ? 1 : -1;
            }
        }
        if (CheckCollisionCircleRec(Vector2{ ball.x, ball.y }, ball.radius, Rectangle{ bot.x, bot.y, bot.width, bot.height })) {
            ball.speedX *= -1;
            if (abs(ball.speedX) < 15) {
                ball.speedX += (ball.speedX > 0) ? 1 : -1;
            }
        }

        BeginDrawing();
        ClearBackground(BLACK);

        // Draw objects
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        ball.Draw();
        player.Draw(BLUE);
        bot.Draw(RED);

        // Display Score
        DrawText(TextFormat("%i", botScore), screen_width / 4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", playerScore), 3 * screen_width / 4 - 20, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
