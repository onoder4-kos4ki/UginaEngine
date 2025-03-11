#pragma once
#include "..\\UginaEngine_SOURCE\\uginaScript.h"
namespace ugina
{
	class PlayerScript :public Script
	{
	public:
		enum class eState
		{
			SitDown,
			Walk,
			Sleep,
			Attak
		};
		PlayerScript();
		~PlayerScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;
	private:
		void sitDown();
		void move();

	private:
		eState mstate;
		class Animator* mAnimator;
	};
}

