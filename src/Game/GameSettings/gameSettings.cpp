#include "gameSettings.h"

GameSettings::GameSettings()
{

    doubleClickThreshold = 0.5f;

    margin = 20.0f;

    cardsToDeal = 1;
    deckCycleLimit = 3;

    deckCyclingLimited = false;
}