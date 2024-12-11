#pragma once
#include <optional>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Shader.hpp"
#include "Config.hpp"


class Renderer
{
public:
	Renderer();
	~Renderer();

	std::optional<EngineError> Init(GLFWwindow *window);
	std::optional<EngineError> Render();
	std::optional<EngineError> Update();

	EngineError GetLastError() noexcept;
private:
	GLFWwindow* m_window;
	GLuint m_currVAO;
	GLuint m_currVBO;
	Shader m_currShader;


	glm::mat4 m_projectionMatrix;
	glm::mat4 m_model = glm::mat4(1.0f);
	glm::mat4 m_view;
	GLint m_matrixID;
	glm::mat4 m_mvp;

	EngineError m_lastError;

	// TODO: setup loading vertices from file
    GLfloat vertices[108] = {
   -1.0f,-1.0f,-1.0f, // triangle 1 : begin
   -1.0f,-1.0f, 1.0f,
   -1.0f, 1.0f, 1.0f, // triangle 1 : end
   1.0f, 1.0f,-1.0f, // triangle 2 : begin
   -1.0f,-1.0f,-1.0f,
   -1.0f, 1.0f,-1.0f, // triangle 2 : end
   1.0f,-1.0f, 1.0f,
   -1.0f,-1.0f,-1.0f,
   1.0f,-1.0f,-1.0f,
   1.0f, 1.0f,-1.0f,
   1.0f,-1.0f,-1.0f,
   -1.0f,-1.0f,-1.0f,
   -1.0f,-1.0f,-1.0f,
   -1.0f, 1.0f, 1.0f,
   -1.0f, 1.0f,-1.0f,
   1.0f,-1.0f, 1.0f,
   -1.0f,-1.0f, 1.0f,
   -1.0f,-1.0f,-1.0f,
   -1.0f, 1.0f, 1.0f,
   -1.0f,-1.0f, 1.0f,
   1.0f,-1.0f, 1.0f,
   1.0f, 1.0f, 1.0f,
   1.0f,-1.0f,-1.0f,
   1.0f, 1.0f,-1.0f,
   1.0f,-1.0f,-1.0f,
   1.0f, 1.0f, 1.0f,
   1.0f,-1.0f, 1.0f,
   1.0f, 1.0f, 1.0f,
   1.0f, 1.0f,-1.0f,
   -1.0f, 1.0f,-1.0f,
   1.0f, 1.0f, 1.0f,
   -1.0f, 1.0f,-1.0f,
   -1.0f, 1.0f, 1.0f,
   1.0f, 1.0f, 1.0f,
   -1.0f, 1.0f, 1.0f,
   1.0f,-1.0f, 1.0f
    };
};