#include "IController.h"
#include "CustomKey.h"

IController::IController()
{

}

IController::~IController()
{
	keycodeDescriptions.clear();
	descriptionKeys.clear();
}

void IController::setKey(const std::string description, CustomKey* key)
{
	int keycode = key->getKeyNumber();
	keycodeDescriptions.emplace(keycode, description);
	descriptionKeys.emplace(description, key);
}

void IController::changeKey(const std::string description, int keycode)
{
	CustomKey* key = getKey(description);
	keycodeDescriptions.erase(key->getKeyNumber());
	key->setKeyNumber(keycode);
	keycodeDescriptions.emplace(keycode, description);
}

CustomKey* IController::getKey(const std::string description) const
{
	auto it = descriptionKeys.find(description);
	if (it != descriptionKeys.end())
	{
		return it->second;
	}

	return nullptr;
}

CustomKey* IController::getKey(int keycode) const
{
	auto it = keycodeDescriptions.find(keycode);
	if (it != keycodeDescriptions.end())
	{
		std::string description = it->second;
		return getKey(description);
	}
	return nullptr;
}

void IController::actionKey(const std::string description, bool pressed)
{
	CustomKey* key = getKey(description);
	if (key) key->Action(pressed);
}

void IController::actionKey(int keycode, bool pressed)
{
	CustomKey* key = getKey(keycode);
	if (key) key->Action(pressed);
}
