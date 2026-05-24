#pragma once
#include<raylib.h>

enum class Suit
{
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

class Card
{
    public:
        Card(int aRank, Suit aSuit, bool aIsVisible = false);

        void TurnFaceUp();
        void TurnFaceDown();

        void Draw(Vector2 position, const Texture2D &spritesheet, bool debugMode = false);

        Suit GetSuit();
        int GetRank();
        int GetSuitIndex();

        Vector2 GetDimensions() const;
        Rectangle GetHitBox(Vector2 position) const;

        bool CheckAccommodation(const Card &other);

        bool isFaceUp;

    protected:
        int rank;
        int suitIndex;

        Suit suit;

        float spriteWidth;
        float spriteHeight;

        float width;
        float height;
};