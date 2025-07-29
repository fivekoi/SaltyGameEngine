#ifndef SALTYSCENE_H
#define SALTYSCENE_H
// Will be included in user scripts, indicated by "Salty" being part of name

class Scene { 
    public:
        // NOTE: this should only be accessed by Engine, call Scene::Load to change
        static int sceneToLoad;
        // NOTE: this value should be Read-only for users, Engine will change it after LoadScene
        static int currentScene;

        static void Load(int sceneIdx);
};

#endif // SALTYSCENE_H