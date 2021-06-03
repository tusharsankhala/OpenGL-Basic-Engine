#include "../Common/Scene.h"
#include "../Common/SceneBasic.h"
#include "../Common/SceneRunner.h"

#include <memory>

const int winWidth = 800;
const int winHeight = 800;

static std::map<std::string, std::string> sceneData = {
	{"basic", "Basic Scene."},
};

int main()
{
	SceneRunner runner{ "Chapter1", winWidth, winHeight };
	runner.Init();

	std::unique_ptr<Scene> scene;
	scene = std::unique_ptr<Scene>(new SceneBasic(runner.GetWindow(), winWidth, winHeight));

	return runner.Run(*scene);
}

