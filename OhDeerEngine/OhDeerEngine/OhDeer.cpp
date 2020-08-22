#include "OhDeerPCH.h"
#include "OhDeer.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "SDL.h"
#include "GameObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "TextComponent.h"


using namespace std;
using namespace std::chrono;
//16 for 60 fps, 33 for 30 fps
const float OhDeerEngine::OhDeer::SPerFrame = 0.016f;

void OhDeerEngine::OhDeer::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
	
	ServiceLocator::InitGameHandler();
	ServiceLocator::RegisterWindow(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void OhDeerEngine::OhDeer::LoadGame() const
{}

void OhDeerEngine::OhDeer::Cleanup()
{
	Renderer::GetInstance().Release();
	ServiceLocator::CleanUpGameHandler();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void OhDeerEngine::OhDeer::Run()
{
	Initialize();



	LoadGame();

	{
		//initting singletons
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		input.Initialize();


		//we want a normal update and a fixed update
		auto lastTime = std::chrono::high_resolution_clock::now();
		//this is for fixedupdate
		float lag = 0.0f;

		bool doContinue = true;
		while (doContinue)
		{
			//first update variables then update game
			const auto currentTime = high_resolution_clock::now();
			float deltaT = std::chrono::duration<float>(currentTime - lastTime).count();
			//this is specific to fixedupdate, in normal update this happens at the end of the while loop
			lastTime = currentTime;
			lag += deltaT;

			doContinue = input.ProcessInput();

			sceneManager.Update(deltaT);

			while (lag >= SPerFrame)
			{
				sceneManager.FixedUpdate(SPerFrame);
				lag -= SPerFrame;
			}
			//rendering after updates

			renderer.Render();

		}
	}
	Cleanup();
}
