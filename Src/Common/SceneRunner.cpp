#include "SceneRunner.h"

#include <stdexcept>

SceneRunner::SceneRunner(const std::string _winTitle, int _width, int _height, int samples)
	: m_winTitle(_winTitle), m_winWidth(_width), m_winHeight(_height), m_samples(samples)
{}

void SceneRunner::Init()
{
	// Initialize GLFW.
	if (!glfwInit())
		throw std::runtime_error("Failed to initialize GLFW");
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 6);
	
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	if (m_debug)
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

	if (m_samples > 0)
		glfwWindowHint(GLFW_SAMPLES, m_samples);

	// Open the window.
	m_window = glfwCreateWindow(m_winWidth, m_winHeight, m_winTitle.c_str(), nullptr, nullptr);

	if (!m_window)
	{
		throw std::runtime_error("Failed to Create GLFW window");
		glfwTerminate();

		return;
	}

	glfwMakeContextCurrent(m_window);

	// Get Framebuffer Size.
	glfwGetFramebufferSize(m_window, &m_frameBufferWidth, &m_frameBufferHeight);

	// Load the OpenGL functions.
	if (!gladLoadGL())
	{
		throw std::runtime_error("Loading GLAD Failed");
		glfwDestroyWindow(m_window);
		glfwTerminate();
		
		return;
	}

	// Initialization.
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
}

int SceneRunner::Run(Scene& scene)
{
	scene.SetDimensions(m_frameBufferWidth, m_frameBufferHeight);
	scene.InitScene();
	scene.Resize(m_frameBufferWidth, m_frameBufferHeight);

	// Enter the main Loop.
	MainLoop(m_window, scene);

	// Close window and terminate GLFW
	glfwTerminate();

	return EXIT_SUCCESS;
}


void SceneRunner::MainLoop(GLFWwindow* window, Scene& scene)
{
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		scene.Update(glfwGetTime());
		scene.Render();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}