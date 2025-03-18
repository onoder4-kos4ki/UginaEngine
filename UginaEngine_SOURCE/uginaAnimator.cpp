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
		for (auto& iter : mAnimations)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}

	void ugina::Animator::Initialize()
	{
	}

	void ugina::Animator::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();

			Events* events = FindEvents(mActiveAnimation->getName());
			//���� ������ �ִϸ��̼��� ����Ϸ�鼭 �����ϴ� �ִϸ��̼��̸�
			//�ִϸ��̼��� �����Լ� ������Ѽ� �ٽ� �����ų �غ��ϱ�
			if (mActiveAnimation->IsComplete() == true)
			{
				if (events)
					events->mCompleteEvent();

				//���� ������ �ִϸ��̼��� ����Ϸ�鼭 �����ϴ� �ִϸ��̼��̸�
				//�ִϸ��̼��� �����Լ� ������Ѽ� �ٽ� �����ų �غ��ϱ�
				if (mbLoop == true)
				{
					mActiveAnimation->Reset();
				}
				
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

		Events* events = new Events();
		mEvents.insert(std::make_pair(name,events));
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

		if (mActiveAnimation)
		{
			Events* currentEvents = FindEvents(mActiveAnimation->getName());

			if (currentEvents)
			{
				currentEvents->endEvent();
			}
		}
		Events* nextEvents = FindEvents(animation->getName());
		if (nextEvents)
		{
			nextEvents->startEvent();
		}
			
		mActiveAnimation = animation;
		mActiveAnimation->Reset();
		mbLoop = loop;
	}

	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		auto iter = mEvents.find(name);
		if (iter == mEvents.end())
		{
			return nullptr;
		}
		return iter->second;
	}

	std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
	{
		// TODO: ���⿡ return ���� �����մϴ�.
		Events* events = FindEvents(name);
		return events->startEvent.mEvent;
	}

	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{
		// TODO: ���⿡ return ���� �����մϴ�.
		Events* events = FindEvents(name);
		return events->completeEvent.mEvent;
	}

	std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
	{
		// TODO: ���⿡ return ���� �����մϴ�.
		Events* events = FindEvents(name);
		return events->endEvent.mEvent;
	}

}
