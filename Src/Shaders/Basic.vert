#version 410

layout (location=0) in vec3 vertexPosition;
layout (location=1) in vec3 vertexColor;
layout (location=2) in vec2 vertexTexCoord;

layout (location=0) out vec3 vColor;
layout (location=1) out vec2 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	vColor = vertexColor;
	gl_Position = proj * view * model * vec4(vertexPosition, 1.0f);
	texCoord = vertexTexCoord;
}