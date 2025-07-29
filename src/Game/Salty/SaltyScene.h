#ifndef SALTYSCENE_H
#define SALTYSCENE_H
// Will be included in user scripts, indicated by "Salty" being part of name

class Scene { 
    public:
        // NOTE: this should only be accessed by Engine, call Scene::Load to change
        static int sceneToLoad;

        static void Load(int sceneIdx);
};

#endif // SALTYSCENE_H