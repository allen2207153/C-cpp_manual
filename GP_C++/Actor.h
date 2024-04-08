#pragma once
#include <vector>
#include "Math.h"

using namespace std;
class Actor
{
public:
	enum State {
		EActive,
		EPaused,
		EDead
	};

	Actor(class Game* game);
	virtual ~Actor();

	//Update function
	void Update(float deltatime);
	//Update component
	void UpdateComponent(float deltaTime);
	//Update actor
	virtual void UpdateActor(float deltaTime);
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }



	void AddComponent(class Componenet* component);
	void RemoveComponent(class Component* component);

private:
	State mState;
	Vector2 mPosition;
	float mScale;
	float mRotation;
	vector<class Component*> mComponent;
	class Game* mGame;
};
