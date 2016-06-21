#version 330 core

in vec2 uvCoords;
in vec4 position;

uniform sampler2D tSampler;

out vec4 color;

void main()
{
	color = texture(tSampler, uvCoords);
}