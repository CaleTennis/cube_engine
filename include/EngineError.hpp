#pragma once

enum class EngineError
{
	EE_OK,
	EE_GLFW_INIT_FAILED,
	EE_GLFW_WINDOW_CREATION_FAILED,
	EE_GLAD_INIT_FAILED,

	// Engine
	EE_WINDOW_MANAGER_INIT_BUT_NO_WINDOW,

	// Window Manager
	EE_GET_WINDOW_INVALID_WINDOW,

	// User Interface
	EE_UIMANAGER_INIT_INVALID_WINDOW_PROVIDED,
	EE_IMGUI_CREATE_CONTEXT_FAILED,
	EE_IMGUI_GET_IO_FAILED,
	EE_IMGUI_GET_STYLE_FAILED,
	EE_UIMANAGER_INIT_FONT_NOT_FOUND,
	// Renderer
	EE_RENDERER_INIT_INVALID_WINDOW_PROVIDED,

	// Shaders
	EE_SHADER_FAILED_TO_READ_FILE,
	EE_SHADER_VERTEX_COMPILATION_FAILED,
	EE_SHADER_FRAGMENT_COMPILATION_FAILED,
	EE_SHADER_UNKNOWN_SHADER_TYPE_IN_LOADING,
	EE_SHADER_INIT_PROGRAM_LINKING_FAILED,
	EE_SHADER_USE_BEFORE_INIT,
	EE_SHADER_GETID_BEFORE_INIT
};