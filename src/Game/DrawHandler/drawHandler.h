#pragma once
#include <raylib.h>
#include <map>
#include <vector>
#include "../gamestate.h"
#include "../../Card/card.h"
#include <deque>

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
        ~DrawHandler();
        Game *game;
        Texture2D cardSpriteSheet;

        std::map<DropdownMenu, bool> dropdownMenuState;

        void Draw(bool debugMode = false);

        void DrawGame(bool debugMode = false);
        void DrawMainMenu();
        void DrawOptionsMenu();
        void DrawPauseMenu();

        void GameStateButton(float baseY, int row, const char *text, GameState newState);
        void ResetWinAnimation();

    private:
        class WinAnimation
        {
            public:
                WinAnimation(Game *aGame);
                void Draw(Texture2D &spritesheet, bool debugMode = false);
                void Update();
                void Reset();
            private:
                Game *game;
                bool uninitializedCursor;
                bool playing;

                Card currentCard;
                std::deque<std::pair<Card, Vector2>> trail;

                int index;
                Vector2 cursor;
                Vector2 velocity;
                Vector2 acceleration;

                bool outOfBounds();
                void bounce();
                void setCursor();
                void advance();
        };

        WinAnimation winAnimation;

};