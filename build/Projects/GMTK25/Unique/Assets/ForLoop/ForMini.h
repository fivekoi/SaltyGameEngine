#pragma once
#include "SaltyEngine.h"

class ForMini : public IScript {
private:
    SF_ Text* forText;

    SF_ Text* inputText;

    // Will be set on start
    std::vector<int> values;
    std::string valueString;

    std::vector<int> numberKeys = {KEY_0, KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9};
    int currentNumber = 0;

    // Will be set as flag to stop reading inputs, so little celebration animation can play
    bool won = false;
    SF_ Transform* check;
    float winTimer = 0.8;
public:
    // Initialization will be handled by engine (including that of SF_ variables)
    ForMini(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;
};