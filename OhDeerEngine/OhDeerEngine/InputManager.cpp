#include "InputManager.h"
#include "InputManager.h"
#include "InputManager.h"

//https://stackoverflow.com/questions/11699183/what-is-the-best-way-to-read-input-from-keyboard-using-sdl


//these functions will always happen regardless on if gamepad is connected or not

OhDeerEngine::InputManager::~InputManager()
{

}

void OhDeerEngine::InputManager::Initialize()
{
	m_GamepadIsConnected = Connected();

	int size;
	SDL_GetKeyboardState(&size);

	for (int i = 0; i < size; i++)
	{
		m_KeyboardCurrent[i] = false;
		m_KeyboardOld[i] = false;
		m_KeyboardTemp[i] = false;
	}
}

bool OhDeerEngine::InputManager::ProcessInput()
{
	if (m_GamepadIsConnected)
	{
		m_CurrentState = GetState();
	}
	//ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	//XInputGetState(m_GamepadIndex, &m_CurrentState);

	//updating keyboard states
	m_KeyboardOld = m_KeyboardCurrent;
	m_KeyboardCurrent = m_KeyboardTemp;

	SDL_Event e;
	SDL_StartTextInput();
	//this is for closing 
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT || m_CloseGame)
		{
			return false;
		}
		if (e.type == SDL_KEYUP)
		{
			m_KeyboardTemp[e.key.keysym.sym] = false;
			break;
		}
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_BACKSPACE && m_InputString.size() > 0)
				m_InputString = m_InputString.substr(0, m_InputString.size() - 1);
			m_KeyboardTemp[e.key.keysym.sym] = true;
			break;
		}
		if (e.type == SDL_TEXTINPUT) 
		{
			m_InputString += e.text.text;
		}
	}
	SDL_StopTextInput();
	return true;
}

bool OhDeerEngine::InputManager::AnyButtonPressed() const
{
	if (m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A ||
		m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B ||
		m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X ||
		m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y)
		return true;
	return false;

}

bool OhDeerEngine::InputManager::IsPressed(const ControllerButton& button) const
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	default: return false;
	}
}

bool OhDeerEngine::InputManager::IsPressed([[maybe_unused]] const SDL_Keycode& button) const
{
	return !m_KeyboardOld.at(button) && m_KeyboardCurrent.at(button);
}
bool  OhDeerEngine::InputManager::IsReleased([[maybe_unused]] const SDL_Keycode& button) const
{
	return m_KeyboardOld.at(button) && !m_KeyboardCurrent.at(button);
}
bool  OhDeerEngine::InputManager::IsDown([[maybe_unused]] const SDL_Keycode& button) const
{
	return m_KeyboardOld.at(button) && m_KeyboardCurrent.at(button);
}

void OhDeerEngine::InputManager::SetCloseWindow(bool doClose)
{
	m_CloseGame = doClose;
}

std::string OhDeerEngine::InputManager::GetInputString() const
{
	return m_InputString;
}
void OhDeerEngine::InputManager::CleanInputString()
{
	m_InputString = "";
}


//==============GAMEPAD FUNCTIONS


//basically like processinginput but for gamepad I presume
XINPUT_STATE OhDeerEngine::InputManager::GetState()const
{
	XINPUT_STATE gamepadState;
	ZeroMemory(&gamepadState, sizeof(XINPUT_STATE));
	XInputGetState(m_GamepadIndex, &gamepadState);
	return gamepadState;
}
//gamepadIndex
int OhDeerEngine::InputManager::GetIndex()const
{
	return m_GamepadIndex;
}

bool OhDeerEngine::InputManager::Connected()
{

	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));

	DWORD result = XInputGetState(m_GamepadIndex, &m_CurrentState);

	if (result == ERROR_SUCCESS) {
		std::cout << "gamepadConnected" << std::endl;
		return true; //connected
	}
	else
		return false; //no gamepad connected
}

bool OhDeerEngine::InputManager::LStick_InDeadZone()const
{
	//getting axis
	short sX = m_CurrentState.Gamepad.sThumbLX;
	short sY = m_CurrentState.Gamepad.sThumbLY;
	if (sX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || sX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;
	if (sY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE || sY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		return false;

	return true;
}

bool OhDeerEngine::InputManager::RStick_InDeadZone()const
{
	//getting axis
	short sX = m_CurrentState.Gamepad.sThumbRX;
	short sY = m_CurrentState.Gamepad.sThumbRY;
	if (sX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE || sX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return false;
	if (sY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE || sY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
		return false;

	return true;
}

float OhDeerEngine::InputManager::LeftTrigger() const
{
	BYTE trigger = m_CurrentState.Gamepad.bLeftTrigger;

	if (trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		//this way we can get the power of the trigger
		return trigger / 255.0f;

	return 0.0f;
}

float OhDeerEngine::InputManager::RightTrigger() const
{
	BYTE trigger = m_CurrentState.Gamepad.bRightTrigger;

	if (trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		return trigger / 255.0f;

	return 0.0f;
}

glm::vec2 OhDeerEngine::InputManager::GetLeftStick(bool squareDir)const
{
	//in OG tutorial he divides these shorts with 32767, tried finding out why and found this short thread
	//https://e2e.ti.com/support/tools/ccs/f/81/t/586525?CCS-TMS320VC5402-cast-from-float-to-short
	//but that is from float to short, so just keep it in mind if getting weird errors
	float sX = (static_cast<float>(m_CurrentState.Gamepad.sThumbLX) / 32767.0f);
	float sY = -(static_cast<float>(m_CurrentState.Gamepad.sThumbLY) / 32767.0f);
	//if not square dirs, return the axis direction
	if (!squareDir)
		return glm::vec2(sX, sY);

	//if in deadzone just return 0
	if (LStick_InDeadZone()) return glm::vec2(0, 0);

	if (std::fabsf(sX) > std::fabsf(sY))
	{
		if (std::signbit(sX))
			return glm::vec2(-1, 0);
		else return glm::vec2(1, 0);
	}
	if (std::signbit(sY))
		return glm::vec2(0, -1);
	else return glm::vec2(0, 1);
}

glm::vec2 OhDeerEngine::InputManager::GetRightStick(bool squareDir)const
{
	float sX = (static_cast<float>(m_CurrentState.Gamepad.sThumbRX) / 32767.0f);
	float sY = -(static_cast<float>(m_CurrentState.Gamepad.sThumbRY) / 32767.0f);
	if (!squareDir)
		return glm::vec2(sX, sY);


	if (RStick_InDeadZone()) return glm::vec2(0, 0);

	if (std::fabsf(sX) > std::fabsf(sY))
	{
		if (std::signbit(sX))
			return glm::vec2(-1, 0);
		else return glm::vec2(1, 0);
	}
	if (std::signbit(sY))
		return glm::vec2(0, 1);
	else return glm::vec2(0, -1);
}
