#include "Engine.hpp"
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>

Engine::Engine() :
	m_lastError(EngineError::EE_OK),
	m_windowManager(WindowManager()),
	m_uiManager(UIManager()),
	m_renderer(Renderer())
{
	Init();
}

std::optional<EngineError> Engine::Init()
{
	if (m_windowManager.Init().has_value())
	{
		m_lastError = m_windowManager.GetLastError();
		return m_lastError;
	};

	std::optional<GLFWwindow*> window = m_windowManager.GetWindow();

	if (window.has_value() && m_uiManager.Init(window.value()).has_value())
	{
		m_lastError = m_uiManager.GetLastError();
		return m_lastError;
	}
	else if(!window.has_value())
	{
		m_lastError = EngineError::EE_WINDOW_MANAGER_INIT_BUT_NO_WINDOW;
		return m_lastError;
	}

	if (window.has_value() && m_renderer.Init(window.value()).has_value())
	{
		m_lastError = m_uiManager.GetLastError();
		return m_lastError;
	}

	m_lastError = EngineError::EE_OK;
	std::cout << "Engine::Init successfully completed" << std::endl;
	return std::nullopt;
}

std::optional<EngineError> Engine::Run()
{
	while (m_windowManager.GetWindowShouldClose().has_value() && (m_windowManager.GetWindowShouldClose().value() == false))
	{
		if(m_windowManager.PollAndClear().has_value()) return m_windowManager.GetLastError();
		if(m_uiManager.ProcessInput().has_value()) return m_uiManager.GetLastError();
		if(m_renderer.Update().has_value()) return m_renderer.GetLastError();

		if(m_uiManager.BuildUI().has_value()) return m_uiManager.GetLastError();
		if(m_renderer.Render().has_value()) return m_renderer.GetLastError();
		if(m_windowManager.Render()) return m_windowManager.GetLastError();
		if(m_uiManager.UpdateAndRenderPlatformWindows().has_value()) return m_uiManager.GetLastError();
	}
	return std::nullopt;
}

void Engine::quit() const
{
	glfwTerminate();
}

EngineError Engine::GetLastError() { return m_lastError; }

int Engine::GetExitResult() noexcept
{
	if (m_lastError == EngineError::EE_OK)
	{
		std::cout << "Engine exited successfully" << std::endl;
		return 0;
	}
	else
	{
		std::cerr << "Engine encounted error #" << static_cast<int>(m_lastError) << std::endl;
		return static_cast<int>(m_lastError);
	}
}