#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "easy/profiler.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <stdio.h>
#include <stdlib.h>
#include <chrono>
#include <thread>

using glm::mat4;
using glm::vec3;

static const char* shaderCodeVertex = R"(

#version 460 core
layout(std140, binding = 0) uniform PerFrameData
{
	uniform mat4 MVP;
	uniform vec4 color;
};

layout (location=0) out vec2 uv;
layout (location=1) out vec4 outColor;

const vec2 pos[3] = vec2[3](
	vec2(-0.6f, -0.4f),
	vec2( 0.6f, -0.4f),
	vec2( 0.0f,  0.6f)
);

const vec2 tc[3] = vec2[3]
(
	vec2(0.0, 0.0),
	vec2(1.0, 0.0),
	vec2(0.5, 1.0)
);

void main()
{
	gl_Position = MVP * vec4(pos[gl_VertexID], 0.0, 1.0);
	uv = tc[gl_VertexID];
	outColor = color;
}
)";

static const char* shaderCodeFragment = R"(
#version 460 core
layout (location=0) in vec2 uv;
layout (location=1) in vec4 outColor;
layout (location=0) out vec4 out_FragColor;

uniform sampler2D texture0;
 
void main()
{
	out_FragColor = texture(texture0, uv) * outColor;
}
)";

struct PerFrameData
{
	mat4 mvp;
	glm::vec4 color;
};


int main()
{
	EASY_MAIN_THREAD;
	EASY_PROFILER_ENABLE;

	glfwSetErrorCallback(
		[](int error, const char* description)
		{
			fprintf(stderr, "Error: %s\n", description);
		}
	);

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(1024, 768, "OpenGL Window", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwSetKeyCallback(window,
		[](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
			{
				glfwSetWindowShouldClose(window, true);
			}
		}
	);

	glfwSetCursorPosCallback(window,
		[](GLFWwindow* window, double x, double y)
		{
			ImGui::GetIO().MousePos = ImVec2(x, y);
		}
	);

	glfwSetMouseButtonCallback(window,
		[](GLFWwindow* window, int button, int action, int mods)
		{
			auto& io = ImGui::GetIO();
			int idx = button == GLFW_MOUSE_BUTTON_LEFT ? 0 : GLFW_MOUSE_BUTTON_RIGHT ? 2 : 1;
			io.MouseDown[idx] = action = GLFW_PRESS;
		}
	);

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glfwSwapInterval(1);

	EASY_BLOCK("Create Resources");

	const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &shaderCodeVertex, nullptr);
	glCompileShader(vertexShader);

	const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &shaderCodeFragment, nullptr);
	glCompileShader(fragmentShader);

	const GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);
	glUseProgram(program);

	GLuint VAO;
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	const GLsizeiptr kBufferSize = sizeof(PerFrameData);

	GLuint perFrameDataBuffer;
	glCreateBuffers(1, &perFrameDataBuffer);
	glNamedBufferStorage(perFrameDataBuffer, kBufferSize, nullptr, GL_DYNAMIC_STORAGE_BIT);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, perFrameDataBuffer, 0, kBufferSize);

	EASY_END_BLOCK

	// IMGUI.
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;

	// Build texture atlas
	ImFontConfig cfg = ImFontConfig();
	cfg.FontDataOwnedByAtlas = false;
	cfg.RasterizerMultiply = 1.0f;
	cfg.SizePixels = 768.0f / 32.0f;
	cfg.PixelSnapH = true;
	cfg.OversampleH = 4;
	cfg.OversampleV = 4;

	ImFont* Font = io.Fonts->AddFontFromFileTTF("../Resources/Fonts/OpenSans-Light.ttf", cfg.SizePixels, &cfg);

	unsigned char* pixels = nullptr;
	int width, height;
	io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);


	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 460");

	{
		EASY_BLOCK("Set State");
		glClearColor(0.65f, 0.8f, 1.0f, 1.0f);
	}

	int w, h, comp;
	const uint8_t* img = stbi_load("../Resources/Textures/Wood.jpg", &w, &h, &comp, 3);

	GLuint texture;
	glCreateTextures(GL_TEXTURE_2D, 1, &texture);
	glTextureParameteri(texture, GL_TEXTURE_MAX_LEVEL, 0);
	glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureStorage2D(texture, 1, GL_RGB8, w, h);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTextureSubImage2D(texture, 0, 0, 0, w, h, GL_RGB, GL_UNSIGNED_BYTE, img);
	glBindTextures(0, 1, &texture);

	stbi_image_free((void*)img);

	float col[4] = { 1.0f , 1.0f, 1.0f, 1.0f };

	while (!glfwWindowShouldClose(window))
	{
		EASY_BLOCK("MainLoop");

		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		const float ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::ColorEdit4("Color", col);

		const mat4 m = glm::rotate(mat4(1.0f), (float)glfwGetTime(), vec3(0.0f, 0.0f, 1.0f));
		const mat4 p = glm::ortho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

		const mat4 mvp = p * m;

		PerFrameData perFrameData = { .mvp = p * m, .color = glm::vec4(col[0], col[1], col[2], col[3]) };
		{
			EASY_BLOCK("Triangle Render");
			glNamedBufferSubData(perFrameDataBuffer, 0, kBufferSize, &perFrameData);
			glDrawArrays(GL_TRIANGLES, 0, 3);
		}

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		{
			EASY_BLOCK("glfwSwapBuffers()");
			glfwSwapBuffers(window);
		}

		{
			EASY_BLOCK("glfwPoolEvents()");
			std::this_thread::sleep_for(std::chrono::milliseconds(2));
			glfwPollEvents();
		}
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glDeleteTextures(1, &texture);
	glDeleteBuffers(1, &perFrameDataBuffer);
	glDeleteProgram(program);
	glDeleteShader(fragmentShader);
	glDeleteShader(vertexShader);
	glDeleteVertexArrays(1, &VAO);

	glfwDestroyWindow(window);
	glfwTerminate();

	profiler::dumpBlocksToFile("profiler_dump.prof");

	return 0;
}

