#pragma once
#include <raylib.h>
#include <vector>
#include "../../../Card/card.h"

class Deck{
    public:
        Deck();
        void Shuffle();
        bool IsEmpty();
        void Reset();
        Card DealOne();
        void Append(const std::vector<Card> &newCards);

        std::vector<Card> DealN(int n);
    private:
        std::vector<Card> cards;
        void Generate();
};