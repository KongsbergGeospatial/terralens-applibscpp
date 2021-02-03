#include "TerraLens/InputControl.h"

TerraLens::InputControl::InputControl()
{
	for (int button = MB_None; button < MB_MAX; ++button)
	{
		mouseInputs[button] = std::vector<TerraLens::MouseInput*>();
	}
}

TerraLens::InputControl::~InputControl()
{
	for (int button = MB_None; button < MB_MAX; ++button)
	{
		for (int i = 0; i < mouseInputs[button].size(); ++i)
		{
			delete mouseInputs[button][i];
		}
	}
	for (int i = 0; i < keyInputs.size(); ++i)
	{
		delete keyInputs[i];
	}
	for (int i = 0; i < wheelInputs.size(); ++i)
	{
		delete wheelInputs[i];
	}
}

int TerraLens::InputControl::addMouseInput(TerraLens::MouseButton button, TerraLens::MouseInput* input)
{
	for (int i = 0; i < mouseInputs[button].size(); ++i)
	{
		if (!mouseInputs[button][i] || mouseInputs[button][i] == input)
		{
			mouseInputs[button][i] = input;
			return i;
		}
	}
	mouseInputs[button].push_back(input);
	return mouseInputs[button].size() - 1;
}

void TerraLens::InputControl::removeMouseInput(TerraLens::MouseButton button, TerraLens::MouseInput* input)
{
	for (int i = 0; i < mouseInputs[button].size(); ++i)
	{
		if (mouseInputs[button][i] == input)
		{
			mouseInputs[button][i] = 0;
			return;
		}
	}
}

void TerraLens::InputControl::selectMouseInput(TerraLens::MouseButton button, int index)
{
	if (index >= 0 && index < mouseInputs[button].size())
	{
		currentMouseInput[button] = index;
	}
	else
	{
		currentMouseInput[button] = -1;
	}
}

int TerraLens::InputControl::getMouseInputCount(TerraLens::MouseButton button)
{
	return (int)mouseInputs[button].size();
}

void TerraLens::InputControl::onMousePress(TerraLens::MouseButton button, InterMAPhics::ScreenPoint& p)
{
	if (mouseInputs[button].size() > 0 && currentMouseInput[button] >= 0 &&
		mouseInputs[button].size() > currentMouseInput[button])
	{
		MouseInput* input = mouseInputs[button][currentMouseInput[button]];
		if (input)
		{
			isMousePressed[button] = true;
			input->onPressed(p);
		}
	}
}

void TerraLens::InputControl::onMouseMove(InterMAPhics::ScreenPoint& p)
{
	for (int button = MB_None; button < MB_MAX; ++button)
	{
		if (isMousePressed[button] && currentMouseInput[button] >= 0 &&
			mouseInputs[button].size() > 0 && mouseInputs[button].size() > currentMouseInput[button])
		{
			MouseInput* input = mouseInputs[button][currentMouseInput[button]];
			if (input)
			{
				input->onMoved(p);
			}
		}
	}
}

void TerraLens::InputControl::onMouseRelease(TerraLens::MouseButton button, InterMAPhics::ScreenPoint& p)
{
	if (mouseInputs[button].size() > 0 && currentMouseInput[button] >= 0 &&
		mouseInputs[button].size() > currentMouseInput[button])
	{
		MouseInput* input = mouseInputs[button][currentMouseInput[button]];
		if (input)
		{
			isMousePressed[button] = false;
			input->onReleased(p);
		}
	}
}

int TerraLens::InputControl::addKeyInput(TerraLens::KeyInput* input)
{
	for (int i = 0; i < keyInputs.size(); ++i)
	{
		if (!keyInputs[i] || keyInputs[i] == input)
		{
			keyInputs[i] = input;
			return i;
		}
	}
	keyInputs.push_back(input);
	return (int)keyInputs.size() - 1;
}

void TerraLens::InputControl::removeKeyInput(TerraLens::KeyInput* input)
{
	for (int i = 0; i < keyInputs.size(); ++i)
	{
		if (!keyInputs[i] || keyInputs[i] == input)
		{
			keyInputs[i] = 0;
			return;
		}
	}
}

void TerraLens::InputControl::selectKeyInput(int index)
{
	if (index >= 0 && index < keyInputs.size())
	{
		currentKeyInput = index;
	}
	else
	{
		currentKeyInput = -1;
	}
}

int TerraLens::InputControl::getKeyInputCount()
{
	return (int)keyInputs.size();
}

void TerraLens::InputControl::onKeyPress(int key)
{
	if (keyInputs.size() > 0 && currentKeyInput >= 0 &&
		keyInputs.size() > currentKeyInput)
	{
		KeyInput* input = keyInputs[currentKeyInput];
		switch (key)
		{
		case TL_KEY_RIGHTSHIFT: keyMods |= (TL_KMOD_RSHIFT); break;
		case TL_KEY_LEFTSHIFT: keyMods |= (TL_KMOD_LSHIFT); break;
		case TL_KEY_RIGHTALT: keyMods |= (TL_KMOD_RALT); break;
		case TL_KEY_LEFTALT: keyMods |= (TL_KMOD_LALT); break;
		case TL_KEY_RIGHTCTRL: keyMods |= (TL_KMOD_RCTRL); break;
		case TL_KEY_LEFTCTRL: keyMods |= (TL_KMOD_LCTRL); break;
		default:break;
		}
		if (input)
		{
			input->onPressed(key, keyMods);
		}
	}
}

void TerraLens::InputControl::onKeyRelease(int key)
{
	if (keyInputs.size() > 0 && currentKeyInput >= 0 &&
		keyInputs.size() > currentKeyInput)
	{
		KeyInput* input = keyInputs[currentKeyInput];
		switch (key)
		{
		case TL_KEY_RIGHTSHIFT: keyMods &= (~TL_KMOD_RSHIFT); break;
		case TL_KEY_LEFTSHIFT: keyMods &= (~TL_KMOD_LSHIFT); break;
		case TL_KEY_RIGHTALT: keyMods &= (~TL_KMOD_RALT); break;
		case TL_KEY_LEFTALT: keyMods &= (~TL_KMOD_LALT); break;
		case TL_KEY_RIGHTCTRL: keyMods &= (~TL_KMOD_RCTRL); break;
		case TL_KEY_LEFTCTRL: keyMods &= (~TL_KMOD_LCTRL); break;
		default:break;
		}
		if (input)
		{
			input->onReleased(key, keyMods);
		}
	}
}

int TerraLens::InputControl::addWheelInput(TerraLens::WheelInput* input)
{
	for (int i = 0; i < wheelInputs.size(); ++i)
	{
		if (!wheelInputs[i] || wheelInputs[i] == input)
		{
			wheelInputs[i] = input;
			return i;
		}
	}
	wheelInputs.push_back(input);
	return (int)wheelInputs.size() - 1;
}

void TerraLens::InputControl::removeWheelInput(TerraLens::WheelInput* input)
{
	for (int i = 0; i < wheelInputs.size(); ++i)
	{
		if (!wheelInputs[i] || wheelInputs[i] == input)
		{
			wheelInputs[i] = 0;
			return;
		}
	}
}

void TerraLens::InputControl::selectWheelInput(int index)
{
	if (index >= 0 && index < wheelInputs.size())
	{
		currentWheelInput = index;
	}
	else
	{
		currentWheelInput = -1;
	}
}

int TerraLens::InputControl::getWheelInputCount()
{
	return (int)wheelInputs.size();
}

void TerraLens::InputControl::onWheel(int delta)
{
	if (wheelInputs.size() > 0 && currentWheelInput >= 0 &&
		wheelInputs.size() > currentWheelInput)
	{
		wheelInputs[currentWheelInput]->onWheel(delta);
	}
}
