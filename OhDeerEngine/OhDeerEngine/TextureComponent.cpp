#include "TextureComponent.h"

TextureComponent::TextureComponent()
	:BaseComponent()
	, m_pTexture(nullptr)
{}

TextureComponent::TextureComponent(const std::string & assetFile):
	BaseComponent()
{
	if (!m_IsInitialized) {
		Initialize();
	}
	sf::Texture tempTex;
	if (!tempTex.loadFromFile(assetFile)) {
		std::string errorLog{ "file not found" };
		ImGui::LogText(&(errorLog[0]));
	}
	else {
		std::string errorLog{ "texture has been found" };
		ImGui::LogText(&(errorLog[0]));
	}

	m_pTexture->setTexture(tempTex);
}


TextureComponent::~TextureComponent()
{
	//SafeDelete(m_pTexture);
	delete m_pTexture;
	m_pTexture = nullptr;
}

void TextureComponent::Initialize()
{
	//if (!m_IsInitialized) {
	//}
	m_IsInitialized = true;
	m_pTexture = new sf::Sprite();
}

void TextureComponent::Render(sf::RenderWindow*) const
{
	ServiceLocator::GetWindow()->draw(*m_pTexture);
}

void TextureComponent::SetTexture(const std::string& assetFile)
{
	if (!m_IsInitialized) {
		Initialize();
	}
	sf::Texture tempTex;
	if (!tempTex.loadFromFile(assetFile)) {
		std::string errorLog{ "file not found" };
		ImGui::LogText(&(errorLog[0]));
	}
	else {
		std::string errorLog{ "texture has been found" };
		ImGui::LogText(&(errorLog[0]));
	}

	m_pTexture->setTexture(tempTex);
}

sf::Vector2<float> TextureComponent::GetTexturePos() const
{
	return m_pTexture->getPosition();
}

sf::Sprite* TextureComponent::GetTexture() const
{
	return m_pTexture;
}