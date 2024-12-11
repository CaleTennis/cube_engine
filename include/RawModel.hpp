#pragma once

#include <iostream>

class RawModel {
public:
	RawModel();
	RawModel(int vaoID, int vertexCount);
	void Init(int vaoID, int vertexCount);
	int GetVaoID();
	int GetVertexCount();

private:
	int m_vaoID;
	int m_vertexCount;
	bool m_hasBeenInit;
};