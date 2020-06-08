#pragma once
#include "pch.h"


class BaseComponent
{
public:
	BaseComponent();
	virtual ~BaseComponent() = default;

	//virtual void justaTest() = 0;
	virtual void Initialize() = 0;
	virtual void Render(sf::RenderWindow& window)const = 0;

	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) noexcept = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other)noexcept = delete;

protected:

	bool m_IsInitialized;
};

