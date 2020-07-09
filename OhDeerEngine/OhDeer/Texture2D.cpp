#include "OhDeerPCH.h"
#include "Texture2D.h"
#include <SDL.h>

OhDeerEngine::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_Texture);

}

SDL_Texture* OhDeerEngine::Texture2D::GetSDLTexture() const
{
	return m_Texture;
}

OhDeerEngine::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_Texture = texture;
}
