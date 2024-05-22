#include "ColliderComponent.h"
#include"Actor.h"

ColliderComponent::ColliderComponent(class Actor* actor)
	:Component(actor)
	, mRadius(0.0f)
{

}

const Vector2& ColliderComponent::GetCenter() const
{
	return mActor->GetPosition();
}

float ColliderComponent::GetRadius() const
{
	return mActor->GetScale() * mRadius;
}

bool Intersect(const ColliderComponent& a, const ColliderComponent& b)
{
	//Calculate collide object's distance
	Vector2 diff = a.GetCenter() - b.GetCenter();
	float distSq = diff.LengthSq();
	//Collide circle
	float radDiff = a.GetRadius() + b.GetRadius();
	return distSq <= radDiff * radDiff;
}