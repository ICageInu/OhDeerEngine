#pragma once
#include <BaseComponent.h>
#include <string>
#include "TextComponent.h"
class InputComponent :
    public OhDeerEngine::BaseComponent
{
public:
	InputComponent(OhDeerEngine::TextComponent* pText);
	virtual void Update(const float deltaT) override;
	virtual void Render() const override {};
	virtual void FixedUpdate(const float deltaT) override {};
	std::string GetInitials()const;
private:
	OhDeerEngine::TextComponent* m_pText;
	std::string m_Initials;
	bool m_SetControllerInput{ false };
};

