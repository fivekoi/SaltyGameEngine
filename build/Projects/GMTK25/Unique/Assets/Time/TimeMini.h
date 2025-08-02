#pragma once
#include "SaltyEngine.h"

class TimeMini : public IScript {
private:
    SF_ Sprite* walkSprite;
    SF_ Transform* walkTransform;
    float walkTimer = 0;

    SF_ string walk1;
    SF_ string walk2;
    SF_ string walk3;
    SF_ string walk4;
    std::vector<string> walkFrames;
    int walkIndex;

    int phase = 0;

    SF_ Text* goalText;
    std::vector<int> goalIdxs;
    std::vector<string> letters = {"Q", "W", "E", "T", "A", "S", "D", "F", "Z", "C", "V"};
    std::vector<int> letterKeys = {KEY_Q, KEY_W, KEY_E, KEY_T, KEY_A, KEY_S, KEY_D, KEY_F, KEY_Z, KEY_C, KEY_V};
    int textRevealed = 0;

    std::vector<int> letterPositions = {90, 368, 655};

    bool won = false;
    SF_ Transform* check;
    float winTimer = 0.8;
public:
    // Initialization will be handled by engine (including that of SF_ variables)
    TimeMini(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;
};