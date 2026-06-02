#pragma once
#include <raylib.h>
#include <map>
#include "../gamestate.h"

enum DropdownMenu
{
    DECK_CYCLES,
    CARDS_DEALT
};

class Game;

class DrawHandler
{
    public:
        DrawHandler(Game *aGame);
        Game *game;
        Texture2D cardSpriteSheet;

        std::map<DropdownMenu, bool> dropdownMenuState;

        void Draw(bool debugMode = false);

        void DrawGame(bool debugMode = false);
        void DrawMainMenu();
        void DrawOptionsMenu();
        void DrawPauseMenu();

        void GameStateButton(float baseY, int row, const char *text, GameState newState);
};