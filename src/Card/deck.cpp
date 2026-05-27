#include <algorithm>
#include <random>
#include <stdexcept>
#include "deck.h"

Deck::Deck()
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

void Deck::Append(const std::vector<Card> &newCards)
{
    for (Card c: newCards)
    {
        c.TurnFaceDown();
        cards.insert(cards.end(), c);
    }
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
