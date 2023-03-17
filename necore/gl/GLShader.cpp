#include "GLShader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <exception>
#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

GLShader::GLShader(unsigned int program) : program(program) {
}

GLShader::~GLShader() {
	glDeleteProgram(program);
}

void GLShader::use() {
	glUseProgram(program);
}

void GLShader::uniformMatrix(std::string name, glm::mat4 matrix) {
	GLuint transformLoc = glGetUniformLocation(program, name.c_str());
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
}

void GLShader::uniform1i(std::string name, int x) {
	GLuint transformLoc = glGetUniformLocation(program, name.c_str());
	glUniform1i(transformLoc, x);
}

void GLShader::uniform1f(std::string name, float x) {
	GLuint transformLoc = glGetUniformLocation(program, name.c_str());
	glUniform1f(transformLoc, x);
}

void GLShader::uniform2f(std::string name, float x, float y) {
	GLuint transformLoc = glGetUniformLocation(program, name.c_str());
	glUniform2f(transformLoc, x, y);
}

void GLShader::uniform3f(std::string name, float x, float y, float z) {
	GLuint transformLoc = glGetUniformLocation(program, name.c_str());
	glUniform3f(transformLoc, x,y,z);
}

Shader* GLShader::create(std::string vertexCode, std::string fragmentCode) {
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	// Vertex Shader
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, nullptr);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success){
		glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
		std::cerr << "SHADER::VERTEX: compilation failed" << std::endl;
		std::cerr << infoLog << std::endl;
		return nullptr;
	}

	// Fragment Shader
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, nullptr);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success){
		glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
		std::cerr << "SHADER::FRAGMENT: compilation failed" << std::endl;
		std::cerr << infoLog << std::endl;
		return nullptr;
	}

	// Shader Program
	GLuint id = glCreateProgram();
	glAttachShader(id, vertex);
	glAttachShader(id, fragment);
	glLinkProgram(id);

	glGetProgramiv(id, GL_LINK_STATUS, &success);
	if (!success){
		glGetProgramInfoLog(id, 512, nullptr, infoLog);
		std::cerr << "SHADER::PROGRAM: linking failed" << std::endl;
		std::cerr << infoLog << std::endl;

		glDeleteShader(vertex);
		glDeleteShader(fragment);
		return nullptr;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return new GLShader(id);
}
