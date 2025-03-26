#pragma once
#include "uginaComponent.h"
#include "uginaAnimation.h"

namespace ugina
{
	class Animator : public Component
	{
	public:
		//애니메이션 이벤트
		struct Event
		{
			//객체를 옮겨주는 기능을 구현
			void operator =(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			//Event구조체로 변수를 만들면 그 변수 이름을 가지고 내부의 function 변수(즉 함수)를 바로 호출하기위한 오퍼레이터
			void operator()()
			{
				if (mEvent)
				{
					mEvent();
				}
			}
			//반환값이 void에 매개변수가 없는 델리게이트 변수
			std::function<void()> mEvent;
		};

		struct Events
		{
			Event startEvent;
			Event completeEvent;
			Event endEvent;
		};

		Animator();
		~Animator();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void CreateAnimation(const std::wstring& name
			, graphics::Texture* spriteSheet
			, Vector2 leftTop
			, Vector2 size
			, Vector2 offset
			, UINT spriteLength
			, float duration);
		//폴더에 있는 텍스쳐파일을 합쳐서 하나의 애니메이션 시트를 만들어 저장하는 함수
		void CreateAnimationByFolder(const std::wstring& name,
			const std::wstring& path,Vector2 offset, float duration);

		Animation* FindAnimation(const std::wstring& name);
		void PlayAnimation(const std::wstring& name, bool loop = true);

		Events* FindEvents(const std::wstring& name);
		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);
		bool IsComplete() { return mActiveAnimation->IsComplete(); }
	private:
		std::map<std::wstring, Animation*> mAnimations;

		Animation* mActiveAnimation;
		//애니메이션이 루프를 도는가
		bool mbLoop;

		std::map<std::wstring, Events*> mEvents;
	};
}

