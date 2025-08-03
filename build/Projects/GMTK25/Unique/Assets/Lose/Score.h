#pragma once
#include "SaltyEngine.h"

class Score : public IScript {
private:

public:
    // Initialization will be handled by engine (including that of SF_ variables)
    Score(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;

    static int recentScore;
    static int highScore;
};