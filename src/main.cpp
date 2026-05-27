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


/*     Deck d = Deck({0,0});
    Column col = Column({100, 200}, d.DealN(20)); */

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        game.Update();
        game.Draw();
        EndDrawing();
    }

    CloseWindow();
}