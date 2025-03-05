#pragma once
#include "uginaComponent.h"
#include "uginaGameObject.h"
namespace ugina
{
	using namespace ugina::math;
	class Camera :public Component
	{
	public:
		//������Ʈ�� ��ǩ�����κ��� ī�޶� �̵��� �Ÿ���ŭ ����
		//ī�޶��� ��ǩ���� �������� ������Ʈ�� pos�� �ٽð��(�� ���ϰ��� ������Ʈ�� ���ο���ǩ��)
		Vector2 CalculatePosition(Vector2 pos) { return pos - mDistance; }

		Camera();
		~Camera();
		virtual void Initialize()		override;
		virtual void Update()			override;
		virtual void LateUpdate()		override;
		virtual void Render(HDC hdc)	override;

	private:
		 GameObject* mTarget;
		 //ī�޶� �̵��� �Ÿ�
		 Vector2 mDistance;
		 //Ű�޶��� �ػ�
		 Vector2 mResolution;
		 //ī�޶� �ٶ󺸴� ��ǥ
		 Vector2 mLookPosition;
	};
}
