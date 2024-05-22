#pragma once
#include "SDL_image.h"
#include "string"

using namespace std;

class Scene
{
public:
	Scene(class Game* games);
	virtual ~Scene();
	virtual void Start();
	virtual void Update(float deltaTime);
	virtual void ProcessInput(const Uint8* state);
	virtual string const GetSceneName();

protected:
	class Game* mGame;
};