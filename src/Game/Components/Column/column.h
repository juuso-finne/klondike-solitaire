#pragma once
#include <vector>
#include <raylib.h>
#include "../../../Card/card.h"

class Game;

class Column
{
    friend class Game;
    public:
        void Draw(float stagger, Texture2D &spritesheet, bool debugMode = false);


    protected:
        Vector2 position;
        std::vector<Card> cards;
        Column();
        Column(Vector2 aPosition, std::vector<Card> aCards);

};

class FixedColumn: public Column
{
    friend class Game;
    public:
        void Draw(float stagger, Texture2D &spritesheet, bool debugMode = false);

    protected:
        FixedColumn(Vector2 aPosition, std::vector<Card> aCards);
        Rectangle GetBoundaries(float stagger);
        int FindClickedIndex(float stagger);
        std::vector<Card> DetatchToDrag(float stagger);
};