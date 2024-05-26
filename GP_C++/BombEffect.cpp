#include"BombEffect.h"
#include"Game.h"
#include"SpriteComponent.h"
#include"AnimSpriteComponent.h"

BombEffect::BombEffect(class Game* game)
	:Actor(game)
	, mTimeCount(0.0f)
{
	AnimSpriteComponent* asc = new AnimSpriteComponent(this, 100);
	vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/explosion1.png"),
		game->GetTexture("Assets/explosion2.png"),
		game->GetTexture("Assets/explosion3.png"),
		game->GetTexture("Assets/explosion4.png"),
	};
	asc->SetAnimTextures(anims); 
	SetScale(1.0f);
}

void BombEffect::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);
	float changeScale = mTimeCount / DisplayTime * 3.0f;
	if (changeScale > 3.0f)
	{
		changeScale = 3.0f;
	}
	SetScale(changeScale);

	mTimeCount += deltaTime;
	if (mTimeCount > +DisplayTime)
	{
		SetState(EDead);
	}
}