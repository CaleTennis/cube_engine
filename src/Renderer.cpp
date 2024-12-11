#include "Renderer.hpp"

Renderer::Renderer() :
	m_window(nullptr),
	m_lastError(EngineError::EE_OK),
	m_currShader(Shader()),
	m_projectionMatrix(
		glm::perspective(
			glm::radians(45.0f),
			(float)Config::WINDOW_WIDTH / (float)Config::WINDOW_HEIGHT, 0.1f, 100.0f)),
	m_view(
		glm::lookAt(
			glm::vec3(4, 3, 3),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0)
		)),
	m_model(glm::mat4(1.0f)),
	m_mvp(m_projectionMatrix* m_view* m_model),
	m_matrixID(0),
	m_demoModel(RawModel())
{}

Renderer::~Renderer()
{
	VertexObjectLoader::Cleanup();
}

std::optional<EngineError> Renderer::Init(GLFWwindow *window)
{
	PTRCHECK_M(window,
		EngineError::EE_RENDERER_INIT_INVALID_WINDOW_PROVIDED,
		"ERROR::RENDERER::INIT::INVALID_WINDOW_PROVIDED");
	
	m_window = window;
	
	EECHECK(m_currShader, Init());

	std::optional<GLuint> currShaderID = m_currShader.GetId();
	VALCHECK(currShaderID, m_currShader.GetLastError());
		
	m_matrixID = glGetUniformLocation(currShaderID.value(), "MVP");
	
	m_demoModel = VertexObjectLoader::LoadToVAO(m_vertices, (sizeof(m_vertices)/(sizeof(*m_vertices))));
	m_currShader.Use();

	glEnable(GL_DEPTH_TEST); // enable depth-testing for z-culling
	glDepthFunc(GL_LESS); // set type of depth-test
	glShadeModel(GL_SMOOTH); // enable smooth shading

	return std::nullopt;
}

// TODO: will this ever fail?
std::optional<EngineError> Renderer::Render()
{
	m_currShader.Use();
	renderRawModel(m_demoModel);
	return std::nullopt;
}

// TODO: will this ever fail?
std::optional<EngineError> Renderer::Update()
{
	m_model = applyRotation(m_demoModel);

	m_mvp = m_projectionMatrix * m_view * m_model;	// Recalculate MVP matrix
	glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &m_mvp[0][0]);
	return std::nullopt;
}

EngineError Renderer::GetLastError() noexcept
{
	return m_lastError;
}

void Renderer::renderRawModel(RawModel model)
{
	glBindVertexArray(model.GetVaoID());
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	glDisableVertexAttribArray(0);
	glBindVertexArray(0);
}

glm::highp_mat4 Renderer::applyRotation(RawModel model, glm::vec3 axis, float rotationSpeed)
{
	float angle = static_cast<float>(glfwGetTime()) * glm::radians(rotationSpeed);
	return glm::rotate(glm::mat4(1.0f), angle, axis);
}