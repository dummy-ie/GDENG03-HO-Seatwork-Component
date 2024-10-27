#include "ResourceManager.h"

#if __cplusplus <= 201402L 
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#endif

#if __cplusplus >= 201703L
#include <filesystem>
#endif

using namespace graphics;


ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
}

Resource* ResourceManager::createResourceFromFile(const wchar_t* filePath)
{
#if (_MSC_VER >= 1900 && _MSC_VER <= 1916)  || ( _MSC_VER >= 1920 && __cplusplus <= 201402L) 
	std::wstring fullPath = std::experimental::filesystem::absolute(filePath);
#endif

#if _MSC_VER >= 1920 && __cplusplus > 201402L 
	std::wstring fullPath = std::filesystem::absolute(filePath);
#endif
	auto it = mapResources.find(fullPath);

	if (it != mapResources.end())
		return it->second;

	Resource* rawResource = this->createResourceFromFileConcrete(fullPath.c_str());

	if (rawResource)
	{
		mapResources[fullPath] = rawResource;
		return rawResource;
	}

	return nullptr;
}
