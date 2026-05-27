#include <raylib.h>
#include "Card/deck.h"
#include "Game/Components/Column/column.h"
#include "Game/game.h"

int main()
{
    constexpr int screenWidth = 1152;
    constexpr int screenHeight = 864;

    InitWindow(screenWidth, screenHeight, "Solitaire");
    Game game = Game();
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        game.Update();
        game.Draw();
    }

    CloseWindow();
}