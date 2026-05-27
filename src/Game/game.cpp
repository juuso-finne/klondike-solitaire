#include "game.h"

Game::Game(): drawHandler(this)
{
    for (int i = 0; i < 7; i++)
    {
        float x = 50 + i * 100;

        Column c = Column({x, 50}, {});
        columns.push_back(c);
    }

    Reset();
}

void Game::Reset()
{
    deck = Deck();

    for (int i = 0; i < 7; i++){
        Column *c = &columns[i];

        c -> cards = deck.DealN(i + 1);
    }
}

void Game::Draw()
{
    drawHandler.Draw();
}
