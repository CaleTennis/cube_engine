#pragma once
#include "WindowManager.hpp"
#include "EngineError.hpp"
#include "UIManager.hpp"
#include "Renderer.hpp"

class Engine
{
public:
	Engine();
	
	std::optional<EngineError> Init();

	std::optional<EngineError> Run();

	EngineError GetLastError();
	int GetExitResult() noexcept;

private:
	void quit() const;

	EngineError m_lastError;
	WindowManager m_windowManager;
	UIManager m_uiManager;
	Renderer m_renderer;
};