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
	m_mvp(m_projectionMatrix * m_view * m_model),
	m_matrixID(0),
	m_currVAO(0),
	m_currVBO(0)
{}

Renderer::~Renderer()
{
	glDeleteVertexArrays(1, &m_currVAO);
	glDeleteBuffers(1, &m_currVBO);
}

std::optional<EngineError> Renderer::Init(GLFWwindow *window)
{
	m_window = window;
	if (!m_window)
	{
		std::cerr << "ERROR::RENDERER::INIT::INVALID_WINDOW_PROVIDED" << std::endl;
		m_lastError = EngineError::EE_RENDERER_INIT_INVALID_WINDOW_PROVIDED;
		return m_lastError;
	}

	// Vertex data
	glGenVertexArrays(1, &m_currVAO);
	glGenBuffers(1, &m_currVBO);

	// Bind VAO first
	glBindVertexArray(m_currVAO);

	// Bind and set vertex buffer(s)
	glBindBuffer(GL_ARRAY_BUFFER, m_currVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	// Configure vertex attribute(s
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(0);

	if (m_currShader.Init("","").has_value())
	{
		m_lastError = m_currShader.GetLastError();
		return m_lastError;
	}

	std::optional<GLuint> currShaderID = m_currShader.GetId();
	if(currShaderID.has_value())
		m_matrixID = glGetUniformLocation(currShaderID.value(), "MVP");
	else
	{
		m_lastError = m_currShader.GetLastError();
		return m_lastError;
	}

	m_currShader.Use();

	glEnable(GL_DEPTH_TEST); // enable depth-testing for z-culling
	glDepthFunc(GL_LESS); // set type of depth-test
	glShadeModel(GL_SMOOTH); // enable smooth shading
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Nice perspective corrections

	return std::nullopt;
}

// TODO: will this ever fail?
std::optional<EngineError> Renderer::Render()
{
	glBindVertexArray(m_currVAO);
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
	return std::nullopt;
}

// TODO: will this ever fail?
std::optional<EngineError> Renderer::Update()
{
	float angle = static_cast<float>(glfwGetTime()) * glm::radians(35.0f);		// degrees per sec
	m_model = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.4f, 1.0f, 0.1f)); // rotate about y-axis

	m_mvp = m_projectionMatrix * m_view * m_model;	// Recalculate MVP matrix
	glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &m_mvp[0][0]);
	return std::nullopt;
}

EngineError Renderer::GetLastError() noexcept
{
	return m_lastError;
}