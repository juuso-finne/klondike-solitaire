#include "game.h"

Game::Game(): drawHandler(this), waste(this), deck (Deck({settings.margin, settings.margin}))
{
    isDragging = false;
    draggedColumn = Column();

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
    UpdateDragging();

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        ClickHandler();
    }

    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
    {
        ReleaseHandler();
    }
}

void Game::Draw(bool debugMode)
{
    drawHandler.Draw(debugMode);
}

bool Game::CyclesLeft()
{
    return !settings.deckCyclingLimited || deckCyclesUsed < settings.deckCycleLimit;
}