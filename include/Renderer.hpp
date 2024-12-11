#pragma once
#include <optional>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Shader.hpp"
#include "Config.hpp"
#include "VertexObjectLoader.hpp"

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

	Shader m_currShader;
	RawModel m_demoModel;
	void renderRawModel(RawModel model);
	glm::highp_mat4 applyRotation(RawModel model, glm::vec3 axis = glm::vec3(0.4f, 1.0f, 0.1f), float rotationSpeed = 35.0f);

	glm::mat4 m_projectionMatrix;
	glm::mat4 m_model = glm::mat4(1.0f);
	glm::mat4 m_view;
	GLint m_matrixID;
	glm::mat4 m_mvp;

	EngineError m_lastError;

	// TODO: setup loading vertices from file
    GLfloat m_vertices[108] = {
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