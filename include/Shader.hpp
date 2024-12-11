#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <optional>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "EngineError.hpp"
#include "Config.hpp"

class Shader {
public:
	Shader();
	~Shader();
	std::optional<EngineError> Init();
	std::optional<EngineError> Init(const std::string& vertexPath, const std::string& fragmentPath);
	std::optional<EngineError> Use();
	std::optional<GLuint> GetId();
	EngineError GetLastError() noexcept; // Will always work
	std::optional<EngineError> SetBool(const std::string& name, bool value) const;
	std::optional<EngineError> SetInt(const std::string& name, int value) const;
	std::optional<EngineError> SetFloat(const std::string& name, float value) const;

private:
	GLuint m_programID;
	GLboolean m_currentShaderValid;
	EngineError m_lastError;
	std::optional<GLuint> loadShader(const std::string& path, GLenum type);
	std::optional<std::string> readFile(const std::string& path);
};