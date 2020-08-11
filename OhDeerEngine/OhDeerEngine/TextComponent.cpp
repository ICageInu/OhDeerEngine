#include "OhDeerPCH.h"
#include "TextComponent.h"
#include "Font.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "GameObject.h"
#include "TransformComponent.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "ResourceManager.h"

OhDeerEngine::TextComponent::~TextComponent()
{
	//SafeDelete(m_pTexture);
}

OhDeerEngine::TextComponent::TextComponent(const std::string& text):
	m_Text{text},
	m_pFont{nullptr},
	m_pTexture{},
	m_NeedsUpdate{false}
{
}

OhDeerEngine::TextComponent::TextComponent(const std::string& text, Font* pFont) :
	m_Text{ text },
	m_pFont{ pFont },
	m_pTexture{ nullptr },
	m_NeedsUpdate{ true }
{
}

void OhDeerEngine::TextComponent::Update(const float)
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTexture = ResourceManager::GetInstance().ChangeTexture(*texture,m_Text);
		m_NeedsUpdate = false;
	}
}

void OhDeerEngine::TextComponent::Render() const
{
	if (m_pTexture != nullptr) 
	{
		const auto pos = m_pParent->GetComponent<TransformComponent>()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}
}

void OhDeerEngine::TextComponent::FixedUpdate(const float){}

void OhDeerEngine::TextComponent::AddFont(Font* pFont)
{
	m_pFont = pFont;
	m_NeedsUpdate = true;
}

void OhDeerEngine::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

