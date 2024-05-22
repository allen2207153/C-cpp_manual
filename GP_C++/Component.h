#pragma once

class Component
{
public:
	//Constructor
	//the lower update order, the eariler update
	Component(class Actor* owner, int updateOrder = 100);
	//Destructor
	virtual ~Component();
	//Update component with deltatime
	virtual void Update(float deltatime);
	
	int GetUpdateOrder() const { return mUpdateOrder; }


protected:
	//all actor
	class Actor* mOwner;
	//Component update order
	class Actor* mActor;
	int mUpdateOrder;
};
