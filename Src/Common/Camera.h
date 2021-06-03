#ifndef CAMERA_H
#define CAMERA_H

#include "CommonOGL.h"
#include "ShaderClass.h"

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

class Camera
{
public:
	Camera();
	void Init(int width, int height, glm::vec3 position);
	void Matrix(float fov, float nPlane, float fPlane, Shader& shader, const char* uniform);
	void Inputs(GLFWwindow* window);

private:
	glm::vec3 m_position;
	glm::vec3 m_orientation;
	glm::vec3 m_up;

	int m_width;
	int m_height;

	// Prevents the camera from jumping around when first clicking left click
	bool m_firstClick = true;

	float m_speed;
	float m_sensitivity;
};

#endif
