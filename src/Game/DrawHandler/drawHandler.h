#pragma once
#include <raylib.h>
#include <map>

enum GameState
{
    MAIN_MENU,
    OPTIONS_MENU,
    GAME
};

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

        void GameStateButton(float baseY, int row, const char *text, Game *game, GameState newState);
};