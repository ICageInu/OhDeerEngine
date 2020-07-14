#pragma once
#include "Singleton.h"
#include <map>
#include <vector>
#include <string>

namespace OhDeerEngine
{
	//class SDL_Texture;
	class Texture2D;
	class Font;
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		void Init(const std::string& data);
		~ResourceManager() override;
		//textures
		Texture2D* LoadTexture(const std::string& file);
		Texture2D* LoadTexture(const std::string& file, const std::string& data);
		Texture2D* ChangeTexture(Texture2D* pTexture,const std::string& text);

		//fonts
		Font* LoadFont(const std::string& file, unsigned int size);
		Font* LoadFont(const std::string& file, unsigned int size, const std::string& data);
	private:
		friend class Singleton<ResourceManager>;
		ResourceManager() = default;

		std::vector<std::pair< Texture2D*, std::string>> m_Textures;
		std::vector<Font*> m_Fonts;
		std::string m_DataPath;
	};
}
