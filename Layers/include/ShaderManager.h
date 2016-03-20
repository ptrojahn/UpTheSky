#pragma once

#include "glFunctions.h"

#include <string>
#include <vector>

struct ShaderData
{
	GLuint id;
	std::string vertexShaderPath;
	std::string fragmentShaderPath;
	std::vector<int> attributeSizes;
};

class ShaderManager
{
public:
	static ShaderManager& instance() {
		static ShaderManager shaderManager;
		return shaderManager;
	}
	GLuint createShader(std::string vertexShaderSource, std::string fragmentShaderSource);
	void useShader(GLuint id);
private:
	GLuint currentShader;
	std::vector<ShaderData> shaders;
};