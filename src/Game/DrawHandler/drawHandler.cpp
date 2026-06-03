#include "drawHandler.h"
#include "../game.h"
#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

DrawHandler::DrawHandler(Game *aGame): winAnimation(WinAnimation(aGame))
{
    game = aGame;
    cardSpriteSheet = LoadTexture("assets/graphics/card_spritesheet.png");
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
    dropdownMenuState = {{DECK_CYCLES, false}, {CARDS_DEALT, false}};
}

DrawHandler::~DrawHandler()
{
    UnloadTexture(cardSpriteSheet);
}

void DrawHandler::Draw(bool debugMode)
{
    BeginDrawing();
    ClearBackground(DARKGREEN);

    switch (game -> state)
    {
        case MAIN_MENU:
            DrawMainMenu();
            break;

        case OPTIONS_MENU:
            DrawOptionsMenu();
            break;

        case GAME:
            DrawGame(debugMode);
            break;

        case PAUSE:
            DrawPauseMenu();
            break;

        case WIN:
            winAnimation.Update();
            winAnimation.Draw(cardSpriteSheet);
            break;

        default:
            break;;
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
    GameStateButton(300.0f, 0, "Start game", RESET);
    GameStateButton(300.0f, 1, "Options", OPTIONS_MENU);
    GameStateButton(300.0f, 2, "Exit", HALT);
}

void DrawHandler::DrawOptionsMenu()
{

    float baseX = GetScreenWidth() * 0.4f;
    float indent = 25.0f;

    float baseY = GetScreenHeight() * 0.25f;
    float rowSpacing = 45.0f;

    int cycleLimitIndex = game -> settings.deckCycleLimit == 1 ? 0 : 1;
    DrawText("Max. deck passes:", baseX, baseY, 24, WHITE);
    GuiCheckBox({baseX + indent, baseY + rowSpacing, 25, 25}, "Unlimited", &(game -> settings.deckCyclingUnlimited));

    if (game -> settings.deckCyclingUnlimited)
    {
        GuiSetState(STATE_DISABLED);
    }

    if (GuiDropdownBox({baseX + indent, baseY + rowSpacing * 2, 100, 25}, "1;3", &cycleLimitIndex, dropdownMenuState[DECK_CYCLES]))
    {
        dropdownMenuState[DECK_CYCLES] = !dropdownMenuState[DECK_CYCLES];
    }
    game -> settings.deckCycleLimit = cycleLimitIndex == 0 ? 1 : 3;

    GuiSetState(STATE_NORMAL);

    int cardsDealtIndex = game -> settings.cardsToDeal == 1 ? 0 : 1;
    DrawText("Cards dealt:", baseX, baseY + rowSpacing * 4, 24, WHITE);

    if(GuiDropdownBox({baseX + indent, baseY + rowSpacing * 5, 100, 25}, "1;3", &cardsDealtIndex, dropdownMenuState[CARDS_DEALT]))
    {
        dropdownMenuState[CARDS_DEALT] = !dropdownMenuState[CARDS_DEALT];
    }
    game -> settings.cardsToDeal = cardsDealtIndex == 0 ? 1 : 3;

    GameStateButton(baseY + rowSpacing * 7, 0, "Back", MAIN_MENU);
}

void DrawHandler::DrawPauseMenu()
{
    GameStateButton(300.0f, 0, "Continue", GAME);
    GameStateButton(300.0f, 2, "New game", RESET);
    GameStateButton(300.0f, 3, "Exit to menu", MAIN_MENU);
    GameStateButton(300.0f, 4, "Exit", HALT);
}


void DrawHandler::GameStateButton(float baseY, int row, const char *text, GameState newState)
{
    Vector2 size = {200, 50};
    float rowSpacing = 20.0f;

    float x = GetScreenWidth() / 2 - size.x / 2;
    float y = baseY + row * (rowSpacing + size.y);

    if(GuiButton({x, y, size.x, size.y}, text))
    {
        game -> state = newState;
    }
}

void DrawHandler::ResetWinAnimation()
{
    winAnimation.Reset();
}
