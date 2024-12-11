#include "RawModel.hpp"


RawModel::RawModel() :
	m_vaoID(0), m_vertexCount(0), m_hasBeenInit(false)
{}

RawModel::RawModel(int vaoID, int vertexCount) :
	m_vaoID(vaoID), m_vertexCount(vertexCount), m_hasBeenInit(true)
{}

void RawModel::Init(int vaoID, int vertexCount)
{
	m_vaoID = vaoID;
	m_vertexCount = vertexCount;
	m_hasBeenInit = true;
}

int RawModel::GetVaoID()
{
	if (!m_hasBeenInit) {
		std::cerr << "ERROR::RAWMODEL::GET_VAO_ID_CALLED_BEFORE_INIT" << std::endl;
		return -1;
	}
	return m_vaoID;
}

int RawModel::GetVertexCount()
{
	if (!m_hasBeenInit) {
		std::cerr << "ERROR::RAWMODEL::GET_VERTEX_COUNT_CALLED_BEFORE_INIT" << std::endl;
		return -1;
	}
	return m_vertexCount;
}