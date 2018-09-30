#include <iostream>
#include <sstream>

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

const char* appTitle = "OpenGL Basic Engine Window";
const int w_Width = 800;
const int w_Height = 600;
GLFWwindow *window = NULL;

void glfw_OnKey(GLFWwindow *window, int key, int scancode, int action, int mode);
void glfw_showFPS(GLFWwindow *window);

bool initGL();

int main()
{
	if (!initGL())
	{
		std::cerr << "OpenGL initialization Failed" << std::endl;
		return -1;
	}

	// Render Loop.
	while (!glfwWindowShouldClose(window))
	{
		glfw_showFPS(window);

		// Events Checking.
		glfwPollEvents();

		glClearColor(0.23f, 0.45f, 0.47f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swapping the Buffers (Double Buffering).
		glfwSwapBuffers(window);
	}

	// GLFW: Cleaning Up.
	glfwTerminate();

	return 0;
}

bool initGL()
{
	// GLFW: Initialize glfw
	if (!glfwInit())
	{
		std::cerr << "GLFW Initialization Failed" << std::endl;
		return false;
	}

	// GLFW: Setting up OpenGL Context settings.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	window = glfwCreateWindow(w_Width, w_Height, appTitle, NULL, NULL);
	
	if (window == NULL)
	{
		std::cerr << "Failed to Create GLFW Window" << std::endl;
		glfwTerminate();
		return false;
	}

	// GLFW: Making the GLFW Window Currrent Context, so that we can draw on that.
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, glfw_OnKey);

	// GLEW: Initliazing.
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "GLEW Initialization Failed" << std::endl;
		return false;
	}

	return true;
}

void glfw_OnKey(GLFWwindow *window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void glfw_showFPS(GLFWwindow *window)
{
	static double previousSeconds = 0.0;
	static int frameCount = 0;
	double elapsedSeconds;

	// Returns the no of seconds since program started, in seconds.
	double currentSeconds = glfwGetTime();

	elapsedSeconds = currentSeconds - previousSeconds;

	// Limit text updates for 4 times a sec.
	if (elapsedSeconds > 0.25)
	{
		previousSeconds = currentSeconds;
		double fps = (double)frameCount / elapsedSeconds;
		double msPerFrame = 1000.0 / fps;

		std::ostringstream outs;
		outs.precision(3);
		outs << std::fixed
			<< appTitle << " "
			<< "FPS: " << fps << "  "
			<< " Frame Time: " << msPerFrame << " (ms)";

		glfwSetWindowTitle(window, outs.str().c_str());

		frameCount = 0;
	}

	frameCount++;
}