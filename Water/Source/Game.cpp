#include "Game.h"
#include "Benchmark/BenchmarkMacros.h"

Game::Game()
	:
    mWindow("Water", 1920, 1080),
    mKeyboard(mWindow)
{
    NAME_THREAD("Main");
    BENCHMARK;

    mWindow.SetCloseCallback(std::bind(&Game::CloseWindowCallback, std::ref(*this)));
}

Game::~Game()
{
    SAVE_BENCHMARK;
}

void Game::BeginLoop()
{
    // Loop until the user closes the window
    while (!mWindowShouldClose)
    {
        Loop();
    }
}

void Game::Loop()
{
    BENCHMARK;

    glClear(GL_COLOR_BUFFER_BIT);

    Update();
    Render();

    NAMED_BENCHMARK("Swap and poll");
    // Swap front and back buffers
    mWindow.SwapBuffers();

    // Poll for and process events
    mWindow.PollEvents();
}

void Game::Update()
{
    BENCHMARK;
}

void Game::Render()
{
    BENCHMARK;
}

void Game::CloseWindowCallback()
{
    // Close the window
    mWindowShouldClose = true;
}

