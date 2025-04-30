#include "uginaCamera.h"
#include "uginaApplication.h"
#include "uginaTransform.h"
#include "uginaGameObject.h"
extern ugina::Application api;
namespace ugina
{
	Camera::Camera()
		:Component(enums::eComponentType::Camera)
		, mDistance(Vector2::Zero)
		, mResolution(Vector2::Zero)
		, mLookPosition(Vector2::Zero)
		, mTarget(nullptr)
	{
	}
	Camera::~Camera()
	{
	}
	void Camera::Initialize()
	{
		mResolution.x = api.GetWidth();
		mResolution.y = api.Getheight();
	}
	void Camera::Update()
	{

		//���� �ٶ󺸴� Ÿ���� �����ϸ� Ÿ���� ���������� ī�޶� �ٶ󺸴� ����(mLookPosition) ����
		if (mTarget)
		{
			Transform* tr = mTarget->GetComponent<Transform>();
			mLookPosition = tr->GetPosition();
		}
		//�ٶ󺸴� Ÿ���� �������� �ʴٸ� ���� ī�޶��� ��ġ�� �ٶ󺸴� �������� 
		else
		{
			Transform* cameraTr = GetOwner()->GetComponent<Transform>();
			mLookPosition = cameraTr->GetPosition();
		}		
		//ī�޶� �̵��� �Ÿ�(ī�޶��� �»��) = ī�޶� �ٶ󺸴� ��ġ(Ÿ�������� or ī�޶���������) - ī�޶� �ػ��� ����(�߾�)
		mDistance = mLookPosition - (mResolution / 2.0f);

	}
	void Camera::LateUpdate()
	{
	}
	void Camera::Render(HDC hdc)
	{
	}
}