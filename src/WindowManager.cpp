#include "WindowManager.hpp"
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>

WindowManager::WindowManager() :
	m_window(nullptr),
	m_lastError(EngineError::EE_OK),
	m_windowShouldClose(false)
{}

WindowManager::~WindowManager()
{
	// Not needed since using GLFWwindowPtr
	//if(m_window)
	//	glfwDestroyWindow(m_window);
}

std::optional<EngineError> WindowManager::Init()
{
	// Initialize GLFW
	if (!glfwInit())
	{
		std::cerr << "ERROR::GLFW::INIT::INITIALIZATION_FAILED" << std::endl;
		m_lastError = EngineError::EE_GLFW_INIT_FAILED;
		return m_lastError;
	}

	// Give GLFW guidance for window creation
	// GLFW Version 3.30
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Only using core functionality
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (Config::MAXIMIZE_WINDOW_ON_START)
		glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
	
	// Create GLFW Window
	m_window = glfwCreateWindow(
		Config::WINDOW_WIDTH,
		Config::WINDOW_HEIGHT,
		Config::WINDOW_NAME,
		NULL,
		NULL);

	if (!m_window)
	{
		std::cerr << "ERROR::GLFW::WINDOW::CREATION_FAILED" << std::endl;
		m_lastError = EngineError::EE_GLFW_WINDOW_CREATION_FAILED;
		return m_lastError;
	}

	if (Config::CENTER_WINDOW_ON_START && !Config::MAXIMIZE_WINDOW_ON_START)
	{
		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwSetWindowPos(m_window, (mode->width / 2) - Config::WINDOW_WIDTH / 2, (mode->height / 2) - Config::WINDOW_HEIGHT / 2);

	}

	glfwMakeContextCurrent(m_window);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "ERROR::GLAD::INITIALIZATION_FAILED\n" << std::endl;
		glfwTerminate();
		m_lastError = EngineError::EE_GLAD_INIT_FAILED;
		return m_lastError;
	}

	enableReportGlErrors();

	if (Config::VSYNC_ENABLED)
		glfwSwapInterval(1);

	return std::nullopt;
}
std::optional<EngineError> WindowManager::PollAndClear()
{
	glfwPollEvents();

	int display_w, display_h;
	glfwGetFramebufferSize(m_window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return std::nullopt;
}

std::optional<EngineError> WindowManager::Render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwSwapBuffers(m_window);
	return std::nullopt;
}

std::optional<bool> WindowManager::GetWindowShouldClose()
{
	if (!m_window)
	{
		m_lastError = EngineError::EE_GET_WINDOW_INVALID_WINDOW;
		return std::nullopt;
	}

	return static_cast<bool>(glfwWindowShouldClose(m_window));
}

std::optional<GLFWwindow *> WindowManager::GetWindow()
{
	if (!m_window)
	{
		m_lastError = EngineError::EE_GET_WINDOW_INVALID_WINDOW;
		return std::nullopt;
	}
	return m_window;
}

EngineError WindowManager::GetLastError() noexcept { return m_lastError; }