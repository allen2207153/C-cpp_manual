#pragma once
#include "Scene.h"

// �������V�[���N���X
class TitleScene : public Scene {
public:
    TitleScene(class Game* game);
    ~TitleScene();
    void Start() override;
    void Update(float deltaTime) override;
    void ProcessInput(const Uint8* state) override;
    std::string const GetSceneName() override;

private:
    class Actor* mStartMsg; // �J�n���b�Z�[�W

};