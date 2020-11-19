#pragma once
#include "Window/Window.h"
#include "Keyboard.h"

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
	Keyboard mKeyboard;
};