#include "TextureManager.h"

#if __cplusplus <= 201402L 
#define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#include <experimental/filesystem>
#endif

#if __cplusplus >= 201703L
#include <filesystem>
#endif

#include "Logger.h"
#include "Texture.h"


using namespace graphics;

TextureManager::TextureManager() : ResourceManager() 
{
	debug::Logger::log(this, "Initialized");
}

TextureManager::~TextureManager()
{
	debug::Logger::log(this, "Destroyed");
}

Texture* TextureManager::createTextureFromFile(const wchar_t* filePath)
{
#if (_MSC_VER >= 1900 && _MSC_VER <= 1916)  || ( _MSC_VER >= 1920 && __cplusplus <= 201402L) 
	std::wstring fullPath = std::experimental::filesystem::absolute(filePath);
#endif

#if _MSC_VER >= 1920 && __cplusplus > 201402L 
	std::wstring fullPath = std::filesystem::absolute(filePath);
#endif

	if (this->mapResources[fullPath] == NULL)
	{
		debug::Logger::log(L"Created Texture from path : " + fullPath);
		this->mapResources[fullPath] = this->createResourceFromFileConcrete(filePath);
	}

	return (Texture*)this->mapResources[fullPath];
}

Resource* TextureManager::createResourceFromFileConcrete(const wchar_t* filePath)
{
	Texture* texture = nullptr;
	try
	{
		texture = new Texture(filePath);
	}
	catch(...) {}

	return texture;
}