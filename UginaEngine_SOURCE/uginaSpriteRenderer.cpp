#include "uginaSpriteRenderer.h"
#include "uginaGameObject.h"
#include "uginaTransform.h"
namespace ugina
{
	SpriteRenderer::SpriteRenderer()
		:mImage(nullptr)
		,mWidth(0)
		,mHeight(0)
	{
	}

	SpriteRenderer::~SpriteRenderer()
	{
	}

	void SpriteRenderer::Initialize()
	{
	}

	void SpriteRenderer::Update()
	{
	}

	void SpriteRenderer::LateUpdate()
	{
	}

	void SpriteRenderer::Render(HDC hdc)
	{
		//유니티 방식의 컴포넌트와 좌표
		Transform* tr = getOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		//그래픽 객체 생성
		Gdiplus::Graphics graphics(hdc);
		graphics.DrawImage(mImage, Gdiplus::Rect(pos.x, pos.y, mWidth, mHeight));
		
	}

	void SpriteRenderer::ImageLoad(const std::wstring& path)
	{
		mImage = Gdiplus::Image::FromFile(path.c_str());
		mWidth = mImage->GetWidth();
		mHeight = mImage->GetHeight();
	}

}