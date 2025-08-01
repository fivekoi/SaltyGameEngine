#pragma once
#include "SaltyEngine.h"

class MicMini : public IScript {
private:
    SF_ Text* letter1;
    SF_ Text* letter2;
    SF_ Text* letter3;
    SF_ Text* letter4;

    std::vector<int> numbers = {4, 9, 1, 2, 5, 8, 6, 7, 0, 3};
    std::vector<int> numberKeys = {KEY_4, KEY_9, KEY_1, KEY_2, KEY_5, KEY_8, KEY_6, KEY_7, KEY_0, KEY_3};

    int correct;

    bool won = false;
public:
    // Initialization will be handled by engine (including that of SF_ variables)
    MicMini(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;
};