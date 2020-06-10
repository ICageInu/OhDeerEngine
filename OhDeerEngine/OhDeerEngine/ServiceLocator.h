#pragma once
#include "pch.h"
#include "SFML/Graphics.hpp"

namespace OhDeer {
	class InputManager;

	struct GameHandlers {
		GameHandlers() :
			window{ nullptr },
			inputManager{ nullptr }
		{}
		//GameHandlers(sf::RenderWindow* pWindow,InputManager* pInput):
		//	window{ pWindow },
		//	inputManager{ pInput }
		//{}


		sf::RenderWindow* window = nullptr;
		InputManager* inputManager = nullptr;

	};

	class ServiceLocator
	{
	public:
		inline static GameHandlers* GetGameHandlers() { return gameHandlers; }
		inline static void InitGameHandler() { gameHandlers = new GameHandlers(); };
		inline static void CleanUpGameHandler() { delete gameHandlers; gameHandlers = nullptr; };
		inline static void RegisterRenderWindow(sf::RenderWindow* pWindow) { gameHandlers->window = pWindow; }
		inline static void RegisterInputManager(InputManager* pInput) { gameHandlers->inputManager = pInput; }

	private:
		inline static GameHandlers* gameHandlers = nullptr;
	};
}