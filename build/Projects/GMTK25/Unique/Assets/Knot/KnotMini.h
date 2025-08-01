#pragma once
#include "SaltyEngine.h"

class KnotMini : public IScript {
private:
    SF_ Text* leftLetterText;
    SF_ Transform* leftLetterTransform;
    SF_ Text* rightLetterText;
    SF_ Transform* rightLetterTransform;

    std::vector<int> leftKeys = {KEY_Q, KEY_W, KEY_E, KEY_R, KEY_A, KEY_S, KEY_D};
    std::vector<std::string> leftKeyLetters = {"Q", "W", "E", "R", "A", "S", "D"}; 
    std::vector<int> rightKeys = {KEY_U, KEY_I, KEY_O, KEY_P, KEY_J, KEY_K, KEY_L};
    std::vector<std::string> rightKeyLetters = {"U", "I", "O", "P", "J", "K", "L"};

    int left = -1;
    int right = -1;

    int leftPresses = 0;
    int rightPresses = 0;

    bool won = false;
    
public:
    // Initialization will be handled by engine (including that of SF_ variables)
    KnotMini(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;
};