#pragma once
#include <glm/vec2.hpp>

namespace OhDeerEngine
{
	class BaseComponent;
	class Texture2D;
	class GameObject final
	{
	public:
		void Update(float deltaT);
		void FixedUpdate(float deltaT);
		void Render() const;

		//void SetTexture(const std::string& filename);

		GameObject(const glm::vec2& pos = {0.f,0.f}, const float angle = {0.f});
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		//handy functions
		template <class T>
		T* GetComponent()const
		{
			const type_info& ti = typeid(T);
			for (BaseComponent* pComp : m_Components)
			{
				if (pComp && typeid(*pComp) == ti)
					return static_cast<T*>(pComp);
			}
			return nullptr;
		}
		void AddComponent(BaseComponent* pComp);
		void SetTag(const std::string& tag);
	private:
		std::vector<BaseComponent*> m_Components;
		std::string m_Tag;
	};
}
