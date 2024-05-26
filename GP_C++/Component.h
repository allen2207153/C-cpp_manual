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
	
protected:
	//all actor
	class Actor* mOwner;
	//Component update order
	int mUpdateOrder;

public:
	int GetUpdateOrder() const { return mUpdateOrder; }



};
