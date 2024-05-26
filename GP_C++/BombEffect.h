#pragma once
#include "Actor.h"

//Explosion effect
class BombEffect :public Actor{
public:
		BombEffect(class Game* game);
		void UpdateActor(float deltaTime) override;

private:
	float mTimeCount;
	const float DisplayTime = 0.5f;
};

