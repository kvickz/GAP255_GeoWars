#version 400

uniform vec3 shaderColor;

out vec4 outColor;

void main()
{
	outColor = vec4(shaderColor, 0.6);
}