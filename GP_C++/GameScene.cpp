#include "GameScene.h"
#include "EndScene.h"
#include "Game.h"
#include "Ship.h"
#include "Math.h"

GameScene::GameScene(class Game* game)
	:Scene(game)
{

}

GameScene::~GameScene()
{

}

void GameScene::Start()
{

}

void GameScene::Update(float deltaTime)
{

}

void GameScene::ProcessInput(const Uint8* state)
{
	mGame->GetShip()->ProcessKeyBoard(state);

	if (state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_RETURN])
	{
		mGame->SetGameClear(true);
		mGame->SetNextScene(new GameScene(mGame));
	}
}

string const GameScene::GetSceneName()
{
	return "GAME";
}