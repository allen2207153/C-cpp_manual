#include "GameScene.h"
#include "EndScene.h"
#include "Game.h"
#include "Ship.h"
#include"Enemy.h"
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
	for (int i = 0; i < 10; i++)
	{
		auto* enemy = new Enemy(mGame);
		enemy->SetPosition(Vector2(1100.0f, Math::GetRand(100.0f, mGame->ScreenHeight - 300)));
		enemy->SetEnemySpeed(Math::GetRand(200.0f, 300.f));
		enemy->SetScale(Math::GetRand(2.0f, 2.5f));

		if (i % 2 == 0)
		{
			enemy->SetEnemyMoveType(Enemy::SHAKE);
			enemy->SetEnemyShakeHeight(Math::GetRand(1.0f, 5.0f));
		}
		enemy->SetWaitTime(i / 3 * Math::GetRand(80.0f, 100.0f));
	}
}

void GameScene::Update(float deltaTime)
{
	if (mGame->GetEnemies().empty())
	{
		mGame->SetGameClear(true);
		mGame->SetNextScene(new EndScene(mGame));
	}
}

void GameScene::ProcessInput(const Uint8* state)
{
	mGame->GetShip()->ProcessKeyBoard(state);


}

string const GameScene::GetSceneName()
{
	return "GAME";
}