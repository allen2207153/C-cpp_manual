#pragma once
#include"Actor.h"

class Missile : public Actor {
public :
	Missile(class Game* game);
	void UpdateActor(float deltaTime) override;

private:
	const float mMissileSpeed = 1000.0f;
	class ColliderComponent* mCollider;
};