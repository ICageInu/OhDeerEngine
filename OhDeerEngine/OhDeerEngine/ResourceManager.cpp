#include "OhDeerPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"
#include <string>


void OhDeerEngine::ResourceManager::Init(const std::string& dataPath)
{
	m_DataPath = dataPath;

	// load support for png and jpg, this takes a while!

	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		throw std::runtime_error(std::string("Failed to load support for png's: ") + SDL_GetError());
	}

	if ((IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG) != IMG_INIT_JPG)
	{
		throw std::runtime_error(std::string("Failed to load support for jpg's: ") + SDL_GetError());
	}

	if (TTF_Init() != 0)
	{
		throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
	}
}

OhDeerEngine::ResourceManager::~ResourceManager()
{
	for (std::pair<Texture2D*, std::string> pTexture : m_Textures)
	{
		SafeDelete(pTexture.first);
	}
	m_Textures.clear();
	for (Font* pFont : m_Fonts)
	{
		SafeDelete(pFont);
	}
	m_Fonts.clear();
}

OhDeerEngine::Texture2D* OhDeerEngine::ResourceManager::LoadTexture(const std::string& file)
{
	std::string fullPath = m_DataPath + file;

	const auto it = std::find_if(m_Textures.cbegin(), m_Textures.cend(), [fullPath](const std::pair < Texture2D*, std::string> &pair)
		{
			return fullPath == pair.second;
		});


	if (it != m_Textures.cend())
	{
		int index = int(it - m_Textures.cbegin());
		return m_Textures[index].first;
	}

	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());



	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}

	m_Textures.push_back(std::pair<Texture2D*, std::string>{ new Texture2D(texture), fullPath });
	return m_Textures.back().first;
}

OhDeerEngine::Texture2D* OhDeerEngine::ResourceManager::ChangeTexture(Texture2D* pTexture, const std::string& text)
{
	//make this look over te textures, if exist return that texture, otherwise make new texture
	//if index is < 0 that means you don't know if the texture exists or that the texture needs to be made
	//if (index < 0)
	//{
		//failsafe to make sure texture isn't in here already
		//is this plausible?? TODO
		//const auto it = std::find_if(m_Textures.cbegin(), m_Textures.cend(), [pTexture](Texture2D* pTex)
		//	{
		//		return *pTexture == *pTex;
		//	});
		//if (it != m_Textures.cend())
		//{
		//	int index = it - m_Textures.cbegin();
		//	return m_Textures[index].first;
		//}
		//if (index != m_Textures.size())
		//{
		//}
	//		m_Textures.push_back(pTexture);
	//		index = int(m_Textures.size());
	//		return m_Textures.back();
	//}
	//else
	//{
		//delete m_Textures[index].first;
		//m_Textures[index].first = pTexture;
		//return m_Textures[index].first;
	//}
	//return nullptr;


	const auto it = std::find_if(m_Textures.cbegin(), m_Textures.cend(), [text](const std::pair < Texture2D*, std::string>& pair)
		{
			return text == pair.second;
		});

	if (it != m_Textures.cend())
	{
		int index = int(it - m_Textures.cbegin());
		return m_Textures[index].first;
	}
	else
	{
		m_Textures.push_back(std::pair<Texture2D*, std::string>{ pTexture, text });
		return m_Textures.back().first;
	}
}

OhDeerEngine::Texture2D* OhDeerEngine::ResourceManager::LoadTexture(const std::string& file, const std::string& data)
{
	const auto fullPath = data + file;


	const auto it = std::find_if(m_Textures.cbegin(), m_Textures.cend(), [fullPath](const std::pair < Texture2D*, std::string>& pair)
		{
			return fullPath == pair.second;
		});

	if (it != m_Textures.cend())
	{
		int index = int(it - m_Textures.cbegin());
		return m_Textures[index].first;
	}

	auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	if (texture == nullptr)
	{
		throw std::runtime_error(std::string("Failed to load texture: ") + SDL_GetError());
	}

	m_Textures.push_back(std::pair<Texture2D*, std::string>{ new Texture2D(texture), fullPath });
	return m_Textures.back().first;

}

OhDeerEngine::Font* OhDeerEngine::ResourceManager::LoadFont(const std::string& file, unsigned int size)
{
	m_Fonts.push_back(new Font(m_DataPath + file, size));
	return m_Fonts.back();
}

OhDeerEngine::Font* OhDeerEngine::ResourceManager::LoadFont(const std::string& file, unsigned int size, const std::string& data)
{
	m_Fonts.push_back(new Font(data + file, size));
	return m_Fonts.back();
}
