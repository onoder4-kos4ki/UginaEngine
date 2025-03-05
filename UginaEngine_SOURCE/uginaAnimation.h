#pragma once
#include "uginaResource.h"
#include "uginaTexture.h"
namespace ugina
{
	class Animation : public Resource
	{
	public:

		struct Sprite
		{
			//스프라이트시트에서 현재스프라이트 이미지의 좌상단 좌푯값
			Vector2 leftTop;
			Vector2 size;
			Vector2 offset;

			//애니메이션 스프라이트의 재생시간간격
			float duration;

			Sprite()
				: leftTop(Vector2::Zero)
				, size(Vector2::Zero)
				, offset(Vector2::Zero)
				, duration(0.0f)
			{
			}
		};
		Animation();
		~Animation();

		HRESULT Load(const std::wstring& path) override;

		void Update();
		void Render(HDC hdc);

		void CreateAnimation(const std::wstring& name
			, graphics::Texture* spriteSheet
			, Vector2 leftTop
			, Vector2 size
			, Vector2 offset
			, UINT spriteLength
			, float duration);

		void Reset();
		bool IsComplete() { return mbComplete; }
		void SetAnimator(class Animator* animator) { mAnimator = animator; }

	private:
		
		class Animator* mAnimator;
		graphics::Texture* mTexture;
		
		//텍스쳐에서 이 애니메이션에서 가지는 부분만을 자르고
		//그부분을 또 스프라이트 vector로 쪼개서 저장시켜놓음
		std::vector<Sprite> mAnimationSheet;
		int mIndex;
		float mTime;
		//현재 애니메이션이 끝까지 재생되었는가
		bool mbComplete;
	};
}

