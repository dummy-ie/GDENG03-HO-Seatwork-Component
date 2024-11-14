#pragma once

#include "DeviceContext.h"
#include "Resource.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

using namespace graphics;

class Mesh : public Resource
{
private:
	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
private:
	friend class graphics::DeviceContext;

public:
	Mesh(const wchar_t* fullPath);
	~Mesh() override;

public:
	VertexBuffer* getVertexBuffer();
	IndexBuffer* getIndexBuffer();
};

