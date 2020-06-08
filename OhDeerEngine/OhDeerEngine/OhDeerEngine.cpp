#include "OhDeerEngine.h"
#include "pch.h"
#include "SFML/System/Clock.hpp"
#include "../libraries/imgui-master/imgui.h"
#include "../libraries/imgui-sfml-2.1/imgui-SFML.h"
#include "SceneManager.h"
#include <vld.h>

OhDeerEngine::OhDeerEngine()
{
}

OhDeerEngine::~OhDeerEngine()
{
}

void OhDeerEngine::StartUp()
{
	m_Window.create(sf::VideoMode(640, 480), "OhDeer", sf::Style::Titlebar | sf::Style::Close);
	//m_Window= sf::RenderWindow(sf::VideoMode(640, 480), "OhDeer");
	m_pDebugWindow = new sf::Window();
	m_pDebugWindow->setSize(sf::Vector2u(50, 30));
	m_pDebugWindow->setPosition(sf::Vector2i(0, 30));
	//m_pDebugWindow->create(sf::WindowHandle)

	m_Window.setFramerateLimit(60);
	ImGui::SFML::Init(m_Window);

	//ServiceLocator Inits
	//ServiceLocator::RegisterRenderWindow(m_Window);

	Initialize();

	SceneManager::GetInstance().Initialize();
}

void OhDeerEngine::LoadGame() const
{


}

void OhDeerEngine::CleanUp()
{
	SceneManager::GetInstance().CleanUp();
	SafeDelete(m_pDebugWindow);
	//SafeDelete(m_pWindow);
	ImGui::SFML::Shutdown();
}


void OhDeerEngine::Run()
{
	//std::string test{"Log window works"};
	//ImGui::LogText(test.data());


	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);

	auto& scenemanager = SceneManager::GetInstance();

	sf::Clock deltaClock;
	while (m_Window.isOpen()) {
		sf::Event event;
		while (m_Window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				m_Window.close();
			}
		}

		ImGui::SFML::Update(m_Window, deltaClock.restart());


		//updates
		scenemanager.Update(deltaClock.getElapsedTime().asSeconds());


		//render draw call
		m_Window.clear();
		scenemanager.Render(m_Window);
		//m_pWindow->draw(shape);
		ImGui::SFML::Render(m_Window);
		m_Window.display();
	}

	CleanUp();
}