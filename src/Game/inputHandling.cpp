#include "game.h"
#include <raymath.h>

void Game::clickHandler()
{
    for (FixedColumn &c: columns)
    {
        if(isDragging)
        {
            break;
        }

        if(!c.cards.empty() && CheckCollisionPointRec(GetMousePosition(), c.GetBoundaries()))
        {
            std::size_t startIndex = c.FindClickedIndex();
            draggedColumn.position = c.FindCardPosition(startIndex);
            startDragging(c, startIndex);
        }
    }
}

void Game::startDragging(CardSource &src, std::size_t startIndex)
{
    std::vector<Card> cardsToDrag = src.DetachCards(startIndex);

    if (cardsToDrag.empty()){
        return;
    }

    origin = &src;
    isDragging = true;
    draggedColumn.cards = cardsToDrag;
}

void Game::stopDragging()
{
    if(!isDragging){
        return;
    }

    origin -> Restore(draggedColumn.cards);
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
