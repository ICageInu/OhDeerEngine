#pragma once
//https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Transform.php
#include "BaseComponent.h"
namespace OhDeer
{
	class TransformComponent :
		public BaseComponent
	{
	public:
		TransformComponent();
		virtual ~TransformComponent() override;
		virtual void Initialize() override;
		virtual void Update(float deltaT) override;


		//translate will be used to move in certain direction, so getposition and do plus direction
		void Translate(float x, float y);
		void Translate(const sf::Vector2f& dir);

		//SETTERS
		//TODO might wanna look into this, cause as far as I know right now this be useless
		//void SetPosition(float x, float y);
		//void SetPosition(const sf::Vector2<float>& newPos);

		void SetScale(float x, float y);
		void SetScale(const sf::Vector2<float>& newSize);



		//GETTERS
		const sf::Vector2f GetDimensions()const;
		const sf::Vector2f GetPosition()const;
		const sf::Vector2f& GetScale()const;
		const sf::Transform& GetTransform()const;

	private:
		sf::Transform* m_pTransform;
		sf::Vector2f m_TransformPoint;
		sf::Vector2f m_Scale,m_OldScale;
		float m_Width, m_Height;
		bool m_TransformIsChanged;
	};


}