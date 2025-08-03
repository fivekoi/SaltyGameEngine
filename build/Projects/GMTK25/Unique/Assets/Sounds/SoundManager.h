#pragma once
#include "SaltyEngine.h"

class SoundManager : public IScript {
private:
    static bool loaded;

public:
    // Initialization will be handled by engine (including that of SF_ variables)
    SoundManager(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;

    static Sound drum1;
    static Sound drum2;
    static Sound music;
    static Sound cereal;
    static Sound coaster;
    static Sound lose;
    static Sound micfeedback;
    static Sound rope;
    static Sound ticktock;
    static Sound ticktockrev;
    static Sound typing;
    static Sound winding;
    static Sound wrong;
    static Sound title;
};