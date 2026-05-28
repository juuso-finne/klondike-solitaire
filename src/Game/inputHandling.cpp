#include "game.h"
#include <raymath.h>

void Game::clickHandler()
{
    for (FixedColumn &c: columns)
    {
        if(!c.cards.empty() && CheckCollisionPointRec(GetMousePosition(), c.GetBoundaries(settings.cardStagger)))
        {
            startDragging(c);
        }
    }
}

void Game::startDragging(FixedColumn &c)
{
    std::size_t startIndex = c.FindClickedIndex(settings.cardStagger);
    draggedColumn.position = c.FindCardPosition(settings.cardStagger, startIndex);
    std::vector<Card> cardsToDrag = c.DetachCards(settings.cardStagger, startIndex);

    if (cardsToDrag.empty()){
        return;
    }

    isDragging = true;
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
