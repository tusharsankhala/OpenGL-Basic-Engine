#version 440

layout (location=0) in vec3 vColor;
layout (location=1) in vec2 texCoord;

layout (location=0) out vec4 fragColor;

uniform vec4 u_Color;
uniform sampler2D tex0;

void main()
{
	fragColor = texture(tex0, texCoord);
	//fragColor = vec4(vColor, 1.0f);
}