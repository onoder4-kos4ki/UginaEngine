#include "uginaPlayerScript.h"
#include "uginaInput.h"
#include "uginaTransform.h"
#include "uginaTime.h"
#include "uginaGameObject.h"
ugina::PlayerScript::PlayerScript()
{
}

ugina::PlayerScript::~PlayerScript()
{
}

void ugina::PlayerScript::Initialize()
{
}

void ugina::PlayerScript::Update()
{
	if (Input::GetKey(keyCode::W))
	{
		Transform* tr = getOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos.y -= 100.0f * Time::DeltaTime();

		tr->SetPosition(pos);
	}
	if (Input::GetKey(keyCode::S))
	{
		Transform* tr = getOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos.y += 100.0f * Time::DeltaTime();

		tr->SetPosition(pos);
	}
	if (Input::GetKey(keyCode::A))
	{
		Transform* tr = getOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos.x -= 100.0f * Time::DeltaTime();

		tr->SetPosition(pos);
	}
	if (Input::GetKey(keyCode::D))
	{
		Transform* tr = getOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();
		pos.x += 100.0f * Time::DeltaTime();

		tr->SetPosition(pos);
	}
}

void ugina::PlayerScript::LateUpdate()
{
}

void ugina::PlayerScript::Render(HDC hdc)
{
}
