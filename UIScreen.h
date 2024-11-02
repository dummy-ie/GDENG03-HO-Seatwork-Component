#pragma once

#include <string>

typedef std::string String;

class UIManager;

class UIScreen
{
protected:
	typedef std::string String;

protected:
	String name;
	bool isActive = true;

protected:
	friend class UIManager;

protected:
	UIScreen(String name);
	~UIScreen();

protected:
	String getName();
	virtual void draw() = 0;

public:
	void setActive(bool isActive);
	bool getIsActive();
};

