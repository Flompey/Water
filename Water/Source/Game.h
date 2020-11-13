#pragma once
#include "Window.h"

class Game
{
public:
	Game();

	void Loop();
	void Update();
	void Render();
private:
	Window mWindow;
};