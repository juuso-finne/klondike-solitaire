#include "game.h"

Game::Game(): drawHandler(this)
{
    for (int i = 0; i < 7 ; i++)
    {
        Vector2 cardSize = Card::GetDimensions();
        float x = GetScreenWidth() - (settings.margin + cardSize.x) * (7 - i);
        float y = cardSize.y + 2 * settings.margin;

        Column c = Column({x, y}, {});
        columns.push_back(c);
    }

    Reset();
}

void Game::Reset()
{
    deck = Deck();

    for (std::size_t i = 0; i < columns.size(); i++){
        Column *c = &columns[i];
        c -> cards = deck.DealN(i + 1);

        if (!c -> cards.empty())
        {
            c -> cards.back().TurnFaceUp();
        }
    }
}

void Game::Draw()
{
    drawHandler.Draw();
}
