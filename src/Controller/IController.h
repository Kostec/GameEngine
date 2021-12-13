#pragma once

#include <functional>
#include <string>
#include <map>

class CustomKey;

class IController
{

public:
	IController();
	~IController();
	void setKey(const std::string description, CustomKey* key);
	void changeKey(const std::string description, int keycode);
	CustomKey* getKey(const std::string description) const;
	CustomKey* getKey(int keycode) const;

	void actionKey(const std::string description, bool pressed);
	void actionKey(int keycode, bool pressed);
private:
	std::map<int, std::string> keycodeDescriptions;
	std::map<std::string, CustomKey*> descriptionKeys;
};

