#include "Game.h"
#include "Benchmark/BenchmarkMacros.h"
#include "Mathematics/Vector/Vector.h"
#include <random>

Game::Game()
	:
    mWindow("Water", 1920, 1080),
    mKeyboard(mWindow)
{
    NAME_THREAD("Main");
    BENCHMARK;

    mWindow.SetCloseCallback(std::bind(&Game::CloseWindowCallback, std::ref(*this)));

    std::random_device randomNumberGenerator;
    std::mt19937 randomNumberEngine(randomNumberGenerator());
    std::uniform_real_distribution<float> randomNumberDistributer(0.0f, 1.0f);

    for (int i = 0; i < 10000; ++i)
    {
        BasicVector<float, 3> vector;
        std::generate(vector.begin(), vector.end(), std::bind(randomNumberDistributer, std::ref(randomNumberEngine)));

        std::sort(vector.begin(), vector.end());
    }
    mWindowShouldClose = true;
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

