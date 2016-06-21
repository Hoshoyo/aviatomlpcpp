#version 330 core

layout(location=0) in vec2 vPosition;
layout(location=1) in vec2 vTexCoord;

uniform mat4 mModel;
uniform mat4 mProj;

out vec2 uvCoords;
out vec4 position;

void main()
{
	gl_Position = mProj * mModel * vec4(vPosition, 0.0, 1.0);
	uvCoords = vTexCoord;
	position = gl_Position;
}