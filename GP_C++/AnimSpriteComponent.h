#pragma once
#include <vector>
#include"SpriteComponent.h"

using namespace std;

class AnimSpriteComponent :public SpriteComponent
{
public:
	AnimSpriteComponent(class Actor* owner, int drawOrder = 100);
	//Update animation every frame(override from component)
	void Update(float deltTime) override;
	//Set the texture used for animation
	void SetAnimTextures(const vector<SDL_Texture*>& textures);
	//Set/Get the animation FPS
	float GetAnimFPS() const { return mAnimFPS; }
	void SetAnimFPS(float fps) { mAnimFPS = fps; }


private:
	vector<SDL_Texture*> mAnimTextures;
	//Current frame
	float mCurrFrame;
	//Anime's frame
	float mAnimFPS;
};