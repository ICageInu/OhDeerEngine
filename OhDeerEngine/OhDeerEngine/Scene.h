#pragma once
#include "SceneManager.h"
#include "SFML/Graphics.hpp"

namespace OhDeer{

class GameObject;
class Scene
{

public:
	void AddChild(GameObject* object);
	virtual ~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

protected:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void SceneActivated() {}
	virtual void SceneDeactivated() {}

protected:

	//only giving acces to scenemanager
	friend class SceneManager;


	explicit Scene(const std::string& name);

	void BaseInitialize();
	void BaseUpdate(float deltaTime);
	void BaseRender(sf::RenderWindow* pWindow) const;

	std::string m_Name;
	std::vector <GameObject*> m_pObjects{};

	//static unsigned int m_IdCounter;
};


}