#pragma once
#include "SceneManager.h"
#include <vector>
#include <string>

namespace OhDeerEngine
{
	class GameObject;
	class Scene
	{
		friend Scene& SceneManager::CreateScene(const std::string& name);
	public:
		void Add(GameObject* pObject);

		void Update(float deltaT);
		void FixedUpdate(float deltaT);
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 
		explicit Scene(const std::string& name);

		std::string m_Name;
		std::vector <GameObject*> m_Objects{};
	};

}
