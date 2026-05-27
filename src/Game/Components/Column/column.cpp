#include "column.h"
#include <raymath.h>

Column::Column(Vector2 aPosition, std::vector<Card> aCards)
{
    cards = aCards;
    position = aPosition;
}

void Column::Draw(float stagger, Texture2D &spritesheet, bool debugMode)
{
    for (std::size_t i = 0; i < cards.size(); i++)
    {
        Vector2 offsetPosition = Vector2Add(position, {0, stagger * i});
        cards[i].Draw(offsetPosition, spritesheet, debugMode);
    }
}

FixedColumn::FixedColumn(Vector2 aPosition, std::vector<Card> aCards):Column(aPosition, aCards)
{}

void FixedColumn::Draw(float stagger, Texture2D &spritesheet, bool debugMode)
{
    if (cards.empty())
    {
        Vector2 cardSize = Card::GetDimensions();
        DrawRectangleRoundedLines({position.x, position.y, cardSize.x, cardSize.y}, 0.2f, 2, WHITE);
    } else
    {
        Column::Draw(stagger, spritesheet, debugMode);
    }
}
