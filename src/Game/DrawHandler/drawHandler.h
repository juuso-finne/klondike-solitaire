#pragma once
#include <raylib.h>

class Game;

class DrawHandler
{
    public:
        DrawHandler(Game *aGame);
        Game *game;
        Texture2D cardSpriteSheet;

        void Draw();

        void DrawGame();
};