#include "card.h"
#include <stdexcept>
#include <raymath.h>

Card::Card(Vector2 aPosition, int aRank, Suit aSuit, bool isVisible)
{
    if(aRank < 1 || aRank > 13)
    {
        throw std::invalid_argument("Card.cpp: Card rank must be between 1 and 13 (incl.)");
    }

    spriteWidth = 75.0f;
    spriteHeight = 112.0f;

    const float scaling = 1.5f;

    width = spriteWidth * scaling;
    height = spriteHeight * scaling;

    position = aPosition;

    rank = aRank;
    suit = aSuit;
    suitIndex = static_cast<int>(aSuit);

    isFaceUp = isVisible;
}

void Card::TurnFaceUp()
{
    isFaceUp = true;
}

void Card::TurnFaceDown()
{
    isFaceUp = false;
}

void Card::Draw(const Texture2D &spritesheet, bool debugMode)
{
    float x_offset = (isFaceUp ? (float)(rank - 1) : 13.0) * spriteWidth;
    float y_offset = (isFaceUp ? (float)suitIndex : 3.0) * spriteWidth;

    Rectangle source = {x_offset, y_offset, spriteWidth, spriteHeight};
    Rectangle dest = {position.x, position.y, width, height};

    DrawTexturePro(spritesheet, source, dest, {0,0}, 0, WHITE);

    if(debugMode)
    {
        DrawRectangleRec(this->GetHitBox(), GREEN);
    }
}

Suit Card::GetSuit()
{
    return suit;
}

int Card::GetRank()
{
    return rank;
}

int Card::GetSuitIndex()
{
    return suitIndex;
}

Rectangle Card::GetBoundaries() const
{
    return {position.x, position.y, width, height};
}

Rectangle Card::GetHitBox() const
{
    float x = position.x + width / 4.0f;
    float y = position.y + height / 4.0f;
    return {x, y, width / 2.0F, height / 2.0f};
}

bool Card::CheckCollision(const Card &other)
{
    return CheckCollisionRecs(this->GetHitBox(), other.GetHitBox());
}

// Whether or not other card can be placed on top of this card
bool Card::CheckAccommodation(const Card &other)
{
    bool isOtherBlack = other.suit == Suit::CLUBS || other.suit == Suit::SPADES;
    bool isThisBlack = suit == Suit::CLUBS || suit == Suit::SPADES;

    if(isOtherBlack == isThisBlack){
        return false;
    }

    return other.rank + 1 == rank;
}
