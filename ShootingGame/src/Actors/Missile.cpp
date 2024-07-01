#include "Missile.h"
#include"Enemy.h"
#include"Game.h"
#include"SpriteComponent.h"
#include"ColliderComponent.h"
#include "AnimSpriteComponent.h"
#include"BombEffect.h"

Missile::Missile(class Game* game)
	:Actor(game)
{
	//Set sprite
	// Create an animated sprite component
	AnimSpriteComponent* asc = new AnimSpriteComponent(this,90);
	vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/shoot1.png"),
		
	};
	asc->SetAnimTextures(anims);
	mCollider = new ColliderComponent(this);
	mCollider->SetRadius(50.0f * GetScale());
}

void Missile::UpdateActor(float deltaTime)
{
	//Call parent fuction
	Actor::UpdateActor(deltaTime);
	//Missile's transform
	Vector2 pos = GetPosition();
	pos.x += mMissileSpeed * deltaTime;

	if (pos.x >= 990.0f)
	{
		SetState(EDead);
	}
	SetPosition(pos);


	//Collision with enemy
	for (auto enemy : GetGame()->GetEnemies())
	{
		if (Intersect(*mCollider, *(enemy->GetCollider())))
		{
			SetState(EDead);
			enemy->SetState(EDead);

			//BombEffect
			auto* bomb = new BombEffect(GetGame());
			bomb->SetPosition(Vector2(enemy->GetPosition()));
		}
		
	}

	

}