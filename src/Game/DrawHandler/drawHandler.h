#pragma once
#include <raylib.h>

enum GameState
{
    MAIN_MENU,
    OPTIONS_MENU,
    GAME
};

class Game;

class DrawHandler
{
    public:
        DrawHandler(Game *aGame);
        Game *game;
        Texture2D cardSpriteSheet;

        void Draw(bool debugMode = false);

        void DrawGame(bool debugMode = false);
        void DrawMainMenu();

        void GameStateButton(float y, const char *text, Game *game, GameState newState);
};