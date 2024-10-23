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

	void AddEnemy(class Enemy* enemy);
	void RemoveEnemy(class Enemy* enemy);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	constexpr static const float ScreenWidth = 768.0f;  //Screen width
	constexpr static const float ScreenHeight = 1024.0f; //Screen height

	SDL_Texture* GetTexture(const string& fileName);
private:
	void ProcessInput();
	void UpdateScene();
	void GenerateOutput();
	void LoadData();
	void UnloadData();
	void StartScene();
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
	//Is game clear?
	bool mGameClear;

	const std::string AssetsPath = "Assets/"; // Mac + CLion

	class Scene* mScene;//Current scene
	class Scene* mNextScene;//Next scene

	class Ship* mShip; // Player's ship
	vector<class Enemy*> mEnemies;

public:
	//getter, setter
	Scene* GetNextScene() const { return mNextScene; }
	void SetNextScene(class Scene* scene) { mNextScene = scene; }
	Scene* GetScene() const { return mScene; }
	void SetScene(class Scene* scene) { mScene = scene; }
	vector<class Actor*> GetActors() { return mActor; }
	vector<class Enemy*> GetEnemies() { return mEnemies; }
	void SetGameClear(const bool isClear) { mGameClear = isClear; }
	bool GetGameClear() const { return mGameClear; }
	void SetShip(class Ship* ship) { mShip = ship; }
	Ship* GetShip() const { return mShip; }
	std::string GetAssetsPath() const { return AssetsPath; }
};
