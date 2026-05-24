#include <raylib.h>
#include "Card/card.h"

int main()
{
    constexpr int screenWidth = 1024;
    constexpr int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Solitaire");
    Texture2D card_sprite_sheet = LoadTexture("assets/graphics/card_spritesheet.png");
    SetTargetFPS(60);

    Card c = Card({50, 50}, 4, Suit::HEARTS, true);
    Card c2 = Card({50, 150}, 4, Suit::HEARTS, true);
    bool collision = c.CheckCollision(c2);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        c.Draw(card_sprite_sheet, true);
        c2.Draw(card_sprite_sheet, true);
        DrawCircle(300, 100, 20, (collision ? RED : GREEN));
        EndDrawing();
    }

    CloseWindow();
}