#pragma once
#include <raylib.h>
#include <vector>
#include "../../../Card/card.h"

class Deck{
    public:
        Deck(Vector2 aPosition);
        void Shuffle();
        bool IsEmpty();
        void Reset();
        Card DealOne();
        std::vector<Card> DealN(int n);
        Rectangle GetBoundaries();
        void Append(const std::vector<Card> &newCards);
        void Draw(Texture2D &spritesheet, bool debugMode = false);

    private:
        std::vector<Card> cards;
        Vector2 position;
        void Generate();
};