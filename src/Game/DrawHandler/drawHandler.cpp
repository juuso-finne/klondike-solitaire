#include "drawHandler.h"
#include "../game.h"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

DrawHandler::DrawHandler(Game *aGame)
{
    game = aGame;
    cardSpriteSheet = LoadTexture("assets/graphics/card_spritesheet.png");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
}

void DrawHandler::Draw(bool debugMode)
{
    BeginDrawing();
    ClearBackground(BLACK);
    switch (game -> state)
    {
        case MAIN_MENU:
            DrawMainMenu();
            break;

        case GAME:
            DrawGame(debugMode);
            break;

        default:
            return;
    }
    EndDrawing();
}

void DrawHandler::DrawGame(bool debugMode)
{
    game -> waste.Draw(cardSpriteSheet, debugMode);
    game -> deck.Draw(cardSpriteSheet, game -> CyclesLeft(), debugMode);

    for (Foundation f : game->foundations)
    {
        f.Draw(cardSpriteSheet, debugMode);
    }

    for (FixedColumn col : game->columns)
    {
        col.Draw(cardSpriteSheet, debugMode);
    }

    if(game->isDragging)
    {
        game->draggedColumn.Draw(cardSpriteSheet, debugMode);
    }
}

void DrawHandler::DrawMainMenu()
{
    float baseY = 100.0f;
    float margin = 20.0f;

    GameStateButton(baseY, "Start game", game, GAME);
}

void DrawHandler::GameStateButton(float y, const char *text, Game *game, GameState newState)
{
    Vector2 size = {200, 50};
    float x = GetScreenWidth() / 2 - size.x / 2;

    if(GuiButton({x, y, size.x, size.y}, text))
    {
        game -> state = newState;
    }
}