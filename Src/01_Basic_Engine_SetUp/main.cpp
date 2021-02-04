#include "../Common/Scene.h"
#include "../Common/SceneBasic.h"
#include "../Common/SceneRunner.h"

#include <memory>

static std::map<std::string, std::string> sceneData = {
	{"basic", "Basic Scene."},
};

int main()
{
	SceneRunner runner{ "Chapter1", 500, 500 };
	runner.Init();

	std::unique_ptr<Scene> scene;
	scene = std::unique_ptr<Scene>(new SceneBasic());

	return runner.Run(*scene);
}

