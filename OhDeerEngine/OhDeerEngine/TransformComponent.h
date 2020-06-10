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
		

		//translate will be used to move in certain direction, so getposition and do plus direction
		void Translate(float x, float y);
		void Translate(const sf::Vector2f& dir);

		//SETTERS
		void SetPosition(float x, float y);
		void SetPosition(const sf::Vector2<float>& newPos);
		
		void SetSize(float x, float y);
		void SetSize(const sf::Vector2<float>& newSize);
	
		//GETTERS
		sf::Vector2f GetPosition()const;
	
	
	private:
		sf::Transform* m_pTransform;
	};


}