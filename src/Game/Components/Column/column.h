#pragma once
#include <vector>
#include <raylib.h>
#include "../../../Card/card.h"
#include "../cardSource.h"

class Game;

class Column
{
    friend class Game;
    public:
        void Draw(Texture2D &spritesheet, bool debugMode = false);


    protected:
        static float stagger;

        Vector2 position;
        std::vector<Card> cards;
        Column();
        Column(Vector2 aPosition, std::vector<Card> aCards);

};

class FixedColumn: Column, CardSource
{
    friend class Game;
    public:
        void Draw(Texture2D &spritesheet, bool debugMode = false);

    protected:
        FixedColumn(Vector2 aPosition, std::vector<Card> aCards);
        std::size_t FindClickedIndex();
        Vector2 FindCardPosition(std::size_t cardIndex);

        std::vector<Card> DetachCards(std::size_t startIndex = 0);
        Rectangle GetBoundaries();
        Rectangle GetHitbox();

        bool Attach(std::vector<Card> newCards);
        void Restore(std::vector<Card> returnedCards);
};