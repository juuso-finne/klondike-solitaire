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
        Card(Vector2 aPosition, int aRank, Suit aSuit, bool aIsVisible = false);

        void TurnFaceUp();
        void TurnFaceDown();

        void Draw(const Texture2D &spritesheet, bool debugMode = false);

        Suit GetSuit();
        int GetRank();
        int GetSuitIndex();

        Rectangle GetBoundaries() const;
        Rectangle GetHitBox() const;

        bool CheckCollision(const Card &other);
        bool CheckAccommodation(const Card &other);

        bool isFaceUp;

    protected:
        int rank;
        int suitIndex;

        Suit suit;
        Vector2 position;

        float spriteWidth;
        float spriteHeight;

        float width;
        float height;
};