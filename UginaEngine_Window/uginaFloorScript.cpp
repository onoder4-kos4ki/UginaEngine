#include "uginaFloorScript.h"

#include "uginaCatScript.h"
#include "uginaInput.h"
#include "uginaTransform.h"
#include "uginaTime.h"
#include "uginaGameObject.h"
#include "uginaAnimator.h"
#include "uginaObject.h"
#include "uginaRigidbody.h"

namespace ugina
{
	FloorScript::FloorScript()
	{
	}
	FloorScript::~FloorScript()
	{
	}
	void FloorScript::Initialize()
	{
	}
	void FloorScript::Update()
	{
	}
	void FloorScript::LateUpdate()
	{
	}
	void FloorScript::Render(HDC hdc)
	{
	}
	void FloorScript::OnCollisionEnter(Collider* other)
	{
		Rigidbody* playerRb = other->getOwner()->GetComponent<Rigidbody>();
		Transform* playerTr = other->getOwner()->GetComponent<Transform>();
		Collider* playerCol = other;

		Rigidbody* floorRb = this->getOwner()->GetComponent<Rigidbody>();
		Transform* floorTr = this->getOwner()->GetComponent<Transform>();
		Collider* floorCol = this->getOwner()->GetComponent<Collider>();

		float len = fabs(playerTr->GetPosition().y - floorTr->GetPosition().y);
		float scale = fabs(playerCol->GetSize().y * 100 / 2.0f - floorCol->GetSize().y * 100 / 2.0f);

		if (len < scale)
		{
			Vector2 playerPos = playerTr->GetPosition();
			playerPos.y -= (scale - len) - 1.0f;
			playerTr->SetPosition(playerPos);
		}

		playerRb->SetGround(true);

	}
	void FloorScript::OnCollisionStay(Collider* other)
	{
	}
	void FloorScript::OnCollisionExit(Collider* other)
	{
	}
}