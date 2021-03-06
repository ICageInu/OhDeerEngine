#pragma once


#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "SDL.h"
#include "glm/vec2.hpp"

#pragma region Templates

template<class T>
inline void SafeDelete(T* pObjectToDelete)
{
	if (pObjectToDelete != nullptr)
	{
		delete(pObjectToDelete);
		pObjectToDelete = nullptr;
	}
}

#pragma endregion Templates


#pragma region ServiceLocator

namespace OhDeerEngine
{

	struct GameHandlers
	{
		GameHandlers() :
			window{ nullptr } {}

		SDL_Window* window;
		glm::vec2 windowDimensions;
	};


	class ServiceLocator
	{
	public:
		inline static void InitGameHandler() { gameHandlers = new GameHandlers(); };
		inline static void CleanUpGameHandler() { delete gameHandlers; gameHandlers = nullptr; };
		inline static GameHandlers* GetGameHandlers() { return gameHandlers; }
		inline static void RegisterWindow(SDL_Window* pWindow)
		{
			gameHandlers->window = pWindow;
			int screenWidth, screenHeight;
			SDL_GetWindowSize(gameHandlers->window, &screenWidth, &screenHeight);
			gameHandlers->windowDimensions = { screenWidth,screenHeight };
		}
	private:
		inline static GameHandlers* gameHandlers = nullptr;
	};

}

#pragma endregion ServiceLocator