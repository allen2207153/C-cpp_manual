#pragma once

#include "SDL.h"
#include<vector>
#include<random>


class Game
{
	struct Vector2
	{
		float x;
		float y;
	};
	
	struct Ball
	{
		Vector2 pos;
		Vector2 vel;
	};

public:
	Game();
	// Initialize the game
	bool Initialize();
	// Runs the game loop until the game is over
	void RunLoop();
	// Shutdown the game
	void Shutdown();
private:
	// Helper functions for the game loop
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	void GenerateBall(Ball b, Vector2 pos, Vector2 vel);
	float GetRandom(float min, float max);

	// Window created by SDL
	SDL_Window* mWindow;
	//rendering 2D drawing
	SDL_Renderer* mRender;
	//Number of ticks since start game
	Uint32 mTickCount;

	// Game should continue to run
	bool mIsRunning;
	//Paddle's direction
	int mPaddleDir[2];
	//Paddle's position
	Vector2 mPaddlePos[2];
	//Ball's position
	Vector2 mBallPos;
	Vector2 mBallInitialPos;
	//Ball's velocity
	Vector2 mBallVec;
	Vector2 mBallInitialVel;
	//Use vector to create mutiple ball
	std::vector<Ball> mBall;
	int NumBall;
};
