#include"Game.h"
#include<iostream>


const int HEIGHT = 480;
const int WIDTH = 640;

const int DIRECTION_UP = 0;
const int DIRECTION_DOWN = 1;
const int DIRECTION_RIGHT = 2;
const int DIRECTION_LEFT = 3;

float delay = 0;

Game::Game()
    :mWindow(nullptr)
    , mRender(nullptr)
    , isRunning(true)
    , ticksCount(0)
{}

void RandomFeedPosition(Snake snake, vector2* feed)
{
    feed->x = (rand() % (WIDTH - LENGTH) / 10 + 1) * 10;
    feed->y = (rand() % (HEIGHT - LENGTH) / 10 + 1) * 10;
    while (snake.SearchNode(*feed) > -1) {
        feed->x = (rand() % (WIDTH - LENGTH) / 10 + 1) * 10;
        feed->y = (rand() % (HEIGHT - LENGTH) / 10 + 1) * 10;
    }
}


bool Game::Initialize() {
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    if (sdlResult != 0)
    {
        SDL_Log("Unable to initialize SDL:%s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(
        "Snake Game",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_OPENGL
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

    direction = DIRECTION_RIGHT;
    snake = Snake();
    snake.InsertHead(vector2{ WIDTH / 2 - LENGTH * 4, HEIGHT / 2 });
    snake.InsertHead(vector2{ WIDTH / 2 - LENGTH * 3, HEIGHT / 2 });
    snake.InsertHead(vector2{ WIDTH / 2 - LENGTH * 2, HEIGHT / 2 });
    snake.InsertHead(vector2{ WIDTH / 2 - LENGTH * 1, HEIGHT / 2 });

    srand((unsigned int)time(NULL));
    RandomFeedPosition(snake, &food);

    return true;
}

void Game::Shutdown() {
    SDL_DestroyRenderer(mRender);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::RunLoop()
{
    while (isRunning)
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
            isRunning = false;
            break;
        }
    }
    //Get keyboard state
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_UP] && (direction != DIRECTION_DOWN))
    {
        direction = DIRECTION_UP;
    }
    if (state[SDL_SCANCODE_DOWN] && (direction != DIRECTION_UP))
    {
        direction = DIRECTION_DOWN;
    }
    if (state[SDL_SCANCODE_RIGHT] && (direction != DIRECTION_LEFT))
    {
        direction = DIRECTION_RIGHT;
    }
    if (state[SDL_SCANCODE_LEFT] && (direction != DIRECTION_RIGHT))
    {
        direction = DIRECTION_LEFT;
    }

    //if press esc than end
    if (state[SDL_SCANCODE_ESCAPE])
    {
        isRunning = false;
    }
}

void Game::UpdateGame()
{
    float deltaTime = SDL_GetTicks() - ticksCount;
    ticksCount = SDL_GetTicks();

    delay += deltaTime;

    if (delay >= 100)
    {
        switch (direction) {
        case DIRECTION_UP:
            snake.InsertHead(vector2{ snake.GetFirst()->GetPos().x, snake.GetFirst()->GetPos().y - LENGTH });
            break;
        case DIRECTION_DOWN:
            snake.InsertHead(vector2{ snake.GetFirst()->GetPos().x, snake.GetFirst()->GetPos().y + LENGTH });
            break;
        case DIRECTION_RIGHT:
            snake.InsertHead(vector2{ snake.GetFirst()->GetPos().x + LENGTH, snake.GetFirst()->GetPos().y });
            break;
        case DIRECTION_LEFT:
            snake.InsertHead(vector2{ snake.GetFirst()->GetPos().x - LENGTH, snake.GetFirst()->GetPos().y });
            break;
        default:
            break;
        }
        snake.DeleteLast();
        delay = 0;

        if (snake.SearchBodyNode(snake.GetFirst()->GetPos()) > 0)
        {
            isRunning = false;
        }

        if (snake.GetFirst()->GetPos().x<0 ||
            snake.GetFirst()->GetPos().x >(WIDTH - LENGTH) ||
            snake.GetFirst()->GetPos().y<0 ||
            snake.GetFirst()->GetPos().y>(HEIGHT - LENGTH)) {
            isRunning = false;
        }

        if (snake.SearchNode(food) > -1)
        {
            snake.InsertHead(food);
            RandomFeedPosition(snake, &food);
        }
    }
}

void Game::GenerateOutput()
{
    // Generate Background
    SDL_SetRenderDrawColor(mRender, 0, 128, 0, 255);
    SDL_RenderClear(mRender);

    //Generate Snake
    SDL_SetRenderDrawColor(mRender, 192, 192, 192, 192);
    SnakeNode* current = snake.GetFirst();
    while (current != 0)
    {
        SDL_Rect node{
            static_cast<int>(current->GetPos().x),
            static_cast<int>(current->GetPos().y),
            LENGTH,
            LENGTH
        };
        SDL_RenderFillRect(mRender, &node);
        current = current->GetNext();
    }
    SDL_SetRenderDrawColor(mRender, 255, 50, 0, 255);
    // Generate Feed
    SDL_Rect appleNode{
        static_cast<int>(food.x),
        static_cast<int>(food.y),
        LENGTH, // Width
        LENGTH // Height
    };
    SDL_RenderFillRect(mRender, &appleNode);

    SDL_RenderPresent(mRender);
}