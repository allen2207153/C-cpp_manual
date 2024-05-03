#include"AnimSpriteComponent.h"



void AnimSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);

	if (mAnimTextures.size() > 0)
	{
		//Update the current frame based from frame rate
		//and delta time
		mCurrFrame += mAnimFPS * deltaTime;
		//Wrap current frame if need
		while (mCurrFrame >= mAnimTextures.size())
		{
			mCurrFrame -= mAnimTextures.size();
		}
		//Set the current frame
		SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
	}
}

//void AnimSpriteComponent::SetAnimTextures()