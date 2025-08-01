#pragma once
#include "SaltyEngine.h"

class CoasterMini : public IScript {
private:
    // Coaster animation
    SF_ Transform* coaster;

    std::vector<glm::vec2> positions = {{-30, -89}, {270, -89}, {301, -176}, {349, -339}, {450, -413}, {496, -413},
                                        {620, -306}, {533, -226}, {452, -315}, {586, -411}, {766, -422}, {989, -335}};
    std::vector<float> rotations = {0, 0, -74.5, -74.5, 0, 0, 90, 180, 270, 355.5, 360, 415};
    std::vector<float> times = {1.5, 1, 0.4, 0.5, 0.2, 0.7, 0.9, 1, 0.7, 0.7, 2, 0.7};
    std::vector<glm::vec2> centerPoints;
    float timer = 0;
    int idx = 0;


    bool won = false;

public:
    // Initialization will be handled by engine (including that of SF_ variables)
    CoasterMini(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;
};