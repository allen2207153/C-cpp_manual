#include"Game.h"
#include<iostream>
#include<Windows.h>
#include"Actor.h"
#include <algorithm>
#include"SDL_image.h"
#include"SpriteComponent.h"

using namespace std;

Game::Game()
	:mWindow(nullptr)
	,mRender(nullptr)
	,mTickCount(0)
	, mIsRunning(true)
{
	
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

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mRender = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (!mRender)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

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

	
}

void Game::UpdateGame()
{
	float deltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;
	mUpdatingActors = true;

	//Update all actor
	for (auto actor : mActor)
	{
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	//put any pending actors to mActor
	for (auto pending : mPendingActors)
	{
		mActor.emplace_back(pending);
	}
	mPendingActors.clear();

	vector<Actor*> deadActors;

	for (auto actor : mActor)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	for (auto actor : deadActors)
	{
		delete actor;
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

	
}

void Game::AddActor(Actor* actor)
{
	//pending actor after updating
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActor.emplace_back(actor);
	}
}

void Game::RemoveActor(Actor* actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Is it in actors?
	iter = find(mActor.begin(), mActor.end(), actor);
	if (iter != mActor.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mActor.end() - 1);
		mActor.pop_back();
	}
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRender);
	SDL_Quit();
}

void Game::UnLoadData()
{
	while (!mActor.empty())
	{
		delete mActor.back();
	}
}

void Game::AddSprite(SpriteComponent* sprite)
{
	// Find the insertion point in the sorted vector
	// first element with a higher draw order
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder());
		{
			break;
		}
	}

	//Insert point before position iterator
	mSprites.insert(iter, sprite);
}

SDL_Texture* Game::GetTexture(const char* fileName)
{
	//Load from file
	SDL_Surface* surf = IMG_Load(fileName);
	if (!surf)
	{
		//Error message when failed to load texture file
		SDL_Log("Failed to load texture file %s", fileName);
		return nullptr;
	}

	//Create texture from surface
	SDL_Texture* tex = SDL_CreateTextureFromSurface(mRender, surf);
	SDL_FreeSurface(surf);
	if (!tex)
	{
		SDL_Log("Failed to load texture file %s", fileName);
		return nullptr;
	}
	return tex;
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	//Get texture's wdith and height
	SDL_QueryTexture(texture, nullptr, nullptr,
		&mTexWidth, &mTexHeight);
}




