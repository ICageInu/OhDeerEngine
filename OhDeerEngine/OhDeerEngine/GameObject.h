#pragma once
#include "pch.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include "BaseComponent.h"
namespace OhDeer
{
	class TransformComponent;
	class RenderComponent;
	class GameObject final
	{
	public:
		GameObject();
		~GameObject() = default;
		void Initialize();
		void Render(sf::RenderWindow* pWindow)const;
		void Update(float deltaT);
		void CleanUp();

		//SETTERS
		void AddComponent(BaseComponent* pComp);
		void SetHasTexture(bool hasTexture);
		void SetTag(const std::string& tag);

		//GETTERS
		std::string GetTag()const;
		TransformComponent* GetTransform()const;
		template<class T>
		T* GetComponent()const;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other)noexcept = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other)noexcept = delete;

	private:
		float m_Width, m_Height;
		//RenderComponent* m_pRenderComponent;
		bool m_HasTexture;
		std::string m_Tag;
		std::vector<BaseComponent*> m_pComponents;
	};

	//thanks overlord engine
	template<class T>
	inline T* GameObject::GetComponent() const
	{
		const type_info& ti = typeid(T);
		for (auto* component : m_pComponents)
		{
			if (component && typeid(*component) == ti)
				return reinterpret_cast<T*>(component);
		}
		return nullptr;
	}

}