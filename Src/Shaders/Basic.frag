#version 440

layout (location=0) in vec3 vColor;
layout (location=0) out vec4 fragColor;

 uniform vec4 u_Color;

void main()
{
	fragColor = vec4(vColor, 1.0f);
	//fragColor = u_Color;
}