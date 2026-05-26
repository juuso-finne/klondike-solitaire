#pragma once
#include <vector>
#include <raylib.h>
#include "../../../Card/card.h"

class Game;

class Column
{
    friend class Game;

    public:
    Column(Vector2 aPosition, std::vector<Card> aCards);
    void Draw(float stagger, Texture2D &spritesheet, bool debugMode = false);

    Vector2 position;
    std::vector<Card> cards;

};