#include "uginaAnimation.h"
#include "uginaTime.h"
#include "uginaTransform.h"
#include "uginaGameObject.h"
#include "uginaRenderer.h"
#include "uginaCamera.h"
#include "uginaAnimator.h"
namespace ugina
{
	Animation::Animation()
		:Resource(enums::eResourceType::Animation)
		, mAnimator(nullptr)
		, mTexture(nullptr)
		, mAnimationSheet{}
		, mIndex(-1)
		, mTime(0.0f)
		, mbComplete(false)
	{
	}
	Animation::~Animation()
	{
	}
	HRESULT Animation::Load(const std::wstring& path)
	{
		return E_NOTIMPL;
	}
	void Animation::Update()
	{
		//현재 애니메이션이 다 재생되었다면 스킵 loop애니메이션에 관해서는 animator에서 다룸
		if (mbComplete)
		{
			return;
		}
		//mTime이 0부터 시작해서 게임루프를 도는동안 duration을 넘어가는순간
		//mTime은 다시 0이 되고,만약 애니메이션을 다 돈상태면 인덱스는 0으로,아니면 다음 인덱스를 가리키게함 
		mTime += Time::DeltaTime();
		if (mAnimationSheet[mIndex].duration < mTime)
		{
			mTime = 0.0f;
			if (mIndex < this->mAnimationSheet.size() - 1)
			{
				mIndex++;
			}
			else
			{
				
				mbComplete = true;
			}
		}
	}
	void Animation::Render(HDC hdc)
	{
		if (mTexture == nullptr)
		{
			return;
		}

		GameObject* gameObj = mAnimator->getOwner();
		Transform* tr = gameObj->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		float rot = tr->GetRotation();
		Vector2 scale = tr->GetScale();

		
		if (renderer::mainCamera)
		{
			pos = renderer::mainCamera->CalculatePosition(pos);
		}
		Sprite sprite = mAnimationSheet[mIndex];
		graphics::Texture::eTextureType type = mTexture->GetTextureType();
		if (type == graphics::Texture::eTextureType::Bmp)
		{
			BLENDFUNCTION func = {};
			func.BlendOp = AC_SRC_OVER;
			func.BlendFlags = 0;
			func.AlphaFormat = AC_SRC_ALPHA;
			func.SourceConstantAlpha = 125; // 0(transparent) ~ 255(Opaque)

			

			HDC imgHdc = mTexture->GetHdc();
			//transparentblt와 bitblt와 비슷한 이미지 출력함수 
			//이함수는 이미지를 투명하게 할수 있다
			AlphaBlend(hdc
				, pos.x - (sprite.size.x / 2.0f)
				, pos.y - (sprite.size.y / 2.0f)
				, sprite.size.x * scale.x
				, sprite.size.y * scale.y
				, imgHdc
				, sprite.leftTop.x
				, sprite.leftTop.y
				, sprite.size.x
				, sprite.size.y
				, func);
		}
		else if (type == graphics::Texture::eTextureType::Png)
		{
			Gdiplus::ImageAttributes imgAtt = {};
			imgAtt.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));

			Gdiplus::Graphics graphics(hdc);
			graphics.TranslateTransform(pos.x, pos.y);
			graphics.RotateTransform(rot);
			graphics.TranslateTransform(-pos.x, -pos.y);

			graphics.DrawImage(mTexture->GetImage()
				, Gdiplus::Rect
				(
					pos.x - (sprite.size.x / 2.0f)
					, pos.y - (sprite.size.y / 2.0f)
					, sprite.size.x * scale.x
					, sprite.size.y * scale.y
				)
				, sprite.leftTop.x
				, sprite.leftTop.y
				, sprite.size.x
				, sprite.size.y
				, Gdiplus::UnitPixel
				, /*&imgAtt*/nullptr
			);
		}
	}
	void Animation::CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration)
	{
		//스프라이트 이미지들이 저장된 시트를 텍스쳐 변수에 연결시킴
		mTexture = spriteSheet;

		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite sprite = {};
			//시작은 좌상단부터 시작해서 size의 크기와 순서를 곱한만큼 애니메이션 스프라이트 이미지를 저장함
			sprite.leftTop.x = leftTop.x + (size.x * i);
			sprite.leftTop.y = leftTop.y;
			sprite.duration = duration;
			sprite.size = size;
			sprite.offset = offset;

			mAnimationSheet.push_back(sprite);

		}
	}
	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}
}