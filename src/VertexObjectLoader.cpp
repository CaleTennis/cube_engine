#include "VertexObjectLoader.hpp"

std::vector<GLuint> VertexObjectLoader::m_vaos;
std::vector<GLuint> VertexObjectLoader::m_vbos;
std::mutex VertexObjectLoader::m_mutex;

RawModel VertexObjectLoader::LoadToVAO(const float positions[], size_t size)
{
	std::lock_guard<std::mutex> lock(m_mutex); // Ensure thread safety
	
	int vaoID = createVAO();
	storeDataInAttribList(0, positions, size);
	unbindVAO();
	return RawModel(vaoID, size / 3);
}

int VertexObjectLoader::createVAO()
{
	GLuint vaoID;
	glGenVertexArrays(1, &vaoID);
	if (vaoID == 0)
	{
		std::cerr << "VERTEX_OBJECT_LOADER::CREATE_VAO::FAILED_TO_GENERATE_VAO" << std::endl;
	}
	else
	{
		m_vaos.push_back(vaoID);
	}
	glBindVertexArray(vaoID);
	return vaoID;
}

void VertexObjectLoader::storeDataInAttribList(int attribNum, const float data[], size_t size)
{
	GLuint vboID = 0;
	glGenBuffers(1, &vboID);
	if (vboID == 0)
	{
		std::cerr << "VERTEX_OBJECT_LOADER::STORE_DATA_IN_ATTRIB_LIST::FAILED_TO_GENERATE_VBO" << std::endl;
	}
	else
	{
		m_vbos.push_back(vboID);
		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);

		glVertexAttribPointer(
			attribNum, // Attribute index to store at
			3,		   // Size of each element (3 for Vec3d)
			GL_FLOAT,  // Type
			GL_FALSE,  // Normalized?
			0,		   // Distance between each vertex
			(void*)0);		   // Offset

		glEnableVertexAttribArray(attribNum);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
void VertexObjectLoader::Cleanup()
{
	std::lock_guard<std::mutex> lock(m_mutex);

	for (GLuint& vao : m_vaos)
		glDeleteVertexArrays(1, &vao);
	for (GLuint& vbo : m_vbos)
		glDeleteBuffers(1, &vbo);

	m_vaos.clear();
	m_vbos.clear();
}

void VertexObjectLoader::unbindVAO()
{
	glBindVertexArray(0);
}