#include "Window.h"
#include "../CustomException.h"

Window::Window(const std::string& title, int width, int height)
	:
	mWidth(width),
	mHeight(height)
{
	// There should only be one instance of this class
	assert(!msWindow);
	
	msWindow = this;

    InitializeGLFW(title);
    InitializeGLEW();
}

Window::~Window()
{
    glfwTerminate();
}

void Window::InitializeGLFW(const std::string& title)
{
    // Initialize GLFW
    if (!glfwInit())
    {
        throw CREATE_CUSTOM_EXCEPTION("Failed to initialize GLFW");
    }

    // Create the window 
    mGlfwWindow = glfwCreateWindow(mWidth, mHeight, title.c_str(), NULL, NULL);
    if (!mGlfwWindow)
    {
        glfwTerminate();
        throw CREATE_CUSTOM_EXCEPTION("Failed to create the GLFW window");
    }

    // Make the window's context current
    glfwMakeContextCurrent(mGlfwWindow);
}

void Window::InitializeGLEW() const
{
    GLenum status = glewInit();
    if (GLEW_OK != status)
    { 
        std::string errorString = reinterpret_cast<const char*>(glewGetErrorString(status));
        throw CREATE_CUSTOM_EXCEPTION("Failed to initialize GLEW\n" + errorString);
    }
}

GLFWwindow* Window::GetGlfwWindow()
{
    return mGlfwWindow;
}

int Window::GetWidth()
{
    assert(msWindow);
    return msWindow->mWidth;
}

int Window::GetHeight()
{
    assert(msWindow);
    return msWindow->mHeight;
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(mGlfwWindow);
}

void Window::SwapBuffers() const
{
    glfwSwapBuffers(mGlfwWindow);
}

void Window::PollEvents() const
{
    glfwPollEvents();
}
