#pragma once
#include <raylib.h>

class CardSource
{
    virtual Rectangle GetBoundaries() = 0;
    virtual void Restore() = 0;
    virtual std::vector<Card> DetachCards(std::size_t startIndex = 0) = 0;
};