#include <algorithm>
#include <random>
#include <stdexcept>
#include "deck.h"
#include <raymath.h>

Deck::Deck(Vector2 aPosition): position(aPosition)
{
    cards = std::vector<Card>{};
    Reset();
}


void Deck::Shuffle()
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(cards.begin(), cards.end(), g);
}

bool Deck::IsEmpty()
{
    return cards.empty();
}

void Deck::Reset(){
    Generate();
    Shuffle();
}

void Deck::Generate()
{

    cards.clear();

    std::vector<Suit> suits = {Suit::CLUBS, Suit::DIAMONDS, Suit::HEARTS, Suit::SPADES};

    for (Suit suit : suits){
        for(int rank = 1; rank < 14; rank++){
            cards.push_back(Card(rank, suit));
        }
    }
}

Card Deck::DealOne()
{
    if (cards.empty()){
        throw std::out_of_range("Attempting to deal a card from empty deck");
    }

    Card output = cards.back();
    cards.pop_back();
    return output;
}

std::vector<Card> Deck::DealN(int n)
{
    std::vector<Card> output{};
    for (int i = 0; i < n; i++){
        if (!cards.empty()){
            output.push_back(DealOne());
        } else{
            break;
        }
    }
    return output;
}

Rectangle Deck::GetBoundaries()
{
    Vector2 cardSize = Card::GetDimensions();
    return {position.x, position.y, cardSize.x, cardSize.y};
}

void Deck::Append(const std::vector<Card> &newCards)
{
    for (Card c: newCards)
    {
        c.TurnFaceDown();
        cards.insert(cards.begin(), c);
    }
}

void Deck::Draw(Texture2D &spritesheet, bool cyclesLeft, bool debugMode)
{
    Vector2 cardSize = Card::GetDimensions();
    Vector2 center = Vector2Add(position, Vector2Scale(cardSize, 0.5f));

    if (cards.empty())
    {
        Vector2 cardSize = Card::GetDimensions();
        DrawRectangleRoundedLines({position.x, position.y, cardSize.x, cardSize.y}, 0.2f, 2, WHITE);

        if(cyclesLeft)
        {
            DrawRing(center, 31.0f, 36.0f, 0, 360, 100, GREEN);
        } else
        {
            DrawCross(center, 50.0f, 5.0f);
        }


    } else
    {
        cards[0].Draw(position, spritesheet, debugMode);
    }
}

void Deck::DrawCross(Vector2 center, float size, float thickness)
{
    Vector2 upperLeft = Vector2AddValue(center, -size / 2);
    Vector2 lowerRight = Vector2AddValue(center, size / 2);
    Vector2 lowerLeft = Vector2Add(upperLeft, {0, size});
    Vector2 upperRight = Vector2Add(lowerRight, {0, -size});

    DrawLineEx(upperLeft, lowerRight, thickness, RED);
    DrawLineEx(lowerLeft, upperRight, thickness, RED);
}

