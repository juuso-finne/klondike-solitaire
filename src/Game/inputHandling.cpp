#include "game.h"
#include <raymath.h>

void Game::clickHandler()
{
    for (FixedColumn &c: columns)
    {
        if(CheckCollisionPointRec(GetMousePosition(), c.GetBoundaries(settings.cardStagger)))
        {
            startDragging(c);
        }
    }
}

void Game::startDragging(FixedColumn &c)
{
    std::vector<Card> cardsToDrag = c.DetatchToDrag(settings.cardStagger);
    if (cardsToDrag.empty()){
        return;
    }

    isDragging = true;
    draggedColumn.position = Vector2Add(c.position, {0, ((float)c.cards.size() - cardsToDrag.size()) * settings.cardStagger});
    draggedColumn.cards = cardsToDrag;
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
