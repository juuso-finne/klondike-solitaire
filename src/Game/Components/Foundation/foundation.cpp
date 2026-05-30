#include "foundation.h"

void Foundation::Draw(Texture2D &spritesheet, bool debugMode)
{
    if (cards.empty())
    {
        Vector2 cardSize = Card::GetDimensions();
        DrawRectangleRoundedLines({position.x, position.y, cardSize.x, cardSize.y}, 0.2f, 2, WHITE);
    } else
    {
        cards.back().Draw(position, spritesheet, debugMode);
    }
}

Foundation::Foundation(Vector2 aPosition, Game *aGame)
{
    position = aPosition;
    game = aGame;
    cards = {};
}

Rectangle Foundation::GetHitbox()
{
        return Card::GetHitBox(position);
}

bool Foundation::Attach(std::vector<Card> newCards)
{
    if(newCards.size() != 1)
    {
        return false;
    }

    if (cards.empty() && newCards[0].GetRank() != 1)
    {
        return false;
    }

    if (!cards.empty())
    {
        if (cards.back().GetSuit() != newCards[0].GetSuit())
        {
            return false;
        }

        if (cards.back().GetRank() + 1 != newCards[0].GetRank())
        {
            return false;
        }

    }

    cards.push_back(newCards[0]);
    return true;
}
