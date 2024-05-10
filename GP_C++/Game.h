#pragma once
#include "SDL.h"
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	SDL_Texture* GetTexture(const string& fileName);
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnloadData();

	// Map of textures loaded
	unordered_map<string, SDL_Texture*> mTextures;

	// All the actors in the game
	vector<class Actor*> mActor;
	// Any pending actors
	vector<class Actor*> mPendingActors;

	// All the sprite components drawn
	vector<class SpriteComponent*> mSprites;

	SDL_Window* mWindow;
	SDL_Renderer* mRender;
	Uint32 mTickCount;
	bool mIsRunning;
	// Track if we're updating actors right now
	bool mUpdatingActors;

	class Ship* mShip; // Player's ship
};
