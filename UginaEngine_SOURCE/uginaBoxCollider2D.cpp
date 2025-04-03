#include "uginaBoxCollider2D.h"
#include "uginaTransform.h"
#include "uginaGameObject.h"
namespace ugina
{
	BoxCollider2D::BoxCollider2D()
		:Collider()
	{
	}
	BoxCollider2D::~BoxCollider2D()
	{
	}
	void BoxCollider2D::Initialize()
	{
	}
	void BoxCollider2D::Update()
	{
	}
	void BoxCollider2D::LateUpdate()
	{
	}
	void BoxCollider2D::Render(HDC hdc)
	{
		Transform* tr = getOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		Vector2 offset = GetOffset();
		
		//GetStockObject로 만든 HBRUSH는 메모리해제를 안해줘도 된다
		HBRUSH transparentBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldbrush = (HBRUSH)SelectObject(hdc, transparentBrush);
		HPEN greenPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
		HPEN oldPen = (HPEN)SelectObject(hdc, greenPen);

		Rectangle(hdc,
			pos.x + offset.x
			, pos.y + offset.y
			, pos.x + offset.x + 100
			, pos.y + offset.y + 100);

		SelectObject(hdc, oldbrush);
		SelectObject(hdc, oldPen);
		DeleteObject(greenPen);
	}
}