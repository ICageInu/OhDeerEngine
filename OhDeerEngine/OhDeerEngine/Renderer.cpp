#include "OhDeerPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"

void OhDeerEngine::Renderer::Init(SDL_Window * window)
{
	m_Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void OhDeerEngine::Renderer::Render() const
{
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();
	
	SDL_RenderPresent(m_Renderer);
}

void OhDeerEngine::Renderer::Release()
{
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void OhDeerEngine::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void OhDeerEngine::Renderer::RenderTexture(const Texture2D& texture, const SDL_Rect* destRect, const SDL_Rect* srcRect, const SDL_Point& pivot, const float angle, bool isMirrororororor) const
{
	int w, h;
	SDL_GetRendererOutputSize(m_Renderer, &w, &h);
	SDL_Rect dst{destRect->x,h-destRect->y,destRect->w,destRect->h};
	
	SDL_RenderCopyEx(m_Renderer, texture.GetSDLTexture(), srcRect, &dst,angle,&pivot,(SDL_RendererFlip)isMirrororororor);
}

