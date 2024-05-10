#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

using namespace std;

Actor::Actor(Game* game)
	:mState(EActive)
	, mPosition(Vector2::Zero)
	, mScale(1.0f)
	, mRotation(0.0f)
	, mGame(game)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	mGame->RemoveActor(this);
	// Need to delete components
	// Because ~Component calls RemoveComponent, need a different style loop
	while (!mComponent.empty())
	{
		delete mComponent.back();
	}
}

void Actor::Update(float deltaTime)
{
	if (mState == EActive)
	{
		UpdateComponent(deltaTime);
		UpdateActor(deltaTime);
	}
}

void Actor::UpdateComponent(float deltaTime)
{
	for (auto comp : mComponent)
	{
		comp->Update(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::AddComponent(Component* component)
{
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponent.begin();
	for (;
		iter != mComponent.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mComponent.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
	auto iter = find(mComponent.begin(), mComponent.end(), component);
	if (iter != mComponent.end())
	{
		mComponent.erase(iter);
	}
}