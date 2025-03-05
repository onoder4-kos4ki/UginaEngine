#include "uginaAnimator.h"


namespace ugina
{

	ugina::Animator::Animator()
		:Component(enums::eComponentType::Animator)
		,mAnimations{}
		,mActiveAnimation(nullptr)
		,mbLoop(false)
	{
	}

	ugina::Animator::~Animator()
	{
	}

	void ugina::Animator::Initialize()
	{
	}

	void ugina::Animator::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();

			//���� ������ �ִϸ��̼��� ����Ϸ�鼭 �����ϴ� �ִϸ��̼��̸�
			//�ִϸ��̼��� �����Լ� ������Ѽ� �ٽ� �����ų �غ��ϱ�
			if (mActiveAnimation->IsComplete() == true
				&& mbLoop == true)
			{
				mActiveAnimation->Reset();
			}
		}
	}

	void ugina::Animator::LateUpdate()
	{
	}

	void ugina::Animator::Render(HDC hdc)
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Render(hdc);
		}
	}

	void ugina::Animator::CreateAnimation(const std::wstring& name, graphics::Texture* spriteSheet, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration)
	{
		
		Animation* animation = nullptr;
		animation = FindAnimation(name);
		
		//���� �Լ��� �ִϸ��̼��� ����� �Լ��ε� �����̸�����
		//�̹� �������� �ִϸ��̼��� �ִٸ� ����
		if (animation != nullptr)
		{
			return;
		}
		animation = new Animation();
		animation->CreateAnimation(name, spriteSheet, leftTop, size, offset, spriteLength, duration);
		animation->SetAnimator(this);

		mAnimations.insert(std::make_pair(name, animation));
		//TODO
	}

	ugina::Animation* ugina::Animator::FindAnimation(const std::wstring& name)
	{
		//TODO
		auto iter = mAnimations.find(name);
		if (iter == mAnimations.end())
		{
			return nullptr;
		}
		return iter->second;
	}

	void ugina::Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		Animation* animation = FindAnimation(name);
		if (animation == nullptr)
		{
			return;
		}
		mActiveAnimation = animation;
		mActiveAnimation->Reset();
		mbLoop = loop;
	}

}
