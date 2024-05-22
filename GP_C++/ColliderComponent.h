#pragma once
#include"Component.h"
#include"Vector2.h"

class ColliderComponent : public Component
{
public:
	ColliderComponent(class Actor* actor);
	const Vector2& GetCenter() const;

private:
	float mRadius;

public:
	void SetRadius(float radius) { mRadius = radius; }
	float GetRadius() const;
};

bool Intersect(const ColliderComponent& a, const ColliderComponent& b);