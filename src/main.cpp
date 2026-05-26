#include <raylib.h>
#include "Card/deck.h"
#include "Game/Components/Column/column.h"

int main()
{
    constexpr int screenWidth = 1152;
    constexpr int screenHeight = 864;

    InitWindow(screenWidth, screenHeight, "Solitaire");
    Texture2D card_sprite_sheet = LoadTexture("assets/graphics/card_spritesheet.png");
    SetTargetFPS(60);


    Deck d = Deck({0,0});
    Column col = Column({100, 200}, d.DealN(20));
    Rectangle r = {0,0,0,0};


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        col.Draw(25, card_sprite_sheet);
        EndDrawing();
    }

    CloseWindow();
}