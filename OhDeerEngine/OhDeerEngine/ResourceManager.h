#pragma once
#include "pch.h"
#include "Singleton.h"
namespace OhDeer {

	class ResourceManager : public Singleton<ResourceManager>
	{
	public:
		void Initialize();
		void Update(float deltaTime);
		void CleanUp();
		sf::Texture* LoadTexture(const std::string& assetFile);
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;
		std::vector<sf::Texture*>  m_Textures;
		//std::vector<sf::Font*>
	};


}