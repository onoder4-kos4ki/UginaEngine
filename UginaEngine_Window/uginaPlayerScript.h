#pragma once
#include "..\\UginaEngine_SOURCE\\uginaScript.h"
namespace ugina
{
	class PlayerScript :public Script
	{
	public:
		enum class eState
		{
			Idle,
			Walk,
			Sleep,
			GiveWater,
			Attak
		};
		PlayerScript();
		~PlayerScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

		void AttackEffect();

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;
	private:
		void Idle();
		void move();
		void GiveWater();

	private:
		eState mstate;
		class Animator* mAnimator;

		//�ִϸ��̼� �̺�Ʈ�� ���� ��������Ʈ��
		
		//void (*Startevent)();
		//std::function<void()> start;
		//void (*CompleteEvent)();
		//void (*EndEvent)();
	};
}

