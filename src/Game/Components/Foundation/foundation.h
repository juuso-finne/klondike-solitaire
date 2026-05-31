#pragma once
#include "../interfaces.h"
#include "../../../Card/card.h"

class Game;

class Foundation: CardDestination, CardSource
{
    friend class Game;

    public:
        void Draw(Texture2D &spritesheet, bool debugMode = false);

    protected:

        Foundation (Vector2 aPosition, Game *aGame);

        Game *game;
        std::vector<Card> cards;

        Rectangle GetHitbox();
        bool Attach(std::vector<Card> newCards);

        Rectangle GetBoundaries();
        void Restore(std::vector<Card> returnedCards);
        std::vector<Card> DetachCards(std::size_t startIndex = 0);

        Vector2 position;
};