#include"Enemy.h"
#include"Game.h"
#include"SpriteComponent.h"
#include"EndScene.h"
#include"ColliderComponent.h"
#include"AnimSpriteComponent.h"

Enemy::Enemy(Game* game)
	:Actor(game)
	,mEnemyMoveType(STRAIGHT)
	,mEnemySpeed(5.0f)
	,mTimeCount(0.0f)
	,mEnemyShakeHeight(2.0f)
	,mWaitTime(0.0f)
{
	AnimSpriteComponent* asc = new AnimSpriteComponent(this, 90);
	vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/enemy3.png"),

	};
	asc->SetAnimTextures(anims);
	mCollider = new ColliderComponent(this);
	mCollider->SetRadius(1.0f * GetScale());
	game->AddEnemy(this);
}

Enemy::~Enemy()
{
	GetGame()->RemoveEnemy(this);
}

void Enemy::UpdateActor(float deltaTime)
{
	Actor::UpdateActor(deltaTime);

	mTimeCount++;
	if (mTimeCount < mWaitTime)
	{
		return;
	}

	Vector2 pos = GetPosition();
	switch (mEnemyMoveType)
	{
	case STRAIGHT:
		pos.x -= mEnemySpeed * deltaTime;
		break;
	case SHAKE:
		pos.x -= mEnemySpeed * deltaTime;
		pos.y = mInitPosition->y + (cosf(mTimeCount / 10.0f) * mEnemyShakeHeight);
		break;
	default:
		break;
	}

	if (pos. x<=0)
	{
		SetState(EDead);
		//GetGame()->SetNextScene(new EndScene(GetGame()));
	}
	SetPosition(pos);
}

void Enemy::SetPosition(const Vector2& pos)
{
	mInitPosition = new Vector2(pos.x, pos.y);
	Actor::SetPosition(pos);
}