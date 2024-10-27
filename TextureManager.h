#pragma once

#include "ResourceManager.h"
#include "Prerequisites.h"

class TextureManager : public ResourceManager
{
public:
	TextureManager();
	~TextureManager();

public:
	Texture* createTextureFromFile(const wchar_t* filePath);

public:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* filePath);
};


