#pragma once
#include "uginaComponent.h"
#include "uginaGameObject.h"
namespace ugina
{
	using namespace ugina::math;
	class Camera :public Component
	{
	public:
		//오브젝트의 좌푯값으로부터 카메라가 이동한 거리만큼 빼서
		//카메라의 좌푯값을 기준으로 오브젝트의 pos를 다시계산(즉 리턴값은 오브젝트의 새로운좌푯값)
		Vector2 CalculatePosition(Vector2 pos) { return pos - mDistance; }

		Camera();
		~Camera();
		virtual void Initialize()		override;
		virtual void Update()			override;
		virtual void LateUpdate()		override;
		virtual void Render(HDC hdc)	override;

	private:
		 GameObject* mTarget;
		 //카메라가 이동한 거리
		 Vector2 mDistance;
		 //키메라의 해상도
		 Vector2 mResolution;
		 //카메라가 바라보는 좌표
		 Vector2 mLookPosition;
	};
}
