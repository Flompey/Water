#pragma once
#include "Window.h"

class Game
{
public:
	Game();
	~Game();

	void BeginLoop();
private:
	void Loop();
	void Update();
	void Render();
private:
	Window mWindow;
};