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
	void SetState(const State state) { mState = state; }

	class Game* GetGame() { return mGame; }

	// Add/remove components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	// Actor's state
	State mState;

	// Transform
	Vector2 mPosition;
	float mScale;
	float mRotation;
	vector<class Component*> mComponent;
	class Game* mGame;
};
