#include "MeshManager.h"

#if __cplusplus <= 201402L 
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#endif

#if __cplusplus >= 201703L
#include <filesystem>
#endif

#include "Logger.h"
#include "Mesh.h"


using namespace graphics;

MeshManager::MeshManager() : ResourceManager()
{
	debug::Logger::log(this, "Initialized");
}

MeshManager::~MeshManager()
{
	debug::Logger::log(this, "Destroyed");
}

Mesh* MeshManager::createMeshFromFile(const wchar_t* filePath)
{
#if (_MSC_VER >= 1900 && _MSC_VER <= 1916)  || ( _MSC_VER >= 1920 && __cplusplus <= 201402L) 
	std::wstring fullPath = std::experimental::filesystem::absolute(filePath);
#endif

#if _MSC_VER >= 1920 && __cplusplus > 201402L 
	std::wstring fullPath = std::filesystem::absolute(filePath);
#endif

	if (this->mapResources[fullPath] == NULL)
	{
		debug::Logger::log(L"Created Mesh from path : " + fullPath);
		this->mapResources[fullPath] = this->createResourceFromFileConcrete(filePath);
	}

	return (Mesh*)this->mapResources[fullPath];
}

Resource* MeshManager::createResourceFromFileConcrete(const wchar_t* filePath)
{
	Mesh* mesh = nullptr;
	try
	{
		mesh = new Mesh(filePath);
	}
	catch (...) {}

	return mesh;
}