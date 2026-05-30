#include "waste.h"
#include "../../game.h"

Waste::Waste(Game *aGame): game(aGame)
{
    float x = Card::GetDimensions().x + 2 * game -> settings.margin;
    float y = game -> settings.margin;

    position = {x, y};
    cards = {};
}

void Waste::Draw(Texture2D &spritesheet, bool debugMode)
{
    if (!cards.empty())
    {
        cards.back().Draw(position, spritesheet, debugMode);
    }
}

void Waste::Deal()
{
    if(!game -> CyclesLeft())
    {
        return;
    }

    if (game -> deck.IsEmpty())
    {
        game -> deck.Append(cards);
        cards.clear();
        return;
    }

    for (int i = 0; i < game->settings.cardsToDeal; i++)
    {
        Card c = game -> deck.DealOne();
        c.TurnFaceUp();
        cards.push_back(c);

        if (game -> deck.IsEmpty())
        {
            game -> deckCyclesUsed++;
            return;
        }
    }
}

Rectangle Waste::GetBoundaries()
{
    Vector2 cardSize = Card::GetDimensions();
    return {position.x, position.y, cardSize.x, cardSize.y};
}

void Waste::Restore(std::vector<Card> returnedCards)
{
    cards.push_back(returnedCards[0]);
}

std::vector<Card> Waste::DetachCards(std::size_t startIndex)
{
    std::vector<Card> output = {};

    if (!cards.empty())
    {
        output.push_back(cards.back());
        cards.pop_back();
    }

    return output;
}
