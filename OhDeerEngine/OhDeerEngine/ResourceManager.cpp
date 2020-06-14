#include "ResourceManager.h"
using namespace OhDeer;

void OhDeer::ResourceManager::Initialize()
{
}

void OhDeer::ResourceManager::Update([[maybe_unused]] float deltaTime)
{
}

void OhDeer::ResourceManager::CleanUp()
{
    for (auto texture : m_Textures) {
        SafeDelete(texture);
    }
    m_Textures.clear();
}

sf::Texture* OhDeer::ResourceManager::LoadTexture(const std::string& assetFile)
{
    sf::Texture* pTexture = new sf::Texture();
    

	if (!pTexture->loadFromFile(assetFile))
	{
		std::string errorLog{ "file not found" };
		ImGui::LogText(&(errorLog[0]));
	}
	else
	{
		std::string errorLog{ "texture has been found" };
		ImGui::LogText(&(errorLog[0]));
	}
	m_Textures.push_back(pTexture);

    return pTexture;
}
