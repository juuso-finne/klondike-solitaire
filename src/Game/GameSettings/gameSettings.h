#pragma once

struct GameSettings
{
    GameSettings();

    float margin;

    int cardsToDeal;
    int deckCycleLimit;

    bool deckCyclingLimited;
};