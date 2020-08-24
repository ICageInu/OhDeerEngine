#pragma once
#include "SceneManager.h"
#include <vector>
#include <string>


namespace OhDeerEngine
{
	class Observer;
	class CollisionComponent;
	class GameObject;
	class Subject;
	class Scene final
	{

	public:
		explicit Scene(const std::string& name);
		void Add(GameObject* pObject);

		void BaseUpdate(float deltaT);
		void FixedUpdate(float deltaT);
		void Render() const;

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;


		Subject* Subject = nullptr;
		std::vector <GameObject*> GetObjects()const;
		std::vector <CollisionComponent*> GetStaticCollisions()const;
		std::vector <CollisionComponent*> GetKinematicCollisions()const;
		std::string GetSceneName()const;

	private:
		friend class SceneManager;
		//bool m_IsActive;
		std::string m_Name;
		std::vector <GameObject*> m_Objects{};
		std::vector<CollisionComponent*> m_KinematicCollisions{};
		std::vector<CollisionComponent*> m_StaticCollisions{};
	};

}
