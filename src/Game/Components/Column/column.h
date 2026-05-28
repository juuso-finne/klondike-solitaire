#pragma once
#include <vector>
#include <raylib.h>
#include "../../../Card/card.h"

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

class FixedColumn: public Column
{
    friend class Game;
    public:
        void Draw(Texture2D &spritesheet, bool debugMode = false);

    protected:
        FixedColumn(Vector2 aPosition, std::vector<Card> aCards);
        Rectangle GetBoundaries();
        std::size_t FindClickedIndex();
        std::vector<Card> DetachCards(std::size_t startIndex);
        Vector2 FindCardPosition(std::size_t cardIndex);
};