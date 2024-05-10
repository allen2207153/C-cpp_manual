#pragma once
#include "SpriteComponent.h"
#include <vector>
#include "Math.h"

using namespace std;

class BGSpriteComponent : public SpriteComponent
{
public:
	//Set draw order to default to lower
	BGSpriteComponent(class Actor* owner, int drawOrder = 10);
	void Update(float deltaTime) override;
	void Draw(SDL_Renderer* renderer) override;
	void SetBGTextures(const vector<SDL_Texture*>& textures);
	void SetScreenSize(const Vector2& size) { mScreenSize = size; }
	void SetScrollSpeed(float speed) { mScrollSpeed = speed; }

private:
	struct BGTexture
	{
		SDL_Texture* mTexture;
		Vector2 mOffset;
	};
	vector<BGTexture> mBGTextures;
	Vector2 mScreenSize;
	float mScrollSpeed;
};