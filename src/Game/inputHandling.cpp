#include "game.h"
#include <raymath.h>

void Game::ClickHandler()
{
    for (FixedColumn &c: columns)
    {
        if(!c.cards.empty() && CheckCollisionPointRec(GetMousePosition(), c.GetBoundaries()))
        {
            std::size_t startIndex = c.FindClickedIndex();
            draggedColumn.position = c.FindCardPosition(startIndex);
            StartDragging(c, startIndex);
            return;
        }
    }
}

void Game::ReleaseHandler()
{
    if(!isDragging){
        return;
    }

    bool successfulAttach = false;

    for (FixedColumn &c: columns)
    {
        successfulAttach = Attach(c);
        if (successfulAttach)
        {
            break;
        }
    }

    if(!successfulAttach)
    {
        origin -> Restore(draggedColumn.cards);
    }

    isDragging = false;
    draggedColumn.cards.clear();
}

void Game::StartDragging(CardSource &src, std::size_t startIndex)
{
    std::vector<Card> cardsToDrag = src.DetachCards(startIndex);

    if (cardsToDrag.empty()){
        return;
    }

    origin = &src;
    isDragging = true;
    draggedColumn.cards = cardsToDrag;
}

bool Game::Attach(CardSource &dest)
{
    Rectangle hitbox = Card::GetHitBox(draggedColumn.position);

    if (!CheckCollisionRecs(hitbox, dest.GetHitbox()))
    {
        return false;
    }

    return dest.Attach(draggedColumn.cards);
}

void Game::UpdateDragging()
{
    if (isDragging)
    {
        draggedColumn.position = Vector2Add(draggedColumn.position, GetMouseDelta());
    }
}
