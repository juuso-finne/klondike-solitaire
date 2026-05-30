#pragma once
#include <raylib.h>
#include "GameSettings/gameSettings.h"
#include "Components/Column/column.h"
#include "DrawHandler/drawHandler.h"
#include "Components/Deck/deck.h"
#include "Components/Waste/waste.h"

class Game
{
    public:
        Game();

        void Reset();
        void Update();
        void Draw(bool debugMode = false);

        void ClickHandler();
        void ReleaseHandler();

        GameSettings settings;
        DrawHandler drawHandler;

        std::vector<FixedColumn> columns;
        Waste waste;
        Deck deck;

        int deckCyclesUsed;
        bool isDragging;
        Column draggedColumn;

        bool CyclesLeft();

        void StartDragging(CardSource &c, std::size_t startIndex = 0);
        bool Attach(CardSource &src);
        void UpdateDragging();

        CardSource *origin;
};