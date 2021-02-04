#ifndef SCENERUNNER_H
#define SCENERUNNER_H


#include <glad/glad.h>
#include "Scene.h"
#include <GLFW/glfw3.h>

#include <string>
#include <map>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

class SceneRunner
{
public:
	SceneRunner(const std::string _winTitle, int _width = WIN_WIDTH, int _height = WIN_HEIGHT, int samples = 0);

	void Init();
	int Run(Scene& scene);

private:
	void MainLoop(GLFWwindow* window, Scene& scene);

private:
	GLFWwindow* m_window;
	const std::string m_winTitle;
	int m_winWidth, m_winHeight;
	int m_frameBufferWidth, m_frameBufferHeight;
	int m_samples = 0;
	bool m_debug = true;
};

#endif
