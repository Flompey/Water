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
	void CloseWindowCallback();
private:
	Window mWindow;
	Keyboard mKeyboard;
	bool mWindowShouldClose = false;
};