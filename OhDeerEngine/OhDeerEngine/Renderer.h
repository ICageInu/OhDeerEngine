#pragma once
#include "Singleton.h"

struct SDL_Rect;
struct SDL_Point;
struct SDL_Window;
struct SDL_Renderer;

namespace OhDeerEngine
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Release();
		void RenderTexture(const Texture2D& texture, const float x,const float y) const;

		void RenderTexture(const Texture2D& texture, const SDL_Rect* destRect, const SDL_Rect* srcRect, const SDL_Point& pivot, const float angle, bool isMirrororororor) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	private:
		SDL_Renderer* m_Renderer{};
	};
}

