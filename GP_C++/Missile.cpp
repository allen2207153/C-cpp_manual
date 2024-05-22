#include "Missile.h"
#include"Enemy.h"
#include"Game.h"
#include"SpriteComponent.h"
#include"ColliderComponent.h"
#include "AnimSpriteComponent.h"


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
	pos.y -= mMissileSpeed * deltaTime;

	if (pos.y <= 50.0f)
	{
		SetState(EDead);
	}
	SetPosition(pos);


}