#include "TitleScene.h"
#include "Scene.h"
#include "GameScene.h"
#include "Game.h"
#include "Actor.h"
#include "Ship.h"
#include "SpriteComponent.h"

TitleScene::TitleScene(class Game* game)
	:Scene(game)
{

}

TitleScene::~TitleScene()
{

}

void TitleScene::Start()
{
	//Initialization
	mGame->SetGameClear(false);
	mStartMsg = new Actor(mGame);
	mStartMsg->SetPosition(Vector2(mGame->ScreenHeight / 2-300, mGame->ScreenWidth / 2));
	auto* startMsgSprite = new SpriteComponent(mStartMsg, 200);
	startMsgSprite->SetTexture(mGame->GetTexture("Assets/Ship01.png"));
	//Draw ship
	Ship* ship = new Ship(mGame);
	ship->SetPosition(Vector2(mGame->ScreenHeight / 2-300, mGame->ScreenWidth / 2 ));
	mGame->SetShip(ship);
}

void TitleScene::Update(float deltaTime)
{

}

void TitleScene::ProcessInput(const Uint8* state)
{
	if (state[SDL_SCANCODE_SPACE] || state[SDL_SCANCODE_RETURN])
	{
		mGame->SetNextScene(new GameScene(mGame));
		mStartMsg->SetState(Actor::EDead);
	}
}

string const TitleScene::GetSceneName()
{
	return "TITLE";
}