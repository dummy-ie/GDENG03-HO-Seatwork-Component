#pragma once

#include <unordered_map>
#include <string>

#include "Prerequisites.h"

	class ResourceManager
	{
	protected:
		std::unordered_map<std::wstring, Resource*> mapResources;

	protected:
		ResourceManager();
		~ResourceManager();

	public:
		Resource* createResourceFromFile(const wchar_t* filePath);

	protected:
		virtual Resource* createResourceFromFileConcrete(const wchar_t* filePath) = 0;
	};


