#pragma once

#include "ResourceManager.h"
#include "Prerequisites.h"

class TextureManager : public ResourceManager
{
public:
	Texture* createTextureFromFile(const wchar_t* filePath);

protected:
	virtual Resource* createResourceFromFileConcrete(const wchar_t* filePath);
	friend class graphics::GraphicsEngine;

private:
	TextureManager();
	~TextureManager() override;
};


