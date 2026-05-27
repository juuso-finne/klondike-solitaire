#pragma once
#include <raylib.h>
#include "GameSettings/gameSettings.h"
#include "Components/Column/column.h"
#include "DrawHandler/drawHandler.h"
#include "../Card/deck.h"

class Game
{
    public:
        Game();

        void Reset();
        void Draw();

        GameSettings settings;
        DrawHandler drawHandler;

        Deck deck;
        std::vector<Column> columns;
};