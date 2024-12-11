#include "Shader.hpp"

Shader::Shader() :
	m_programID(0),
	m_currentShaderValid(false),
	m_lastError(EngineError::EE_OK)
{};

std::optional<EngineError> Shader::Init()
{
	return Shader::Init("", "");
}

std::optional<EngineError> Shader::Init(const std::string& vertexPath, const std::string& fragmentPath)
{
	std::optional<GLuint> vertexShader = loadShader(vertexPath, GL_VERTEX_SHADER);
	VALCHECK(vertexShader, m_lastError);

	std::optional<GLuint> fragmentShader = loadShader(fragmentPath, GL_FRAGMENT_SHADER);
	VALCHECK(fragmentShader, m_lastError);

	m_programID = glCreateProgram();
	glAttachShader(m_programID, vertexShader.value());
	glAttachShader(m_programID, fragmentShader.value());
	glLinkProgram(m_programID);

	GLint success;
	char infoLog[512];

	// check for shader linking errors
	glGetProgramiv(m_programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(m_programID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		m_lastError = EngineError::EE_SHADER_INIT_PROGRAM_LINKING_FAILED;
		return m_lastError;
	}

	glDetachShader(m_programID, vertexShader.value());
	glDetachShader(m_programID, fragmentShader.value());

	glDeleteShader(vertexShader.value());
	glDeleteShader(fragmentShader.value());
	m_currentShaderValid = true;

	return std::nullopt;
}

Shader::~Shader()
{
	m_currentShaderValid = false;
	glDeleteProgram(m_programID);
}

std::optional<EngineError> Shader::Use()
{
	ASSERT_TRUE(m_currentShaderValid, EngineError::EE_SHADER_USE_BEFORE_INIT);
	
	glUseProgram(m_programID);
	return std::nullopt;
}

std::optional<GLuint> Shader::GetId()
{
	if(!m_currentShaderValid)
	{
		m_lastError = EngineError::EE_SHADER_GETID_BEFORE_INIT;
		return std::nullopt;
	}

	return m_programID;
}

EngineError Shader::GetLastError() noexcept
{
	return m_lastError;
}

// TODO: validate success of glUniform1i before returning
std::optional<EngineError> Shader::SetBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_programID, name.c_str()), (int)value);
	return std::nullopt;
}
// TODO: validate success of glUniform1i before returning
std::optional<EngineError> Shader::SetInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_programID, name.c_str()), value);
	return std::nullopt;
}
// TODO: validate success of glUniform1f before returning
std::optional<EngineError> Shader::SetFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_programID, name.c_str()), value);
	return std::nullopt;
}

std::optional<GLuint> Shader::loadShader(const std::string& path, GLenum type)
{
	std::optional<std::string> readResult;
	// Replace path with default 
	if (path.empty())
	{
		switch (type)
		{
		case GL_VERTEX_SHADER:
			readResult = readFile(Config::DEFAULT_VERTEX_SHADER_PATH);
			break;
		case GL_FRAGMENT_SHADER:
			readResult = readFile(Config::DEFAULT_FRAGMENT_SHADER_PATH);
			break;
		default:
		{
			std::cout << "ERROR::SHADER::UNKNOWN_SHADER_TYPE::UNKNOWN_ERROR" << std::endl;
			m_lastError = EngineError::EE_SHADER_UNKNOWN_SHADER_TYPE_IN_LOADING;
			break;
			return std::nullopt;
		}
		};
	}
	else
		readResult = readFile(path);

	if (!readResult.has_value())
	{
		return std::nullopt;
	}

	std::string code = readResult.value();
	const char* codeCStr = code.c_str();
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &codeCStr, nullptr);
	glCompileShader(shader);

	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) // shader compilation failed
	{
		switch (type)
		{
		case GL_VERTEX_SHADER:
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			m_lastError = EngineError::EE_SHADER_VERTEX_COMPILATION_FAILED;
			break;
		case GL_FRAGMENT_SHADER:
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			m_lastError = EngineError::EE_SHADER_FRAGMENT_COMPILATION_FAILED;
			break;
		default:
			glGetShaderInfoLog(shader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::UNKNOWN_SHADER_TYPE::UNKNOWN_ERROR\n" << infoLog << std::endl;
			m_lastError = EngineError::EE_SHADER_UNKNOWN_SHADER_TYPE_IN_LOADING;
			break;
		}
		return std::nullopt;
	}

	return shader;
}

// Any non-empty value should be considered a successful opening and scanning
std::optional<std::string> Shader::readFile(const std::string& path)
{ 
	std::string shaderCode;
	std::ifstream shaderFile;
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		shaderFile.open(path);
		if (!shaderFile.is_open()) {
			throw new std::ifstream::failure("Could not open file: \"" + path + "\"");
		}
		std::stringstream shaderStream;
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FAILED_TO_READ_FILE: " << e.what() << std::endl;
		m_lastError = EngineError::EE_SHADER_FAILED_TO_READ_FILE;
		return std::nullopt;
	}

	return shaderCode;
}
