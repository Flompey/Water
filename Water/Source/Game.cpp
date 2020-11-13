#include "Game.h"

Game::Game()
	:
    mWindow("Water", 1920, 1080)
{
}

void Game::Loop()
{
    // Loop until the user closes the window
   while (!mWindow.ShouldClose())
   {
       glClear(GL_COLOR_BUFFER_BIT);

       Update();
       Render();

       // Swap front and back buffers
       mWindow.SwapBuffers();

       // Poll for and process events
       mWindow.PollEvents();
   }
}

void Game::Update()
{
}

void Game::Render()
{
}
