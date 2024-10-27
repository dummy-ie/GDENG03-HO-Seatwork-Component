#pragma once

#include <string>

class Resource
{
protected:
	std::wstring fullPath;

public:
	Resource(const wchar_t* fullPath);
	virtual ~Resource();
};