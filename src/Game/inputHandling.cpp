#include "game.h"
#include <raymath.h>

void Game::clickHandler()
{
    for (FixedColumn c: columns)
    {
        if(CheckCollisionPointRec(GetMousePosition(), c.GetBoundaries(settings.cardStagger)))
        {
            startDragging(c);
        }
    }
}

void Game::startDragging(FixedColumn c)
{
    isDragging = true;
    draggedColumn = c;
}

void Game::stopDragging()
{
    isDragging = false;
    draggedColumn.cards.clear();
}

void Game::updateDragging()
{
    if (isDragging)
    {
        draggedColumn.position = Vector2Add(draggedColumn.position, GetMouseDelta());
    }
}
