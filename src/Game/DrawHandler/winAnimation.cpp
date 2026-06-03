#include "drawHandler.h"
#include <raymath.h>
#include "../game.h"

DrawHandler::WinAnimation::WinAnimation(Game *aGame)
{
    game = aGame;
    index = 0;
    acceleration = {0, 500.0f};
    reset = true;
}

void DrawHandler::WinAnimation::Draw(Texture2D &spritesheet, bool debugMode)
{
    DrawRectangleLines(cursor.x, cursor.y, 50, 100, GREEN);
}

void DrawHandler::WinAnimation::Update()
{
    if(reset)
    {
        reset = false;
        setCursor();
        return;
    }

    bounce();
    cursor = Vector2Add(cursor, Vector2Scale(velocity, GetFrameTime()));
    velocity = Vector2Add(velocity, Vector2Scale(acceleration, GetFrameTime()));

    if(outOfBounds())
    {
        advance();
    }
}

bool DrawHandler::WinAnimation::outOfBounds()
{
    return cursor.x < -100 || cursor.x > GetScreenWidth();
}

void DrawHandler::WinAnimation::bounce()
{
    if (cursor.y > GetScreenHeight() - 100)
    {
        velocity.y = velocity.y * -0.5f;
        cursor.y = GetScreenHeight() - 100;
    }
}

void DrawHandler::WinAnimation::setCursor()
{
    cursor = game -> foundations[index].GetPosition();
    float q = GetRandomValue(75, 100) / 100.0f;
    velocity.x = q * 200.0f;
    if (GetRandomValue(0, 1) > 0)
    {
        velocity.x *= -1;
    }
}

void DrawHandler::WinAnimation::advance()
{
    reset = true;
    index ++;
    index = index % 4;
}
