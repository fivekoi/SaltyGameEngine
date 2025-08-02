#pragma once
#include "SaltyEngine.h"

class FruitMini : public IScript {
private:
    SF_ Text* inputText;
    
    // Will be set on start
    int randomFruit = 0;
    std::vector<std::vector<int>> fruitsKeys = {{KEY_B, KEY_A, KEY_N, KEY_A, KEY_N, KEY_A},  // BANANA
                                                {KEY_A, KEY_P, KEY_P, KEY_L, KEY_E},         // APPLE
                                                {KEY_O, KEY_R, KEY_A, KEY_N, KEY_G, KEY_E}}; // ORANGE
    std::vector<std::string> fruitStrings = {"BANANA", "APPLE", "ORANGE"};
    int currentLetter = 0;

    SF_ Entity* banana;
    SF_ Entity* orange;
    SF_ Entity* apple;

    // Will be set as flag to stop reading inputs, so little celebration animation can play
    bool won = false;
public:
    // Initialization will be handled by engine (including that of SF_ variables)
    FruitMini(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;

    void HideChildren(Entity* e);
};