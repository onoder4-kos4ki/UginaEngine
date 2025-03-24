#pragma once
#include "..\\UginaEngine_SOURCE\\uginaScript.h"
#include "..\\UginaEngine_SOURCE\\uginaTransform.h"
namespace ugina
{
	class CatScript :public Script
	{
	public:
		enum class eState
		{

			SitDown,
			Walk,
			Sleep,
			LayDown,
			Attack,
			Count
		};
		enum class eDirection
		{
			Left,
			Right,
			Down,
			Up,
			End,
		};

		CatScript();
		~CatScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:
		void sitDown();
		void move();
		void laydDown();

		void PlayWalAnimationByDirection(eDirection dir);
		//현재 좌표를 변환시키는 함수
		void translate(Transform* tr);

	private:
		eState mState;
		class Animator* mAnimator;
		eDirection mDirection;
		float mTime;
	};
}