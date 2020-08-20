#pragma once
#include <glm/vec2.hpp>
#include <functional>

namespace OhDeerEngine
{
	class TransformComponent;
	class BaseComponent;
	class Texture2D;
	class GameObject final
	{
	public:
		enum class TriggerAction
		{
			ENTER,
			LEAVE
		};

		typedef std::function<void(GameObject* triggerObject, GameObject* otherObject, TriggerAction action)> TriggerCallback;

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

		std::vector<GameObject*>GetChildren()const;

		//handy functions
		//TODO do auto&
		template <class T>
		T* GetComponent()const
		{
			const type_info& ti = typeid(T);
			for (auto& pComp : m_Components)
			{
				if (pComp && typeid(*pComp) == ti)
					return static_cast<T*>(pComp);
			}
			return nullptr;
		}
		void AddComponent(BaseComponent* pComp);
		void SetTag(const std::string& tag);
		TransformComponent* GetTransform()const;
		//void CheckForCollision(GameObject* pOther);
		void SetOnTriggerCallBack(TriggerCallback);
		void OnTrigger(GameObject* triggerObject, GameObject* otherObject, TriggerAction action);
		std::string GetTag()const;
		void SetEnabledDisabled(bool isEnabled);
		//bool GetIsActive()const;
		bool IsActive;
	private:
		std::vector<BaseComponent*> m_Components;
		TriggerCallback m_OnTriggerCallback;
		std::string m_Tag;
	};
}
