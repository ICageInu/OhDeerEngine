#pragma once

namespace OhDeerEngine
{
	class GameObject;
	class BaseComponent
	{
	public:
		virtual ~BaseComponent() = default;
		virtual void Update(const float deltaT) = 0;
		virtual void Render() const = 0;
		virtual void FixedUpdate(const float deltaT) = 0;
		void SetParent(GameObject* pParent) { m_pParent = pParent; }
		GameObject* GetParent()const { return m_pParent; }
	protected:
		GameObject* m_pParent = nullptr;
	};
}