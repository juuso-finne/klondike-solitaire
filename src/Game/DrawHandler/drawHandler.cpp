#include "drawHandler.h"
#include "../game.h"

DrawHandler::DrawHandler(Game *aGame)
{
    game = aGame;
    cardSpriteSheet = LoadTexture("assets/graphics/card_spritesheet.png");
}

void DrawHandler::Draw()
{
    DrawGame();
}

void DrawHandler::DrawGame()
{
    for (FixedColumn col : game->columns)
    {
        col.Draw(game->settings.cardStagger, cardSpriteSheet);
    }
}
