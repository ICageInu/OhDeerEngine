#pragma once
#include "Singleton.h"

namespace OhDeerEngine
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		~SceneManager() override;

		void Update(float deltaT);
		void FixedUpdate(float deltaT);
		void Render();
	private:
		//this is for us to be unable to call on the constructor
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<Scene*> m_Scenes;
	};
}
