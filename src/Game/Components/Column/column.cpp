#include "column.h"
#include <raymath.h>

float Column::stagger = 25.0f;

Column::Column()
{
    cards = {};
    position = {0,0};
}

Column::Column(Vector2 aPosition, std::vector<Card> aCards)
{
    cards = aCards;
    position = aPosition;
}

void Column::Draw(Texture2D &spritesheet, bool debugMode)
{
    for (std::size_t i = 0; i < cards.size(); i++)
    {
        Vector2 offsetPosition = Vector2Add(position, {0, stagger * i});
        cards[i].Draw(offsetPosition, spritesheet, debugMode);
    }
}


FixedColumn::FixedColumn(Vector2 aPosition, std::vector<Card> aCards):Column(aPosition, aCards)
{}

Rectangle FixedColumn::GetBoundaries()
{
    if (cards.empty()){
        return {0,0,0,0};
    }

    Vector2 cardSize = Card::GetDimensions();

    float height = (cards.size() - 1) * stagger + cardSize.y;

    return {position.x, position.y, cardSize.x, height};
}

void FixedColumn::Draw(Texture2D &spritesheet, bool debugMode)
{
    if (cards.empty())
    {
        Vector2 cardSize = Card::GetDimensions();
        DrawRectangleRoundedLines({position.x, position.y, cardSize.x, cardSize.y}, 0.2f, 2, WHITE);
    } else
    {
        Column::Draw(spritesheet, debugMode);
    }

    if(debugMode)
    {
        DrawRectangleLinesEx(GetBoundaries(), 1.0f, RED);
    }
}

std::size_t FixedColumn::FindClickedIndex()
{
    for(std::size_t i = cards.size() - 1; i >= 0; i--)
    {
        if (GetMousePosition().y > position.y + i * stagger)
        {
            return i;
        }
    }

    return 0;
}

std::vector<Card> FixedColumn::DetachCards(std::size_t startIndex)
{
    if (!cards[startIndex].isFaceUp)
    {
        if (startIndex == cards.size() - 1)
        {
            cards[startIndex].TurnFaceUp();
        }
        return {};
    }

    std::vector<Card> output = {cards[startIndex]};

    for (std::size_t i = startIndex; i < cards.size() - 1; i++)
    {
        if(!cards[i].CheckAccommodation(cards[i + 1]))
        {
            return {};
        }

        output.push_back(cards[i + 1]);
    }

    for (auto i = cards.begin() + startIndex; i != cards.end();)
    {
        i = cards.erase(i);
    }

    return output;
}

Vector2 FixedColumn::FindCardPosition(std::size_t cardIndex)
{
    return Vector2Add(position, {0, cardIndex * stagger});
}

void FixedColumn::Restore(std::vector<Card> returnedCards)
{
    for (Card c : returnedCards)
    {
        cards.push_back(c);
    }

    returnedCards.clear();
}
