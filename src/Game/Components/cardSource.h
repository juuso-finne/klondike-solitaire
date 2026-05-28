#pragma once
#include <raylib.h>

class CardSource
{
    public:
        virtual Rectangle GetBoundaries() = 0;
        virtual void Restore(std::vector<Card> returnedCards) = 0;
        virtual std::vector<Card> DetachCards(std::size_t startIndex = 0) = 0;
        virtual Rectangle GetHitbox() = 0;
        virtual bool Attach(std::vector<Card> newCards) = 0;
    };