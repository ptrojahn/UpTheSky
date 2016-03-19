#include "include\ShaderManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

std::string readFile(std::string path) {
	std::ifstream fileStream(path);
	if (fileStream.fail()){
		std::cout << "Failed to load file " << path << std::endl;
		return std::string();
	}
	std::stringstream stringStream;
	stringStream << fileStream.rdbuf();
	return stringStream.str();
}

GLuint ShaderManager::createShader(std::string vertexShaderPath, std::string fragmentShaderPath) {
	for (ShaderData shaderData : shaders)
		if (shaderData.vertexShaderPath == vertexShaderPath && shaderData.fragmentShaderPath == fragmentShaderPath)
			return shaderData.id;

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertString = readFile(vertexShaderPath);
	if (vertString.empty())
		return 0;
	const char* vss = vertString.c_str();
	glShaderSource(vertexShader, 1, &vss, nullptr);
	glCompileShader(vertexShader);
	GLchar vertexLog[512];
	glGetShaderInfoLog(vertexShader, 512, nullptr, vertexLog);
	std::cout << vertexLog << std::endl;

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragString = readFile(fragmentShaderPath);
	if (fragString.empty())
		return 0;
	const char* fss = fragString.c_str();
	glShaderSource(fragmentShader, 1, &fss, nullptr);
	glCompileShader(fragmentShader);
	GLchar fragmentLog[512];
	glGetShaderInfoLog(fragmentShader, 512, nullptr, fragmentLog);
	std::cout << fragmentLog << std::endl;

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	GLchar programLog[512];
	glGetProgramInfoLog(program, 512, nullptr, programLog);
	std::cout << programLog << std::endl;

	ShaderData data;
	data.id = program;
	data.vertexShaderPath = vertexShaderPath;
	data.fragmentShaderPath = fragmentShaderPath;
	shaders.push_back(data);
}

void ShaderManager::useShader(GLuint id) {
	if (currentShader != id){
		currentShader = id;
		glUseProgram(id);
	}
}