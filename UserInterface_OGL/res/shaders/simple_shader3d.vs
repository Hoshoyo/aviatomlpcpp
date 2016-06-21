#version 330 core

layout(location=0) in vec3 att_position;
layout(location=1) in vec2 att_texcoords;
layout(location=2) in vec3 att_normals;

uniform mat4 m_Model = mat4(1.0);
uniform mat4 m_Proj = mat4(1.0);
uniform mat4 m_View = mat4(1.0);

out vec2 uvCoords;
out vec3 normal;

void main()
{
	gl_Position = m_Proj * m_View * m_Model * vec4(att_position, 1.0);
	uvCoords = att_texcoords;
	normal = vec3(m_Model * vec4(att_normals, 0.0));
}