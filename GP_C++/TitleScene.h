#pragma once
#include "Scene.h"

// 初期化シーンクラス
class TitleScene : public Scene {
public:
    TitleScene(class Game* game);
    ~TitleScene();
    void Start() override;
    void Update(float deltaTime) override;
    void ProcessInput(const Uint8* state) override;
    std::string const GetSceneName() override;

private:
    class Actor* mStartMsg; // 開始メッセージ

};