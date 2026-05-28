#include "drawHandler.h"
#include "../game.h"

DrawHandler::DrawHandler(Game *aGame)
{
    game = aGame;
    cardSpriteSheet = LoadTexture("assets/graphics/card_spritesheet.png");
}

void DrawHandler::Draw(bool debugMode)
{
    BeginDrawing();
    ClearBackground(BLACK);
    DrawGame(debugMode);
    EndDrawing();
}

void DrawHandler::DrawGame(bool debugMode)
{

    for (FixedColumn col : game->columns)
    {
        col.Draw(cardSpriteSheet, debugMode);
    }

    if(game->isDragging)
    {
        game->draggedColumn.Draw(cardSpriteSheet, debugMode);
    }
}
