#pragma once
#include <SDL.h>
#include<SDL_image.h>
#include "Snake.h"
class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();
	void Shutdown();


private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	
	// Window created by SDL
	SDL_Window* mWindow;
	//rendering 2D drawing
	SDL_Renderer* mRender;

	bool isRunning;
	Uint32 ticksCount;

	vector2 food;
	int direction;
	Snake snake;
};

