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
		//���� �ִϸ��̼��� �� ����Ǿ��ٸ� ��ŵ loop�ִϸ��̼ǿ� ���ؼ��� animator���� �ٷ�
		if (mbComplete)
		{
			return;
		}
		//mTime�� 0���� �����ؼ� ���ӷ����� ���µ��� duration�� �Ѿ�¼���
		//mTime�� �ٽ� 0�� �ǰ�,���� �ִϸ��̼��� �� �����¸� �ε����� 0����,�ƴϸ� ���� �ε����� ����Ű���� 
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

		
		if (renderer::mainCamera)
		{
			pos = renderer::mainCamera->CalculatePosition(pos);
		}
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 125; // 0(transparent) ~ 255(Opaque)

		Sprite sprite = mAnimationSheet[mIndex];
		HDC imgHdc = mTexture->GetHdc();
		//transparentblt�� bitblt�� ����� �̹��� ����Լ� 
		//���Լ��� �̹����� �����ϰ� �Ҽ� �ִ�
		AlphaBlend(hdc,pos.x,pos.y,sprite.size.x,sprite.size.y,
			imgHdc,sprite.leftTop.x,sprite.leftTop.y, sprite.size.x,sprite.size.y,
			func);
	}
	void Animation::CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration)
	{
		//��������Ʈ �̹������� ����� ��Ʈ�� �ؽ��� ������ �����Ŵ
		mTexture = spriteSheet;

		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite sprite = {};
			//������ �»�ܺ��� �����ؼ� size�� ũ��� ������ ���Ѹ�ŭ �ִϸ��̼� ��������Ʈ �̹����� ������
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