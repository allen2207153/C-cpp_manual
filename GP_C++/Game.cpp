#include"Game.h"
#include<iostream>
#include<Windows.h>
#include"Actor.h"
#include <algorithm>
#include"SDL_image.h"
#include"SpriteComponent.h"
#include"BGSpriteComponent.h"
#include"Ship.h"
#include"TitleScene.h"

using namespace std;

Game::Game()
	:mWindow(nullptr)
	,mRender(nullptr)
	, mIsRunning(true)
	,mUpdatingActors(false)
	
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
		"Shooting game",
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


	LoadData();

	mTickCount = SDL_GetTicks();

	

	return true;
}



void Game::RunLoop()
{
	mScene = new TitleScene(this);
	mNextScene = mScene;
	StartScene();
	
	while (mIsRunning)
	{
		//Update scene
		UpdateScene();
		//Start scene
		if (mScene->GetSceneName().compare(mNextScene->GetSceneName()) != 0)
		{
			delete mScene;
			mScene = mNextScene;
			StartScene();
		}

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

	mScene->ProcessInput(state);
	
}

void Game::UpdateScene()
{
	ProcessInput();

	//Compute delta time
	//Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16));

	float deltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTickCount = SDL_GetTicks();

	//Update all actor
	mUpdatingActors = true;
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

	//Update scene
	mScene->Update(deltaTime);

	//Add any dead actors to a temp vector
	vector<Actor*> deadActors;

	for (auto actor : mActor)
	{
		if (actor->GetState() == Actor::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}
	//Delete dead actors(which remove them from mActors)
	for (auto actor : deadActors)
	{
		delete actor;
	}

	//Output
	GenerateOutput();
}
void Game::GenerateOutput()
{
	SDL_SetRenderDrawColor(
		mRender,
		0,		//R
		0,		//G
		0,	//B
		255	//A
	);
	 //clear render
	SDL_RenderClear(mRender);

	//Draw all sprite components
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRender);
	}
	
	SDL_RenderPresent(mRender);
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
	auto iter = find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Is it in actors?
	iter = find(mActor.begin(), mActor.end(), actor);
	if (iter != mActor.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		iter_swap(iter, mActor.end() - 1);
		mActor.pop_back();
	}
}

void Game::Shutdown()
{
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRender);
	SDL_Quit();
	UnloadData();
	IMG_Quit();
}

void Game::LoadData()
{
	//// Create player's ship
	//mShip = new Ship(this);
	//mShip->SetPosition(Vector2(100.0f, 384.0f));
	//mShip->SetScale(1.5f);

	// Create actor for the background (this doesn't need a subclass)
	Actor* temp = new Actor(this);
	temp->SetPosition(Vector2(512.0f, 384.0f));
	// Create the "far back" background
	BGSpriteComponent* bg = new BGSpriteComponent(temp);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	vector<SDL_Texture*> bgtexs = {
		GetTexture("Assets/Farback01.png"),
		GetTexture("Assets/Farback02.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-100.0f);
	// Create the closer background
	bg = new BGSpriteComponent(temp, 50);
	bg->SetScreenSize(Vector2(1024.0f, 768.0f));
	bgtexs = {
		GetTexture("Assets/Stars.png"),
		GetTexture("Assets/Stars.png")
	};
	bg->SetBGTextures(bgtexs);
	bg->SetScrollSpeed(-200.0f);
}


void Game::UnloadData()
{
	//Delete actors
	//~Actor(destructor) calls RemoveActor, have to use a different style loop
	while (!mActor.empty())
	{
		delete mActor.back();
	}

	//Destroy textures
	for (auto i : mTextures)
	{
		SDL_DestroyTexture(i.second);
	}
	mTextures.clear();
}

void Game::AddSprite(SpriteComponent* sprite)
{
	// Find the insertion point in the sorted vector
	// first element with a higher draw order
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	//Insert point before position iterator
	mSprites.insert(iter, sprite);
}

SDL_Texture* Game::GetTexture(const string& fileName)
{
	SDL_Texture* tex = nullptr;
	// Is the texture already in the map?
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		// Load from file
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// Create texture from surface
		tex = SDL_CreateTextureFromSurface(mRender, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}

void Game::RemoveSprite(class SpriteComponent* sprite)
{
	auto iter = find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void Game::StartScene()
{
	mScene->Start();
}



