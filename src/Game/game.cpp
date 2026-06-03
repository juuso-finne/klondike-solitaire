#include "game.h"
#include <raymath.h>

Game::Game(): drawHandler(this), waste(this), deck (Deck({settings.margin, settings.margin}))
{
    state = MAIN_MENU;

    for (int i = 0; i < 7 ; i++)
    {
        Vector2 cardSize = Card::GetDimensions();
        float x = GetScreenWidth() - (settings.margin + cardSize.x) * (7 - i);
        float y = cardSize.y + 2 * settings.margin;

        FixedColumn c = FixedColumn({x, y}, {});
        columns.push_back(c);
    }

    for (int i = 0; i < 4; i++)
    {
        Vector2 cardSize = Card::GetDimensions();

        float x = GetScreenWidth() - (settings.margin + cardSize.x) * (4 - i);
        float y = settings.margin;

        Foundation f = Foundation({x, y}, this);
        foundations.push_back(f);
    }

    Reset();
}

void Game::Reset()
{
    deck.Reset();
    origin = nullptr;
    deckCyclesUsed = 0;
    isDragging = false;
    doubleClickTimer = 0.0f;
    draggedColumn = Column();
    waste.cards.clear();

    for (std::size_t i = 0; i < columns.size(); i++){
        FixedColumn *c = &columns[i];
        c -> cards = deck.DealN(i + 1);

        if (!c -> cards.empty())
        {
            c -> cards.back().TurnFaceUp();
        }
    }

    for (Foundation &f : foundations)
    {
        f.cards.clear();
    }
}

void Game::Update()
{
    CheckWinState();

    switch (state)
    {
    case GAME:
        break;

    case WIN:
        break;

    case HALT:
        CloseWindow();
        exit(0);
        return;

    case RESET:
        Reset();
        state = GAME;
        return;

    case PAUSE:
        state = IsKeyPressed(KEY_ESCAPE) ? GAME : PAUSE;
        return;

    case OPTIONS_MENU:
        state = IsKeyPressed(KEY_ESCAPE) ? MAIN_MENU : OPTIONS_MENU;
        return;

    default:
        return;
    }

    UpdateDragging();
    doubleClickTimer -= GetFrameTime();
    doubleClickTimer = Clamp(doubleClickTimer, 0.0f, settings.doubleClickThreshold);

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        ClickHandler();
    }

    if(!IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        ReleaseHandler();
    }

    if(IsKeyPressed(KEY_ESCAPE) && state == GAME)
    {
        state = PAUSE;
    }
}

void Game::Draw(bool debugMode)
{
    drawHandler.Draw(debugMode);
}

bool Game::CyclesLeft()
{
    return settings.deckCyclingUnlimited || deckCyclesUsed < settings.deckCycleLimit;
}

void Game::CheckWinState()
{
    if (state != GAME)
    {
        return;
    }

    for(Foundation &f: foundations)
    {
        if (f.cards.empty())
        {
            return;
        }

        if(f.cards.back().GetRank() != 13)
        {
            return;
        }
    }

    drawHandler.ResetWinAnimation();
    state = WIN;
}