#include"Game.h"
#include<iostream>

const int thickness = 15;
const float paddleH = 100.0f;
const int maxBallNum = 5;
//uniformly - distributed integer random number generator 
//that produces non - deterministic random numbers.
std::random_device rnd;
//A Mersenne Twister pseudo-random generator of 32-bit numbers
//with a state size of 19937 bits.
std::mt19937 mt(rnd());


Game::Game()
	:mWindow(nullptr)
	,mRender(nullptr)
	,mTickCount(0)
	, mIsRunning(true)
{
	for (int i = 0; i < 2; i++) mPaddleDir[i] = 0;
}

bool Game::Initialize()
{
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);

	if (sdlResult != 0)
	{
		SDL_Log("Unable to initialize SDL:%s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game Programming in C++(Chapter1)",
		100,
		100,
		1024,
		768,
		0
	);

	mRender = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	//paddle's position
	for (int i = 0; i < 2; i++)
	{
		mPaddlePos[i].x = (i == 0) ? 10.0f : 1024.0f - 20.0f;
		mPaddlePos[i].y = 768.0f / 2.0f;
	}
	//Initialize value
	mBall.emplace_back();
	mBall[0].pos.x = 1024.0f / 2.0f;
	mBall[0].pos.y = 768.0f / 2.0f;
	mBall[0].vel.x = -2.0f;
	mBall[0].vel.y = 2.0f;
	NumBall = 1;
	

	return true;
}



void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}
void Game::ProcessInput()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}
	//Get keyboard state
	const Uint8* state = SDL_GetKeyboardState(NULL);
	//if press esc than end
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}

	//1P move update
	mPaddleDir[0] = 0;
	if (state[SDL_SCANCODE_W])
	{
		mPaddleDir[0] -= 1;
	}
	if (state[SDL_SCANCODE_S])
	{
		mPaddleDir[0] += 1;
	}

	//2P move update
	mPaddleDir[1] = 0;
	if (state[SDL_SCANCODE_I])
	{
		mPaddleDir[1] -= 1;
	}

	if (state[SDL_SCANCODE_K])
	{
		mPaddleDir[1] += 1;
	}
}

void Game::UpdateGame()
{
	//Wait until 16ms has elapsed since last time
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16));

	//Delta time is the difference in ticks from last time
	//(converted to second);
	float deltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;

	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	for (int i = 0; i < 2; i++)
	{
		if (mPaddleDir[i] != 0)
		{
			mPaddlePos[i].y += mPaddleDir[i] * 300.0f * deltaTime;

			if (mPaddlePos[i].y < (paddleH / 2.0f + thickness))
			{
				mPaddlePos[i].y = paddleH / 2.0f + thickness;
			}
			else if (mPaddlePos[i].y >(768.0f - paddleH / 2.0f - thickness))
			{
				mPaddlePos[i].y = 768.0f - paddleH / 2.0f - thickness;
			}
		}
	}
	
	int count = 0;
	for (Ball& b : mBall)
	{
		//Update ball position based on ball velocity
		b.pos.x += b.vel.x * 100 * deltaTime;
		b.pos.y += b.vel.y * 100 * deltaTime;
		//Did ball collide with the top wall
		if (b.pos.y <= thickness && b.vel.y < 0.0f)
		{
			b.vel.y *= -1;
		}
		//Did ball collide with the down wall
		else if (b.pos.y >= (768.0f - thickness) && b.vel.y > 0.0f)
		{
			b.vel.y *= -1;
		}
		//Did ball interact with paddle
		float diff[2];

		if (b.vel.x < 0)
		{
			int i = 0;
			diff[i] = b.pos.y - mPaddlePos[i].y;
			diff[i] = (diff[i] > 0.0f) ? diff[i] : -diff[i];
			if (diff[i] <= paddleH / 2.0f &&
				b.pos.x <= 25.0f && b.pos.x >= 20.0f &&
				b.vel.x < 0.0f)
			{
				b.vel.x *= -1.0f;
				//Create ball 
				if (NumBall <= maxBallNum)
				{
					Ball IniBall = {
						b.pos,
						{b.vel.x * GetRandom(0.7f, 1.5f), GetRandom(1.0f,5.0f)}
					};
					mBall.push_back(IniBall);
					GenerateBall(mBall[mBall.size() - 1], IniBall.pos, IniBall.vel);
					NumBall++;
					b.pos = IniBall.pos;
				}
			}

		}
		else
		{
			int i = 1;
			diff[i] = b.pos.y - mPaddlePos[i].y;
			diff[i] = (diff[i] > 0.0f) ? diff[i] : -diff[i];
			if (diff[i] <= paddleH / 2.0f &&
				b.pos.x <= 1024.0f - 20.0f && b.pos.x >= 1024.0f - 25.0f &&
				b.vel.x > 0.0f)
			{
				b.vel.x *= -1.0f;
				if (NumBall <= maxBallNum)
				{
					Ball IniBall = {
						b.pos,
						{b.vel.x * GetRandom(0.7f, 1.5), GetRandom(1.0f, 5.0)}
					};
					mBall.push_back(IniBall);
					GenerateBall(mBall[mBall.size() - 1], IniBall.pos, IniBall.vel);
					NumBall++;
					b.pos = IniBall.pos;
				}
			}
		}

		////Out of screen
		//if (b.pos.x < 0.0f)
		//{
		//	NumBall--;
		//	if (mBall.size() > 0)
		//	{
		//		mBall.erase(mBall.begin() + count);
		//	}
		//}
		//else if(b.pos.x >1024.0f)
		//{
		//	NumBall--;
		//	if (mBall.size() > 0)
		//	{
		//		mBall.erase(mBall.begin() + count);
		//	}
		//}

		//if (NumBall <= 0)break;
		//count++;

		
	}
	//When the ball is zero,initialization ball
	/*if (NumBall <= 0)
	{
		SDL_DestroyRenderer(mRender);

	}*/

	
	// Did the ball collide with the right wall?
	/*else if (mBallPos.x >= (1024.0f - thickness) && mBallVec.x > 0.0f)
	{
		mBallVec.x *= -1.0f;
	}*/
	//if ball go off the screen(if so than end)
	
	if (NumBall <= 0)
	{
		SDL_DestroyRenderer(mRender);
		mBall.emplace_back();
		mBall[0].pos = mBallInitialPos;
		mBall[0].vel = mBallInitialVel;
		NumBall = 1;
	}
}
void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(
		mRender,
		0,		//R
		0,		//G
		255,	//B
		255	//A
	);
	 //clear render
	SDL_RenderClear(mRender);


	//Set wall color
	SDL_SetRenderDrawColor(mRender, 255, 255, 255, 255);

	//Draw top wall
	SDL_Rect wall{
		0,//left top x
		0,//left top y
		1024,//weight
		thickness//height
	};
	//Draw top wall
	SDL_RenderFillRect(mRender, &wall);

	//Draw down wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRender, &wall);

	////Draw right wall
	//wall.x = 1024 - thickness;
	//wall.y = 0;
	//wall.w = thickness;
	//wall.h = 1024;
	//SDL_RenderFillRect(mRender, &wall);

	//Draw ball
	
	//Draw paddle
	for (int i = 0; i < 2; i++)
	{
		SDL_Rect paddle{
		static_cast<int>(mPaddlePos[i].x),
		static_cast<int>(mPaddlePos[i].y - paddleH / 2),
		thickness,
		static_cast<int>(paddleH)
		};
		SDL_RenderFillRect(mRender, &paddle);
	}

	for (Ball& b : mBall)
	{
		GenerateBall(b, b.pos, b.vel);
	}
	SDL_RenderPresent(mRender);
	
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRender);
	SDL_Quit();
}


//Draw ball
void Game::GenerateBall(Ball b, Vector2 pos, Vector2 vel)
{
	SDL_Rect ball{
		static_cast<int>(b.pos.x - thickness / 2),
		static_cast<int>(b.pos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRender, &ball);
}

float Game::GetRandom(float min, float max)
{
	std::uniform_real_distribution<float>random(min, max);
	return random(mt);
}

