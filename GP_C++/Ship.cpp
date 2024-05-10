#include "Ship.h"
#include"AnimSpriteComponent.h"
#include"Game.h"

using namespace std;

Ship::Ship(Game* game) 
				:Actor(game),
				mRightSpeed(0.0f), 
				mDownSpeed(0.0f)
{
	//Create an animated sprite component
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	vector<SDL_Texture*> anims = {
			game->GetTexture("Assets/Ship01.png"),
			game->GetTexture("Assets/Ship02.png"),
			game->GetTexture("Assets/Ship03.png"),
			game->GetTexture("Assets/Ship04.png")
	};
	asc->SetAnimTextures(anims);
}

void Ship::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	Vector2 pos = GetPosition();
	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;

	SetPosition(pos);
}