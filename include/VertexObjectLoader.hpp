#pragma once
#include <vector>
#include <mutex>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "RawModel.hpp"

class VertexObjectLoader
{
public:
	static RawModel LoadToVAO(const float positions[], size_t size);
	static void Cleanup();
private:
	static int createVAO();
	static void storeDataInAttribList(int attribNum, const float data[], size_t size);
	static void unbindVAO();

	static std::vector<GLuint> m_vaos;
	static std::vector<GLuint> m_vbos;
	static std::mutex m_mutex;
};