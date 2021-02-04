#version 440

layout (location=0) in vec3 vertexPosition;
layout (location=1) in vec3 vertexColor;

layout (location=0) out vec3 vColor;

void main()
{
	vColor = vertexColor;
	gl_Position = vec4(vertexColor, 1.0f);
}