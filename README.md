# Cube Engine

## Roadmap
### Vision:
	Cube Engine is intended to be an open-source voxel game engine. Possible features include:
		- Level editor
		- Point/Click/Edit on level voxels
			- Modify color/texture
			- Add code to a voxel to give them behavior
		- Raytracing(???)
		- The sky is the limit
### Todo:
	- Create .obj file parser
	- Add keyboard manipulations to rotate the camera around scene and move around the editor
	- Improve shader control/scalability
## Documentation:
### Overview
#### The Engine
	The engine itself mainly revolves around its three components:
		1. WindowManager - Responsible for handling window events
		2. UIManager	 - Responsible for most ImGui features and input processing
		3. Renderer		 - Responsible for most OpenGL/GLFW rendering done in the window
#### Other Classes
	- Shader: responible for loading in shaders from .glsl files and creating shader programs from them
	- Config: contains default parameters and program settings
	- RawModel: Contains VAO and Vertex information for a model
	- VertexObjectLoader: Generates VAOs and VBOs from a vertex array and returns a RawModel
### Style Guidelines:
	- Class names should begin with a capital letter and use CamelCase
	- Public class methods should begin with a capital letter and use CamelCase
	- Private class methods should begin with a lowercase letter and use camelCase
	- return values of void are replaced with std::optional<EngineError> and can be ignored if they are std::nullopt.
	- Non-void return values are replaced with std::optional<T> and if nullopt is returned, GetLastError should be called.
	- A non-optional return value means the function is guaranteed to work, and it should be marked "noexcept"
	- Private member variables should be prefaced with "m_"