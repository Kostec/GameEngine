#pragma once

#include <functional>
#include <string>
#include <map>

typedef std::function<void(bool press)> KeyCallbackFunction;

class CustomKey {
public:
    CustomKey() = delete;
    CustomKey(const int keyNumber, const KeyCallbackFunction callbackFunction);
    void setKeyNumber(int keyNumber) { m_keyNumber = keyNumber; }
    int getKeyNumber() const { return m_keyNumber; }
    void setKeyCallback(KeyCallbackFunction callbackFunction) { m_callbackFunction = callbackFunction; };
    void Action(bool pressed) {
        if (pressed == m_keyPressed) return;
        m_keyPressed = pressed;
        m_callbackFunction(pressed);
    }
    bool keyPressed() { return m_keyPressed; }
private:
    int m_keyNumber;
    bool m_keyPressed;
    KeyCallbackFunction m_callbackFunction;
};