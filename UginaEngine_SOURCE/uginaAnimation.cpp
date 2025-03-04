#include "uginaAnimation.h"
#include "uginaTime.h"
#include "uginaTransform.h"
#include "uginaGameObject.h"
#include "uginaRenderer.h"
#include "uginaCamera.h"

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
	}
	void Animation::Render(HDC hdc)
	{
	}
	void Animation::CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration)
	{
		//스프라이트 이미지들이 저장된 시트를 텍스쳐 변수에 연결시킴
		mTexture = spriteSheet;
	}
	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}
}