#include "OhDeerPCH.h"
#include "OhDeer.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "TextComponent.h"

using namespace std;
using namespace std::chrono;
//16 for 60 fps, 33 for 30 fps
const float OhDeerEngine::OhDeerEngine::SPerFrame = 0.016f;

void OhDeerEngine::OhDeerEngine::Initialize()
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
}

/**
 * Code constructing the scene world starts here
 */
void OhDeerEngine::OhDeerEngine::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = new GameObject();
	//go->SetTexture("background.jpg");
	auto tex1 = new RenderComponent();
	tex1->AddTexture(ResourceManager::GetInstance().LoadTexture("background.jpg"));
	go->AddComponent(tex1);
	go->SetTag("background");
	scene.Add(go);

	go = new GameObject({ 216, 180 }, 0);
	////go->SetTexture("logo.png");
	auto tex2 = new RenderComponent();
	tex2->AddTexture(ResourceManager::GetInstance().LoadTexture("logo.png"));
	go->AddComponent(tex2);
	scene.Add(go);

	go = new GameObject({ 20,20 });
	auto tex3 = new RenderComponent();
	tex3->AddTexture(ResourceManager::GetInstance().LoadTexture("logo.png"));
	auto font = new TextComponent("Programming 4 Assignment");
	font->AddFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));

	go->AddComponent(font);
	go->AddComponent(tex3);
	scene.Add(go);
}

void OhDeerEngine::OhDeerEngine::Cleanup()
{

	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void OhDeerEngine::OhDeerEngine::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Resources/");

	LoadGame();

	{
		//initting singletons
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

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
