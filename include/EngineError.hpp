#pragma once

// VALCHECK - Ensures that x has a value, otherwise returns y
// x -> std::optional<T> to ensure is not std::nullopt
// y -> std::optional<EngineError> to return if x is std::nullopt
#ifndef VALCHECK
#define VALCHECK(x, y) if(!(x).has_value()) { m_lastError = y; return m_lastError;}
#endif
// EECHECK - Assert that the std::optional<EngineError> returned OK
// x -> base class
// y -> function to call and check return value ofCa
// z -> message to print on fail
#ifndef EECHECK
#define EECHECK(x,y) if( (x).y.has_value()) { m_lastError = (x).GetLastError(); return m_lastError;}
#endif

// EECHECK_M - Same as EECHECK but allows printing of error message
#ifndef EECHECK_M
#define EECHECK_M(x,y) if( (x).y.has_value()) { std::cout << (z) << std::endl; m_lastError = (x).GetLastError(); return m_lastError;}
#endif

// PTRCHECK - Assert that the pointer tested is not a nullptr
// x -> pointer to test
// y -> error to return if pointer is a nullptr
// z -> message to print if pointer is a nullptr
#ifndef PTRCHECK
#define PTRCHECK(x,y) if(!(x)) { m_lastError = (y); return m_lastError;}
#endif

// PTRCHECK_M - Same as PTRCHECK but allows printing of error message
#ifndef PTRCHECK_M
#define PTRCHECK_M(x,y,z) if(!(x)) { std::cout << (z) << std::endl; m_lastError = (y); return m_lastError;}
#endif

// ASSERT_TRUE - Assert x, otherwise y
// x -> bool to assert true
// y -> std::optional<EngineError> to return
#ifndef ASSERT_TRUE
#define ASSERT_TRUE(x,y) if(!(x)) { m_lastError = y; return m_lastError;}
#endif

#ifndef ASSERT_TRUE_M
#define ASSERT_TRUE_M(x,y,z) if(!(x)) { std::cerr << z << std::endl; m_lastError = y; return m_lastError;}
#endif

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