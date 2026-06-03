#pragma once

struct GameSettings
{
    GameSettings();

    float doubleClickThreshold;

    float margin;

    int cardsToDeal;
    int deckCycleLimit;

    bool deckCyclingUnlimited;
};