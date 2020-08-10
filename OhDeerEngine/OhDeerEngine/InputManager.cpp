#include "OhDeerPCH.h"
#include "InputManager.h"
#include <SDL.h>


PBYTE OhDeerEngine::InputManager::m_pCurrKeyboardState = nullptr;
PBYTE OhDeerEngine::InputManager::m_pOldKeyboardState = nullptr;

//these functions will always happen regardless on if gamepad is connected or not

OhDeerEngine::InputManager::~InputManager()
{
	delete m_pCurrKeyboardState;
	delete m_pOldKeyboardState;
	m_pCurrKeyboardState = nullptr;
	m_pOldKeyboardState = nullptr;
}

void OhDeerEngine::InputManager::Initialize()
{
	m_GamepadIsConnected = Connected();
}

bool OhDeerEngine::InputManager::ProcessInput()
{
	if (m_GamepadIsConnected)
	{
		m_CurrentState = GetState();

	}
	//ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	//XInputGetState(m_GamepadIndex, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;

		}
		if (e.type == SDL_KEYDOWN) {
			std::cout << "button pressed" << std::endl;
			//e.
			break;
		}
		if (e.type == SDL_KEYUP) {
			std::cout << "button up" << std::endl;
			break;
		}
		if (e.type == SDL_MOUSEBUTTONDOWN) {
			break;
		}
	}

	return true;
}

bool OhDeerEngine::InputManager::IsPressed(ControllerButton button) const
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

bool OhDeerEngine::InputManager::IsPressed([[maybe_unused]] int button) const
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_KEYUP) {
			
			return true;
		}
	}
	return false;
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

	return false;
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

	return false;
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

glm::vec2 OhDeerEngine::InputManager::LeftStick()const
{
	//in OG tutorial he divides these shorts with 32767, tried finding out why and found this short thread
	//https://e2e.ti.com/support/tools/ccs/f/81/t/586525?CCS-TMS320VC5402-cast-from-float-to-short
	//but that is from float to short, so just keep it in mind if getting weird errors
	short sX = m_CurrentState.Gamepad.sThumbLX;
	short sY = m_CurrentState.Gamepad.sThumbLY;
	return glm::vec2(static_cast<float>(sX) / 32767.0f, static_cast<float>(sY) / 32767.0f);
}

glm::vec2 OhDeerEngine::InputManager::RightStick()const
{
	short sX = m_CurrentState.Gamepad.sThumbRX;
	short sY = m_CurrentState.Gamepad.sThumbRY;
	return glm::vec2(static_cast<float>(sX) / 32767.0f, static_cast<float>(sY) / 32767.0f);
}
