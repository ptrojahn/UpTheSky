#pragma once

#include "Component.h"

#include "glFunctions.h"
#include <vector>
#include <string>

enum UniformType
{
	UniformFloat,
	UniformFloat2,
	UniformFloat3,
	UniformFloat4,
	UniformBool,
	UniformInt
};

class Uniform
{
public:
	Uniform(std::string name, float v0) : name(name), type(UniformFloat) {
		data.resize(sizeof(float));
		*(float*)&data[0] = v0;
		location = 0;
	}
	Uniform(std::string name, float v0, float v1) : name(name), type(UniformFloat2) {
		data.resize(sizeof(float) * 2);
		*(float*)&data[0] = v0;
		*(float*)&data[sizeof(float)] = v1;
		location = 0;
	}
	Uniform(std::string name, float v0, float v1, float v2) : name(name), type(UniformFloat3) {
		data.resize(sizeof(float) * 3);
		*(float*)&data[0] = v0;
		*(float*)&data[sizeof(float)] = v1;
		*(float*)&data[sizeof(float) * 2] = v2;
		location = 0;
	}
	Uniform(std::string name, float v0, float v1, float v2, float v3) : name(name), type(UniformFloat4) {
		data.resize(sizeof(float)*4);
		*(float*)&data[0] = v0;
		*(float*)&data[sizeof(float)] = v1;
		*(float*)&data[sizeof(float) * 2] = v2;
		*(float*)&data[sizeof(float) * 3] = v3;
		location = 0;
	}
	Uniform(std::string name, bool v0) : name(name), type(UniformBool) {
		data.resize(sizeof(bool));
		*(bool*)&data[0] = v0;
		location = 0;
	}
	Uniform(std::string name, int v0) : name(name), type(UniformInt) {
		data.resize(sizeof(int));
		*(int*)&data[0] = v0;
		location = 0;
	}
	Uniform(const Uniform& uniform) {
		name = uniform.name;
		type = uniform.type;
		data.resize(uniform.data.size());
		std::memcpy(&data[0], &uniform.data[0], uniform.data.size());
		location = 0;
	}

	std::string name;
	UniformType type;
	std::vector<char> data;
	GLuint location;
};

class UniformsComponent : public BaseComponent<UniformsComponent>
{
public:
	UniformsComponent(std::vector<Uniform> uniforms) : uniforms(uniforms){
	}
	UniformsComponent(std::initializer_list<Uniform> uniforms) : uniforms(uniforms){
	}
	std::vector<Uniform> uniforms;
};