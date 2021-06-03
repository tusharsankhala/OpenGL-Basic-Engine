#include "Camera.h"

Camera::Camera() {}

void Camera::Init(int width, int height, glm::vec3 position)
{
	m_width = width;
	m_height = height;
	m_position = position;
	m_speed = 0.1f;
	m_sensitivity = 100.0f;

	m_orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
}

void Camera::Matrix(float fov, float nPlane, float fPlane, Shader& shader, const char* uniform)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(m_position, m_position + m_orientation, m_up);
	projection = glm::perspective(glm::radians(fov), (float)(m_width / m_height), nPlane, fPlane);

	glUniformMatrix4fv(shader.GetUniformLocation(uniform), 1, GL_FALSE, glm::value_ptr(projection * view));

}

void Camera::Inputs(GLFWwindow * window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_position += m_speed * m_orientation;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_position += m_speed * -glm::normalize(glm::cross(m_orientation, m_up));
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_position += m_speed * -m_orientation;
	}	

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_position += m_speed * glm::normalize(glm::cross(m_orientation, m_up));
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		m_position += m_speed * m_up;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
	{
		m_position += m_speed * -m_up;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		m_speed = 0.4f;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_RELEASE)
	{
		m_speed = 0.1f;
	}

	// Handles mouse inputs
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		// Hide Mouse Cursor.
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Prevents camera from jumping on the first click
		if (m_firstClick)
		{
			glfwSetCursorPos(window, (m_width / 2), (m_height / 2));
			m_firstClick = false;
		}

		// Stores the coordinates of the cursor
		double mouseX;
		double mouseY;

		// Fetches the coordinates of the cursor.
		glfwGetCursorPos(window, &mouseX, &mouseY);

		// Normalizes and shifts the coordinates of the cursor such that they begin in the middle of the screen
		// and then "transforms" them into degrees.
		float rotX = m_sensitivity * (mouseY - (m_height / 2)) / m_height;
		float rotY = m_sensitivity * (mouseX - (m_width / 2)) / m_width;

		// Calculates upcoming vertical change in the Orientation
		glm::vec3 newOrientation = glm::rotate(m_orientation, glm::radians(-rotX), glm::normalize(glm::cross(m_orientation, m_up)));

		// Decides whether or not the next vertical Orientation is legal or not
		if (abs(glm::angle(newOrientation, m_up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			m_orientation = newOrientation;
		}

		// Rotates the Orientation left and right.
		m_orientation = glm::rotate(m_orientation, glm::radians(-rotY), m_up);

		// Sets mouse cursor to the middle of the screen so that it doesn't end up roaming around.
		glfwSetCursorPos(window, (m_width / 2), (m_height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		// Unhides cursor since camera is not looking around anymore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

		// Makes sure the next time the camera looks around it doesn't jump
		m_firstClick = true;
	}
}