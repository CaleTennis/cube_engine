#pragma once
#include <imgui.h>
#include <optional>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "EngineError.hpp"

class UIManager
{
public:
	UIManager();
	~UIManager();
	std::optional<EngineError> Init(GLFWwindow *window);

	std::optional<EngineError> ProcessInput();
	std::optional<EngineError> BuildUI();
	std::optional<EngineError> UpdateAndRenderPlatformWindows();

	EngineError GetLastError() noexcept;
private:
	std::optional<EngineError> buildMainMenuBar();

	ImGuiContext *m_currentContext;
	ImGuiStyle *m_style;
	ImGuiIO *m_currentIO;
	GLFWwindow *m_window;
	EngineError m_lastError;

	bool m_show_engine_about;
	void showEngineAboutWindow();
};