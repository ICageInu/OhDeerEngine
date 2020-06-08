#include "TextureComponent.h"

TextureComponent::TextureComponent()
	:BaseComponent()
	, m_pSprite(nullptr)
{}

TextureComponent::TextureComponent(const std::string& assetFile) :
	BaseComponent()
{
	m_IsInitialized = true;

	//if (!m_IsInitialized)
	//{
	//	Initialize();
	//}
	m_pTexture = new sf::Texture();
	if (!m_pTexture->loadFromFile(assetFile))
	{
		std::string errorLog{ "file not found" };
		ImGui::LogText(&(errorLog[0]));
	}
	else
	{
		std::string errorLog{ "texture has been found" };
		ImGui::LogText(&(errorLog[0]));
	}
	m_pSprite = new sf::Sprite(*m_pTexture);
}


TextureComponent::~TextureComponent()
{
	SafeDelete(m_pTexture);
	delete m_pSprite;
	m_pSprite = nullptr;
}

void TextureComponent::Initialize()
{
	//if (!m_IsInitialized) {
	//}

}

void TextureComponent::Render(sf::RenderWindow& window) const
{
	window.draw(*m_pSprite);
	//ServiceLocator::GetWindow()->draw(*m_pTexture);
}

void TextureComponent::SetTexture(const std::string& assetFile)
{
	m_IsInitialized = true;

	//if (!m_IsInitialized)
	//{
	//	Initialize();
	//}
	sf::Texture tempTex;
	if (!tempTex.loadFromFile(assetFile))
	{
		std::string errorLog{ "file not found" };
		ImGui::LogText(&(errorLog[0]));
	}
	else
	{
		std::string errorLog{ "texture has been found" };
		ImGui::LogText(&(errorLog[0]));
	}
	m_pSprite = new sf::Sprite(tempTex);
	//m_pSprite->setTexture(tempTex);
}

sf::Vector2<float> TextureComponent::GetTexturePos() const
{
	return m_pSprite->getPosition();
}

sf::Sprite* TextureComponent::GetTexture() const
{
	return m_pSprite;
}