#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class WindowAccessSpecifier;

// Singleton
class Window
{
public:
	Window(const std::string& title, int width, int height);
	~Window();

	static int GetWidth();
	static int GetHeight();
	
	bool ShouldClose() const;

	void SwapBuffers() const;
	void PollEvents() const;

	// One should not be able to copy nor move a "Window" instance
	Window(const Window& other) = delete;
	Window& operator=(const Window& other) = delete;
private:
	void InitializeGLFW(const std::string& title);
	void InitializeGLEW() const;
	GLFWwindow* GetGlfwWindow();
private:
	friend class WindowAccessSpecifier;
	// We store a static version of the only object of this class, 
	// in order to be able to access the width and height statically
	static inline Window* msWindow = nullptr;

	GLFWwindow* mGlfwWindow = nullptr;

	int mWidth = 0;
	int mHeight = 0;
};