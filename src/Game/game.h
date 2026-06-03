#pragma once
#include <raylib.h>
#include "GameSettings/gameSettings.h"
#include "Components/Column/column.h"
#include "DrawHandler/drawHandler.h"
#include "Components/Deck/deck.h"
#include "Components/Waste/waste.h"
#include "Components/Foundation/foundation.h"

class Game
{
    public:
        Game();
        GameState state;

        void Reset();
        void Update();
        void Draw(bool debugMode = false);

        void ClickHandler();
        void DoubleClickHandler();
        void ReleaseHandler();

        GameSettings settings;
        DrawHandler drawHandler;

        std::vector<FixedColumn> columns;
        std::vector<Foundation> foundations;
        Waste waste;
        Deck deck;

        float doubleClickTimer;

        int deckCyclesUsed;
        bool isDragging;
        Column draggedColumn;

        void CheckWinState();

        bool CyclesLeft();

        void StartDragging(CardSource &c, std::size_t startIndex = 0);
        bool Attach(CardDestination &src);
        void UpdateDragging();

        CardSource *origin;
};