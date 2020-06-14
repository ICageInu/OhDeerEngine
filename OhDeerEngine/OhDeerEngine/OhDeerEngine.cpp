#include "OhDeerEngine.h"
#include "pch.h"
#include "SFML/System/Clock.hpp"
#include "../libraries/imgui-master/imgui.h"
#include "../libraries/imgui-sfml-2.1/imgui-SFML.h"
#include <vld.h>
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Box2D.h"

using namespace OhDeer;
OhDeerEngine::OhDeerEngine():
	m_pDebugWindow{nullptr},
	m_pWindow{nullptr}
{
}

void OhDeerEngine::StartUp()
{
	m_pWindow = new sf::RenderWindow();
	m_pWindow->create(sf::VideoMode(640, 480), "OhDeer", sf::Style::Titlebar | sf::Style::Close);
	//m_Window= sf::RenderWindow(sf::VideoMode(640, 480), "OhDeer");
	m_pDebugWindow = new sf::Window();
	m_pDebugWindow->setSize(sf::Vector2u(50, 30));
	m_pDebugWindow->setPosition(sf::Vector2i(0, 30));
	//m_pDebugWindow->create(sf::WindowHandle)

	//I mean I can use this to cheat the update speed
	//m_pWindow->setFramerateLimit(60);
	ImGui::SFML::Init(*m_pWindow);
	m_pInputManager = new InputManager();
	m_pClock = new sf::Clock();
	//ServiceLocator Inits
	ServiceLocator::InitGameHandler();
	ServiceLocator::RegisterInputManager(m_pInputManager);
	ServiceLocator::RegisterRenderWindow(m_pWindow);
	ServiceLocator::RegisterClock(m_pClock);
	Initialize();

	SceneManager::GetInstance().Initialize();
}

void OhDeerEngine::LoadGame() const
{


}

void OhDeerEngine::CleanUp()
{
	//clearing of singletons
	SceneManager::GetInstance().CleanUp();
	ResourceManager::GetInstance().CleanUp();
	SafeDelete(m_pClock);
	SafeDelete(m_pDebugWindow);
	SafeDelete(m_pWindow);
	SafeDelete(m_pInputManager);
	ServiceLocator::CleanUpGameHandler();
	ImGui::SFML::Shutdown();
}


void OhDeerEngine::Run()
{
	auto& scenemanager = SceneManager::GetInstance();

	//gameloop
	m_pClock->restart();
	while (m_pWindow->isOpen()) {
		sf::Event event;
		while (m_pWindow->pollEvent(event)) {
			//this is basically the worked in processing of inputs of smfl
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				m_pWindow->close();
			}
		}
		//we continiously restart the clock, so we base it on real time passing since last update
		ImGui::SFML::Update(*m_pWindow, m_pClock->restart());

		//here is where we should handle the inputs


		//updates
		scenemanager.Update(m_pClock->getElapsedTime().asSeconds());


		//change this to an actual renderer and not just a drawcall through scenemanager
		//render draw call
		m_pWindow->clear();
		scenemanager.Render(m_pWindow);
		//m_pWindow->draw(shape);
		ImGui::SFML::Render(*m_pWindow);
		m_pWindow->display();
	}

	CleanUp();
}