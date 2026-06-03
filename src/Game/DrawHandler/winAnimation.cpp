#include "drawHandler.h"
#include <raymath.h>
#include "../game.h"

DrawHandler::WinAnimation::WinAnimation(Game *aGame): currentCard(Card(1, Suit::SPADES))
{
    game = aGame;
    Reset();
}

void DrawHandler::WinAnimation::Reset()
{
    index = 0;
    acceleration = {0, 500.0f};
    uninitializedCursor = true;
    playing = true;
    trail.clear();
}

void DrawHandler::WinAnimation::Draw(Texture2D &spritesheet, bool debugMode)
{
    for (Foundation &f : game -> foundations)
    {
        f.Draw(spritesheet);
    }

    for (std::pair<Card, Vector2> i : trail)
    {
        i.first.Draw(i.second, spritesheet);
    }
}

void DrawHandler::WinAnimation::Update()
{
    if(uninitializedCursor)
    {
        uninitializedCursor = false;
        setCursor();
        return;
    }

    bounce();
    cursor = Vector2Add(cursor, Vector2Scale(velocity, GetFrameTime()));
    velocity = Vector2Add(velocity, Vector2Scale(acceleration, GetFrameTime()));

    if(playing)
    {
        trail.push_back({currentCard, cursor});
    }

    if(trail.size() > 10000)
    {
        trail.pop_front();
    }

    if(outOfBounds())
    {
        advance();
    }
}

bool DrawHandler::WinAnimation::outOfBounds()
{
    float cardWidth = Card::GetDimensions().x;
    return cursor.x < -cardWidth || cursor.x > GetScreenWidth();
}

void DrawHandler::WinAnimation::bounce()
{
    float cardHeight = Card::GetDimensions().y;

    if (cursor.y > GetScreenHeight() - cardHeight)
    {
        velocity.y = velocity.y * -0.5f;
        cursor.y = GetScreenHeight() - cardHeight;
    }
}

void DrawHandler::WinAnimation::setCursor()
{
    cursor = game -> foundations[index].GetPosition();
    float q = GetRandomValue(75, 100) / 100.0f;
    velocity = {q * 200.0f, 0};
    if (GetRandomValue(0, 1) > 0)
    {
        velocity.x *= -1;
    }

    if (game -> foundations[index].cards.empty())
    {
        playing = false;
        return;
    }

    currentCard = game -> foundations[index].cards.back();
    game -> foundations[index].cards.pop_back();
}

void DrawHandler::WinAnimation::advance()
{
    uninitializedCursor = true;
    index ++;
    index = index % 4;
}
