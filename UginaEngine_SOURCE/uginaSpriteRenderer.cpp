#include "uginaSpriteRenderer.h"
#include "uginaGameObject.h"
#include "uginaTransform.h"
#include "uginaRenderer.h"
namespace ugina
{
	SpriteRenderer::SpriteRenderer()
		:Component(enums::eCompnentType::SpriteRenderer),
		mTexture(nullptr),
		mSize(Vector2::One)//기본 사이즈 1x1
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

		if (mTexture == nullptr)
		{
			assert(false);
		}
		//유니티 방식의 컴포넌트와 좌표
		Transform* tr = getOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		
		//BMP파일일때
		if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Bmp)
		{
			TransparentBlt(hdc, pos.x, pos.y, mTexture->GetWidth() * mSize.x, mTexture->GetHeight() * mSize.y,
				mTexture->GetHdc(), 0, 0, mTexture->GetWidth(), mTexture->GetHeight(),
				RGB(255, 0, 255));
		}
		//png파일일때
		else if (mTexture->GetTextureType() == graphics::Texture::eTextureType::Png)
		{
			Gdiplus::Graphics graphics(hdc);
			graphics.DrawImage(mTexture->getImage()
				, Gdiplus::Rect(pos.x, pos.y, mTexture->GetWidth() * mSize.x, mTexture->GetHeight() * mSize.y));

		}
	}



}