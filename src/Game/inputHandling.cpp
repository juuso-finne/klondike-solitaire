#include "game.h"
#include <raymath.h>

void Game::clickHandler()
{
    for (FixedColumn &c: columns)
    {
        if(!c.cards.empty() && CheckCollisionPointRec(GetMousePosition(), c.GetBoundaries()))
        {
            std::size_t startIndex = c.FindClickedIndex();
            draggedColumn.position = c.FindCardPosition(startIndex);
            startDragging(c, startIndex);
        }
    }
}

void Game::startDragging(FixedColumn &c, std::size_t startIndex)
{
    std::vector<Card> cardsToDrag = c.DetachCards(startIndex);

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
