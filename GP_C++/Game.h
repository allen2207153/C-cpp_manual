#pragma once

#include "SDL.h"
#include<vector>
#include<random>

using namespace std;
class Game
{
	
public:
	Game();
	// Initialize the game
	bool Initialize();
	// Runs the game loop until the game is over
	void RunLoop();
	// Shutdown the game
	void Shutdown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

private:
	// Helper functions for the game loop
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void LoadData();
	void UnLoadData();
	
	vector<class Actor*> mActor;
	vector<class Actor*> mPendingActors;
	
	// Window created by SDL
	SDL_Window* mWindow;
	//rendering 2D drawing
	SDL_Renderer* mRender;
	//Number of ticks since start game
	Uint32 mTickCount;

	// Game should continue to run
	bool mIsRunning;
	//Update actor
	bool mUpdatingActors;
};
