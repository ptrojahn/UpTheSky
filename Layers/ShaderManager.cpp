#include "ShaderManager.h"

#include "SDL_rwops.h"

#include <iostream>
#include <fstream>
#include <sstream>

std::string readFile(std::string path) {
	SDL_RWops* file = SDL_RWFromFile(path.c_str(), "r");
	if (file == nullptr){
		std::cout << "Can't find file: " << path.c_str() << std::endl;
		return std::string();
	}
	std::vector<char> fileData(SDL_RWsize(file));
	SDL_RWread(file, &fileData[0], fileData.size(), 1);
	return std::string(&fileData[0], fileData.size());
}

GLuint ShaderManager::createShader(std::string vertexShaderPath, std::string fragmentShaderPath) {
	for (ShaderData shaderData : shaders)
		if (shaderData.vertexShaderPath == vertexShaderPath && shaderData.fragmentShaderPath == fragmentShaderPath)
			return shaderData.id;

	ShaderData data;
	data.vertexShaderPath = vertexShaderPath;
	data.fragmentShaderPath = fragmentShaderPath;
	GLuint program = glCreateProgram();

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	std::string vertString = readFile(vertexShaderPath);
	if (vertString.empty())
		return 0;
	const char* vss = vertString.c_str();
	glShaderSource(vertexShader, 1, &vss, nullptr);
	glCompileShader(vertexShader);
	glAttachShader(program, vertexShader);
	GLchar vertexLog[512];
	glGetShaderInfoLog(vertexShader, 512, nullptr, vertexLog);
	std::cout << vertexLog << std::endl;

	//Remove comments from the vertex shader source
	int commentIndex = 0;
	while ((commentIndex = vertString.find("/*", commentIndex)) != std::string::npos) {
		int commentIndexEnd = vertString.find("*/", commentIndex);
		if (commentIndexEnd == std::string::npos)
			break;
		vertString.replace(commentIndex, commentIndexEnd - commentIndex, "");
	}
	commentIndex = 0;
	while ((commentIndex = vertString.find("//", commentIndex)) != std::string::npos){
		int commentIndexEnd = vertString.find("\n", commentIndex);
		if (commentIndexEnd == std::string::npos)
			commentIndexEnd = vertString.length();
		vertString.replace(commentIndex, commentIndexEnd - commentIndex, "");
	}

	//Assign ids to attributes
	int index = 0;
	int locationIndex = 0;
	while ((index = vertString.find("attribute", index)) != std::string::npos){
		index += 9;
		while (vertString[index] == ' ')
			index++;
		
		int typeEnd = vertString.find(' ', index);
		if (typeEnd == std::string::npos)
			continue;
		std::string type = vertString.substr(index, typeEnd - index);
		index = typeEnd;

		while (vertString[index] == ' ')
			index++;
		int nameEnd = vertString.find(';', index);
		if (nameEnd == std::string::npos)
			continue;
		std::string name = vertString.substr(index, nameEnd-index);
		
		if (type == "float")
			data.attributeSizes.push_back(1);
		else if (type == "vec2")
			data.attributeSizes.push_back(2);
		else if (type == "vec3")
			data.attributeSizes.push_back(3);
		else if (type == "vec4" || type == "mat2")
			data.attributeSizes.push_back(4);
		else if (type == "mat3")
			data.attributeSizes.push_back(9);
		else if (type == "mat4")
			data.attributeSizes.push_back(12);
		else{
			std::cout << "Unknown attribute type " << type << std::endl;
			continue;
		}
		glBindAttribLocation(program, locationIndex, name.c_str());
		locationIndex++;
	}

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
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);
	data.id = program;
	GLchar programLog[512];
	glGetProgramInfoLog(program, 512, nullptr, programLog);
	std::cout << programLog << std::endl;

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	shaders.push_back(data);
	return program;
}

void ShaderManager::useShader(GLuint id) {
	if (currentShader != id){
		currentShader = id;
		glUseProgram(id);
	}
}

std::vector<int> ShaderManager::getAttributesSize(GLuint shader) {
	for (ShaderData data : shaders){
		if (data.id == shader)
			return data.attributeSizes;
	}
	return std::vector <int>();
}