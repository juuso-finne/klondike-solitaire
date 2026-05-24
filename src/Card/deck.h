#pragma once
#include <raylib.h>
#include <vector>
#include "card.h"

class Deck{
    public:
        Deck(Vector2 position);
        void Shuffle();
        bool IsEmpty();
        void Reset();
        Card DealOne();
        void Append(const std::vector<Card> &newCards);

        std::vector<Card> DealN(int n);
    private:
        std::vector<Card> cards;
        Vector2 position;
        void Generate();
};