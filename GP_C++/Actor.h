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
	//constructor and destructor
	Actor(class Game* game);
	virtual ~Actor();

	//Update function
	void Update(float deltatime);
	//Update component
	void UpdateComponent(float deltaTime);
	//Update actor
	virtual void UpdateActor(float deltaTime);

	//get and set
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }
	
	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }



	void AddComponent(class Componenet* component);
	void RemoveComponent(class Component* component);

private:
	State mState;
	Vector2 mPosition;//actor's center
	float mScale;//actor's scale
	float mRotation;
	vector<class Component*> mComponent;
	class Game* mGame;
};
