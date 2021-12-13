#include "CustomKey.h"

CustomKey::CustomKey(const int keyNumber, const KeyCallbackFunction callbackFunction)
	:m_keyNumber(keyNumber), m_callbackFunction(callbackFunction)
{
}