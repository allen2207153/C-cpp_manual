#include"BGSpriteComponent.h"
#include"Actor.h"

using namespace std;

void BGSpriteComponent::SetBGTextures(const vector<SDL_Texture*>& textures)
{
	int count = 0;
	for (auto tex : textures)
	{
		BGTexture temp;
		temp.mTexture = tex;
		temp.mOffset.x = 0;
		temp.mOffset.y = count * mScreenSize.x;
		mBGtextures.emplace_back(temp);
		count++;
	}
}

void BGSpriteComponent::Update(float deltaTime)
{
	SpriteComponent::Update(deltaTime);
	for (auto& bg : mBGtextures)
	{
		bg.mOffset.y += mScrollSpeed * deltaTime;
		if (bg.mOffset.y < -mScreenSize.y)
		{
			bg.mOffset.y = (mBGtextures.size() - 1 * mScreenSize.y - 1);
		}
	}
}