#pragma once

#include "ResourceManager.h"
#include "Prerequisites.h"

class MeshManager : public ResourceManager
{
public:
	Mesh* createMeshFromFile(const wchar_t* filePath);

protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* filePath);
	friend class graphics::GraphicsEngine;

private:
	MeshManager();
	~MeshManager() override;
};