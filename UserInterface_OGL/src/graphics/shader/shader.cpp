#include "Shader.h"
#include "system/log.h"

#include <fstream>

namespace ho {
namespace graphics {

Shader::Shader(std::string& filename)
{
	m_Shader = glCreateProgram();
	m_Shader = LoadShader(filename.c_str(), m_Shader);

	glUseProgram(m_Shader);
}

Shader::~Shader()
{
	glDeleteShader(m_Shader);
}

void Shader::UseShader() const
{
	glUseProgram(m_Shader);
}

void Shader::StopShader() const
{
	glUseProgram(0);
}

GLuint Shader::LoadShader(const char* filename, GLuint shaderProgram) const
{
	GLuint VertexShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLint success;
	std::string vs_filename = filename;
	std::string fs_filename = filename;

	// Le o arquivo do vertex shader a partir do filename
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vs_filename.append(".vs").c_str(), std::ios::in);
	if (VertexShaderStream.is_open()) {
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		log::fatal("Error opening file: \n", filename, ".vs", "\nLine:", __LINE__);
	}
	const GLchar* p_v[1];
	p_v[0] = VertexShaderCode.c_str();
	GLint v_Lengths[1];
	v_Lengths[0] = VertexShaderCode.length();
	glShaderSource(VertexShader, 1, p_v, v_Lengths);

	glCompileShader(VertexShader);


	// Verifica erro de compilação do Vertex Shader
	glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(VertexShader, sizeof(InfoLog), NULL, InfoLog);
		log::fatal("Error compiling vertex shader", InfoLog);
	}

	// Le o arquivo do fragment shader a partir do filename
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fs_filename.append(".fs").c_str(), std::ios::in);
	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	else {
		log::fatal("Error opening file: \n", filename, ".fs", "\nLine:", __LINE__);
	}
	const GLchar* p_f[1];
	p_f[0] = FragmentShaderCode.c_str();
	GLint f_Lengths[1];
	f_Lengths[0] = FragmentShaderCode.length();
	glShaderSource(FragmentShader, 1, p_f, f_Lengths);

	glCompileShader(FragmentShader);

	// Verifica erro de compilação do Fragment Shader
	glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		GLchar InfoLog[1024];
		glGetShaderInfoLog(FragmentShader, sizeof(InfoLog), NULL, InfoLog);
		log::fatal("Error compiling fragment shader", InfoLog);
	}

	glAttachShader(shaderProgram, VertexShader);		// Conecta os programas com os respectivos shaders
	glAttachShader(shaderProgram, FragmentShader);		// "
	glLinkProgram(shaderProgram);						// Linka os programas
	glDetachShader(shaderProgram, VertexShader);		// Precisa ser desconectado para que o driver tenha contagem de referência zerada
	glDetachShader(shaderProgram, FragmentShader);		// "
	glDeleteShader(VertexShader);						// Deleta o shader
	glDeleteShader(FragmentShader);						// "

														// Verifica erro de link entre os programas
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success == 0) {
		GLchar ErrorLog[1024];
		glGetProgramInfoLog(shaderProgram, sizeof(ErrorLog), NULL, ErrorLog);
		log::fatal("Error linking shader programs", ErrorLog);
	}

	glValidateProgram(shaderProgram);

	return shaderProgram;
}

void Shader::ActivateAlphaBlend() const
{
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Shader::DeactivateAlphaBlend() const
{
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}

}}