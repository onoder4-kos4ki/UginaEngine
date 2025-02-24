#include "uginaPlayer.h"
#include "uginaInput.h"
#include "uginaTransform.h"
#include "uginaTime.h"
namespace ugina
{
	void Player::Initialize()
	{
		GameObject::Initialize();
	}
	void Player::Update()
	{
		GameObject::Update();
	}
	void Player::LateUpdate()
	{
		GameObject::LateUpdate();

		if (Input::GetKey(keyCode::D))
		{
			Transform* tr = GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos.x += 100.0f * Time::DeltaTime();
			tr->SetPos(pos);
		}
	}
	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
}