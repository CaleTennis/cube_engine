#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <openglErrorReporting.h>
#include <iostream>
#include <optional>
#include "EngineError.hpp"
#include "Config.hpp"

class WindowManager
{
public:
	WindowManager();
	~WindowManager();
	std::optional<EngineError> Init();

	std::optional<EngineError> PollAndClear();	// Should always be called first in engine loop
	std::optional<EngineError> Render();

	std::optional<bool> GetWindowShouldClose();
	std::optional<GLFWwindow *> GetWindow();
	EngineError GetLastError() noexcept;

private:
	GLFWwindow *m_window;
	EngineError m_lastError;
	bool m_windowShouldClose;
};