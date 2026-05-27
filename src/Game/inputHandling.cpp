#include "game.h"

void Game::clickHandler()
{
    for (FixedColumn c: columns)
    {
        if(CheckCollisionPointRec(GetMousePosition(), c.GetBoundaries(settings.cardStagger)))
        {
        }
    }
}