#include <raylib.h>
#include "Card/deck.h"

int main()
{
    constexpr int screenWidth = 1024;
    constexpr int screenHeight = 768;

    InitWindow(screenWidth, screenHeight, "Solitaire");
    Texture2D card_sprite_sheet = LoadTexture("assets/graphics/card_spritesheet.png");
    SetTargetFPS(60);



    Card c = Card(4, Suit::HEARTS, true);
    Card c2 = Card(1, Suit::SPADES, true);
    //bool collision = c.CheckCollision(c2);


    Deck d = Deck({100, 100});
    while(!d.IsEmpty())
    {
        d.DealOne();
    }

    d.Append({c, c2});

    std::vector<Card> discard = {};

    while(!d.IsEmpty())
    {
        Card newCard = d.DealOne();
        newCard.TurnFaceUp();
        discard.push_back(newCard);

    }

    while (!WindowShouldClose())
    {
        float offset = 0;
        BeginDrawing();
        ClearBackground(BLACK);

        for (Card card: discard){
            Vector2 pos = {50 + offset, 50.0f};
            card.Draw(pos, card_sprite_sheet);
            offset += 25;
        }


        /*
        c.Draw(card_sprite_sheet, true);
        c2.Draw(card_sprite_sheet, true);
        DrawCircle(300, 100, 20, (collision ? RED : GREEN));
         */
        EndDrawing();
    }

    CloseWindow();
}