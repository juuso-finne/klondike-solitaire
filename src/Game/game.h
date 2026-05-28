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
        void Update();
        void Draw(bool debugMode = false);

        void clickHandler();

        GameSettings settings;
        DrawHandler drawHandler;

        Deck deck;
        std::vector<FixedColumn> columns;

        bool isDragging;
        Column draggedColumn;

        void startDragging(Column c);
        void stopDragging();
        void updateDragging();
};