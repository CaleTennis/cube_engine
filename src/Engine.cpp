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
	if(Init().has_value())
		glfwTerminate();
}

std::optional<EngineError> Engine::Init()
{
	EECHECK(m_windowManager, Init())

	std::optional<GLFWwindow*> window = m_windowManager.GetWindow();

	VALCHECK(window, EngineError::EE_WINDOW_MANAGER_INIT_BUT_NO_WINDOW);
	EECHECK(m_uiManager, Init(window.value()));
	
	EECHECK(m_renderer, Init(window.value()));

	m_lastError = EngineError::EE_OK;
	std::cout << "Engine initialization successfully completed." << std::endl;
	return std::nullopt;
}

std::optional<EngineError> Engine::Run()
{
	while (m_windowManager.GetWindowShouldClose().has_value() && (m_windowManager.GetWindowShouldClose().value() == false))
	{
		EECHECK(m_windowManager, PollAndClear());
		EECHECK(m_uiManager, ProcessInput());
		EECHECK(m_renderer, Update());

		EECHECK(m_uiManager, BuildUI());
		EECHECK(m_renderer, Render());
		EECHECK(m_windowManager, Render());
		EECHECK(m_uiManager, UpdateAndRenderPlatformWindows());
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
		std::cout << "Engine exited successfully." << std::endl;
		return 0;
	}
	else
	{
		std::cerr << "Engine encounted error #" << static_cast<int>(m_lastError) << std::endl;
		return static_cast<int>(m_lastError);
	}
}