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
			//현재 선택한 애니메이션이 재생완료면서 루프하는 애니메이션이면
			//애니메이션의 리셋함수 실행시켜서 다시 재생시킬 준비하기
			if (mActiveAnimation->IsComplete() == true)
			{
				if (events)
					events->mCompleteEvent();

				//현재 선택한 애니메이션이 재생완료면서 루프하는 애니메이션이면
				//애니메이션의 리셋함수 실행시켜서 다시 재생시킬 준비하기
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
		
		//현재 함수는 애니메이션을 만드는 함수인데 현재이름으로
		//이미 만들어놓은 애니메이션이 있다면 리턴
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
		// TODO: 여기에 return 문을 삽입합니다.
		Events* events = FindEvents(name);
		return events->startEvent.mEvent;
	}

	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{
		// TODO: 여기에 return 문을 삽입합니다.
		Events* events = FindEvents(name);
		return events->completeEvent.mEvent;
	}

	std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
	{
		// TODO: 여기에 return 문을 삽입합니다.
		Events* events = FindEvents(name);
		return events->endEvent.mEvent;
	}

}
