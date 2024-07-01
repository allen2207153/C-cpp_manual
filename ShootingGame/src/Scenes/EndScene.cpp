#include "EndScene.h"
#include "TitleScene.h"
#include "Game.h"
#include "Actor.h"
#include "Ship.h"
#include"Enemy.h"
#include "SpriteComponent.h"

EndScene::EndScene(class Game* game)
	:Scene(game)
{

}

EndScene::~EndScene()
{

}

void EndScene::Start()
{
	mEndMsg = new Actor(mGame);
	mEndMsg->SetPosition(Vector2(mGame->ScreenWidth / 2, mGame->ScreenHeight / 2));
	auto* endMsgSprite = new SpriteComponent(mEndMsg, 200);

	
	endMsgSprite->SetTexture(
		mGame->GetTexture((mGame->GetGameClear() ? "Assets/msg_clear.png" : "Assets/msg_over.png"))
	);

}

void EndScene::Update(float deltaTime)
{

}

void EndScene::ProcessInput(const Uint8* state)
{
	if (state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_RETURN])
	{
		mGame->SetNextScene(new TitleScene(mGame));
		mEndMsg->SetState(Actor::EDead);

		vector<class Actor*> actors = mGame->GetActors();
		Actor* ship = mGame->GetShip();
		auto iter = find(actors.begin(), actors.end(), ship);

		if (iter != actors.end())
		{
			ship->SetState(Actor::EDead);
		}
		for (auto enemy : mGame->GetEnemies())
		{
			enemy->SetState(Actor::EDead);
		}
	}
}

string const EndScene::GetSceneName()
{
	return "END";
}