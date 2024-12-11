#pragma once

namespace Config {

	static constexpr char CUBE_ENGINE_CURRENT_VERSION[] = "0.0.1";

	// OpenGL
	// Window
	static constexpr int WINDOW_WIDTH = 800;
	static constexpr int WINDOW_HEIGHT = 600;
	static constexpr char WINDOW_NAME[] = "My Project";
	static constexpr bool FULLSCREEN_ENABLED = false;
	static constexpr bool VSYNC_ENABLED = false;
	static constexpr bool MAXIMIZE_WINDOW_ON_START = true;
	static constexpr bool CENTER_WINDOW_ON_START = true;

	// UI
	static constexpr int DEFAULT_UI_FONT_SIZE = 40;
	static constexpr char DEFAULT_FONT_PATH[] = "fonts/OregonLDO_Regular.ttf";

	// Shaders
	static constexpr char GLSL_VERSION[] = "#version 330";
	static constexpr char DEFAULT_VERTEX_SHADER_PATH[] = "shaders/defaultVertexShader.glsl";
	static constexpr char DEFAULT_FRAGMENT_SHADER_PATH[] = "shaders/defaultFragmentShader.glsl";
}