#pragma once
#include <raylib.h>
#include <vector>

class Card;

class CardSource
{
    public:
        virtual Rectangle GetBoundaries() = 0;
        virtual void Restore(std::vector<Card> returnedCards) = 0;
        virtual std::vector<Card> DetachCards(std::size_t startIndex = 0) = 0;
};

class CardDestination
{
    public:
        virtual Rectangle GetHitbox() = 0;
        virtual bool Attach(std::vector<Card> newCards) = 0;
};