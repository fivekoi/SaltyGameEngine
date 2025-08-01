#pragma once
#include "SaltyEngine.h"

class LoopholeController : public IScript {
private:
    SF_ Text* mainText;
    SF_ Transform* textTransform;

    std::vector<std::string> truths = {"a triangle has 3 sides", "2 + 2 = 4", "4 + 4 = 8", "a square has 4 sides", "fish live in water",
                                       "(most) birds can fly", "fire is hot", "ice is cold"};
    std::vector<std::string> lies = {"a triangle has 4 sides", "a square has 3 sides", "2 + 2 = 8", "(most) birds live in water",
                                     "fish can fly", "fire is cold", "ice is hot"};

    std::vector<std::string> nextThree;
    int statementIndex = 2;
    int falseIndex = -1;
    int pushedTrue = 0;

    float timer = 0;

    bool won = false;

public:
    // Initialization will be handled by engine (including that of SF_ variables)
    LoopholeController(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;

    // Generates which of the next 3 will be false
    void GenerateStatements();
};