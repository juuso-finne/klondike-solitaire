#pragma once
#include "../cardSource.h"
#include <vector>
#include "../../../Card/card.h"
#include <raylib.h>

class Game;

class Waste: CardSource
{
    friend class Game;
    public:
        Waste(Game *aGame);

        Game *game;
        Vector2 position;
        std::vector<Card> cards;

        void Draw(Texture2D &spritesheet, bool debugMode = false);
        void Deal();

        Rectangle GetBoundaries();
        void Restore(std::vector<Card> returnedCards);
        std::vector<Card> DetachCards(std::size_t startIndex = 0);
        Rectangle GetHitbox();
        bool Attach(std::vector<Card> newCards);
};