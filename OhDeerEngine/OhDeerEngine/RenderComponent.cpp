#include "OhDeerPCH.h"

#include <glm/gtx/rotate_vector.hpp>
#include "RenderComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "Texture2D.h"
#include "Renderer.h"

void OhDeerEngine::RenderComponent::Update(const float) {}

void OhDeerEngine::RenderComponent::Render() const
{
	const glm::fvec2& pos = m_pParent->GetComponent<TransformComponent>()->GetPosition();


	SDL_Rect dstRect{ static_cast<int>(pos.x), static_cast<int>(pos.y) };
	SDL_QueryTexture(m_Animation.Image->GetSDLTexture(), nullptr, nullptr, &dstRect.w, &dstRect.h);

	//recalculating of dimensions
	//also recalculation of what needed for each curr frame
	SDL_Rect srcRect = { int(m_Animation.SrcPos.x * dstRect.w), int(m_Animation.SrcPos.y * dstRect.h), int(m_Animation.SrcDim.x * dstRect.w), int(m_Animation.SrcDim.y * dstRect.h) };
	if (m_Animation.IsAnimated)
	{
		srcRect = { srcRect.x + (m_Animation.CurrFrame % m_Animation.Columns) * srcRect.w / (m_Animation.Columns),
			srcRect.y + (m_Animation.CurrFrame / m_Animation.Columns) * srcRect.h / (m_Animation.Rows),
			srcRect.w / m_Animation.Columns,
			srcRect.h / m_Animation.Rows };
	}
	if (m_Animation.DrawWidth != 0 && m_Animation.DrawHeight != 0)
	{
		dstRect.w = m_Animation.DrawWidth;
		dstRect.h = m_Animation.DrawHeight;
	}
	SDL_Point pivot = { int(m_Animation.Pivot.x * dstRect.w), int(m_Animation.Pivot.y * dstRect.h) };
	glm::fvec2 worldOffset = { m_Animation.Offset.x * dstRect.w, m_Animation.Offset.y * dstRect.h };
	worldOffset = glm::rotate(worldOffset, -m_pParent->GetComponent<TransformComponent>()->GetRotation() * float(M_PI) / 180.0f);
	dstRect.x += int(worldOffset.x) - pivot.x;
	dstRect.y += int(worldOffset.y) + pivot.y;

	Renderer::GetInstance().RenderTexture(*m_Animation.Image, &dstRect, &srcRect, pivot, m_pParent->GetComponent<TransformComponent>()->GetRotation() + m_Animation.Angle, m_Animation.IsMirrored);
}

OhDeerEngine::TextureAnimation OhDeerEngine::RenderComponent::GetTextureAnimation() const
{
	return m_Animation;
}

void OhDeerEngine::RenderComponent::FixedUpdate(const float deltaT)
{

	if (!m_Animation.IsAnimated) return;
	m_Animation.CurrTime += deltaT;
	//this to prevent this from catching up, cause we don't all like sonic
	while (m_Animation.CurrTime >= m_Animation.FrameTime)
	{
		m_Animation.CurrTime -= m_Animation.FrameTime;
		if (m_Animation.IsReversed)
		{
			m_Animation.CurrFrame--;
			if (m_Animation.CurrFrame < 0) m_Animation.CurrFrame += m_Animation.Rows * m_Animation.Columns;
		}
		else {
			m_Animation.CurrFrame++;
			m_Animation.CurrFrame %= m_Animation.Rows * m_Animation.Columns;
		}
	}
}

void OhDeerEngine::RenderComponent::SetTexture(Texture2D* texture, const int drawWidth, const int drawHeight, const glm::fvec2& pivot, bool isAnimated, bool reverse, const int rows, const int columns, const float frameTime, bool mirror, float angle, const glm::fvec2 srcPos, const glm::fvec2 srcDim, const glm::fvec2 offSet)
{
	//TODO please fix naming conventions
	m_Animation = TextureAnimation{ texture,pivot,srcPos,srcDim,offSet,frameTime,0,angle,rows,columns,0,drawWidth,drawHeight,isAnimated,reverse,mirror };
}
