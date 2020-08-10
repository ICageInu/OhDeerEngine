#pragma once
#include "SceneManager.h"
#include <vector>
#include <string>

namespace OhDeerEngine
{
	class GameObject;
	class Scene
	{
		
	public:
		explicit Scene(const std::string& name);
		void Add(GameObject* pObject);

		void BaseUpdate(float deltaT);
		void FixedUpdate(float deltaT);
		void Render() const;

		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	protected:
		friend class SceneManager;

		virtual void Initialize() =0;
		virtual void Update([[maybe_unused]]float deltaT) =0;

	private: 

		std::string m_Name;
		std::vector <GameObject*> m_Objects{};
	};

}
