#version 330 core

out vec4 fColor;

in vec2 uvCoords;
in vec4 color;

uniform sampler2D textureSampler;

void main()
{
	vec4 fragcolor = texture(textureSampler, uvCoords);
	if(fragcolor.a == 0)
		discard;
	fColor = fragcolor;
}