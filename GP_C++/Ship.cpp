#include "Ship.h"
#include "AnimSpriteComponent.h"
#include "ColliderComponent.h"
#include "Missile.h"
#include "Game.h"
#include"Scene.h"
#include"EndScene.h"
#include"Enemy.h"
#include "Math.h"
#include"BombEffect.h"

Ship::Ship(Game* game)
	:Actor(game)
	, mRightSpeed(0.0f)
	, mDownSpeed(0.0f)
	,mCanShot(false)
	,mDeltaShotTime(0.0f)
{
	// Create an animated sprite component
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png"),
	};
	asc->SetAnimTextures(anims);
	mCollider = new ColliderComponent(this);
	mCollider->SetRadius(70.0f * GetScale());
}

void Ship::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	// Update position based on speeds and delta time
	
	if (GetGame()->GetScene()->GetSceneName().compare("END") != 0)
	{
		Vector2 pos = GetPosition();
		pos.x += mRightSpeed * deltaTime;
		pos.y += mDownSpeed * deltaTime;
		// Restrict position to left half of screen
		if (pos.x < 25.0f)
		{
			pos.x = 25.0f;
		}
		else if (pos.x > 990.0f)
		{
			pos.x = 990.0f;
		}
		if (pos.y < 25.0f)
		{
			pos.y = 25.0f;
		}
		else if (pos.y > 743.0f)
		{
			pos.y = 743.0f;
		}
		SetPosition(pos);
	}

	if (!mCanShot)
	{
		mDeltaShotTime += deltaTime;
		if (mDeltaShotTime > CanShotTime)
		{
			mCanShot = true;
			mDeltaShotTime = 0.0f;
		}
	}

	//Collision with enimies
	for (auto enemy : GetGame()->GetEnemies())
	{
		if (Intersect(*mCollider, *(enemy->GetCollider())))
		{
			GetGame()->SetNextScene(new EndScene(GetGame()));
			SetState(EDead);

			auto* bomb = new BombEffect(GetGame());
			bomb->SetPosition(Vector2(enemy->GetPosition()));
			return;
		}
	}

}

void Ship::ProcessKeyBoard(const uint8_t* state)
{
	mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;
	// right/left
	if (state[SDL_SCANCODE_D])
	{
		mRightSpeed += 250.0f;
	}
	if (state[SDL_SCANCODE_A])
	{
		mRightSpeed -= 250.0f;
	}
	// up/down
	if (state[SDL_SCANCODE_S])
	{
		mDownSpeed += 300.0f;
	}
	if (state[SDL_SCANCODE_W])
	{
		mDownSpeed -= 300.0f;
	}

	if (state[SDL_SCANCODE_K])
	{
		if (mCanShot)
		{
			mCanShot = false;
			mDeltaShotTime = 0.0f;

			auto* missile = new Missile(GetGame());
			Vector2 pos = GetPosition();
			missile->SetPosition(Vector2(pos.x +20.0f, pos.y ));
		}
	}
}