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
		if (mTarget)
		{
			Transform* tr = mTarget->GetComponent<Transform>();
			mLookPosition = tr->GetPosition();
		}
		Transform* cameraTr = getOwner()->GetComponent<Transform>();
		mLookPosition = cameraTr->GetPosition();
		//카메라가 이동한 거리(카메라의 좌상단) = 카메라가 바라보는 위치(카메라의중앙) - 카메라의 해상도 절반
		mDistance = mLookPosition - (mResolution / 2.0f);

	}
	void Camera::LateUpdate()
	{
	}
	void Camera::Render(HDC hdc)
	{
	}
}