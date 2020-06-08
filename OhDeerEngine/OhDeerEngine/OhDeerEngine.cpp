#include "OhDeerEngine.h"
#include "pch.h"
#include "SFML/System/Clock.hpp"
#include "../libraries/imgui-master/imgui.h"
#include "../libraries/imgui-sfml-2.1/imgui-SFML.h"
#include "SceneManager.h"

void OhDeerEngine::Initialize()
{
	m_pWindow = new sf::RenderWindow(sf::VideoMode(640, 480), "OhDeer");
	m_pDebugWindow = new sf::Window();
	m_pDebugWindow->setSize(sf::Vector2u(50, 30));
	m_pDebugWindow->setPosition(sf::Vector2i(0, 30));
	//m_pDebugWindow->create(sf::WindowHandle)

	m_pWindow->setFramerateLimit(60);
	ImGui::SFML::Init(*m_pWindow);

	//ServiceLocator Inits
	ServiceLocator::RegisterRenderWindow(m_pWindow);
}


void OhDeerEngine::LoadGame() const
{



}

void OhDeerEngine::CleanUp()
{
	SceneManager::GetInstance().CleanUp();
	SafeDelete(m_pDebugWindow);
	SafeDelete(m_pWindow);
	ImGui::SFML::Shutdown();
}


void OhDeerEngine::Run()
{
	//std::string test{"Log window works"};
	//ImGui::LogText(test.data());

	auto test = new sf::CircleShape();
	test->setFillColor(sf::Color::Green);
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	auto& scenemanager = SceneManager::GetInstance();

	sf::Clock deltaClock;
	while (m_pWindow->isOpen()) {
		sf::Event event;
		while (m_pWindow->pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);

			if (event.type == sf::Event::Closed) {
				m_pWindow->close();
			}
		}

		ImGui::SFML::Update(*m_pWindow, deltaClock.restart());


		//updates
		scenemanager.Update(deltaClock.getElapsedTime().asSeconds());


		//render draw call
		m_pWindow->clear();
		scenemanager.Render(m_pWindow);
		m_pWindow->draw(shape);
		ImGui::SFML::Render(*m_pWindow);
		m_pWindow->display();
	}

	CleanUp();
}