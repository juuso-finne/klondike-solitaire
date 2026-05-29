#pragma once

struct GameSettings
{
    GameSettings();

    float margin;

    int cardsToDeal;
    int deckPassLimit;

    bool deckPassLimited;
};