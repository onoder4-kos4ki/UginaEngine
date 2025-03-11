#include "uginaPlayerScript.h"
#include "uginaInput.h"
#include "uginaTransform.h"
#include "uginaTime.h"
#include "uginaGameObject.h"
#include "uginaAnimator.h"

namespace ugina
{

	PlayerScript::PlayerScript()
		:mstate(PlayerScript::eState::SitDown)
		, mAnimator(nullptr)
	{
	}

	PlayerScript::~PlayerScript()
	{
	}

	void PlayerScript::Initialize()
	{
	}

	void PlayerScript::Update()
	{
		if (mAnimator == nullptr)
		{
			mAnimator = getOwner()->GetComponent<Animator>();
		}
		switch (mstate)
		{
		case ugina::PlayerScript::eState::SitDown:
			sitDown();
			break;
		case ugina::PlayerScript::eState::Walk:
			move();
			break;
		case ugina::PlayerScript::eState::Sleep:
			break;
		case ugina::PlayerScript::eState::Attak:
			break;
		default:
			break;
		}
	}

	void PlayerScript::LateUpdate()
	{
	}

	void PlayerScript::Render(HDC hdc)
	{
	}
	void PlayerScript::sitDown()
	{
		if (Input::GetKey(keyCode::D))
		{
			mstate = PlayerScript::eState::Walk;
			mAnimator->PlayAnimation(L"RightWalk");
		}
		if (Input::GetKey(keyCode::A))
		{
			mstate = PlayerScript::eState::Walk;
		}
		if (Input::GetKey(keyCode::W))
		{
			mstate = PlayerScript::eState::Walk;
		}
		if (Input::GetKey(keyCode::D))
		{
			mstate = PlayerScript::eState::Walk;
		}
	}
	void PlayerScript::move()
	{
		Transform* tr = getOwner()->GetComponent<Transform>();
		Vector2 pos = tr->GetPosition();

		if (Input::GetKey(keyCode::D))
		{
			pos.x += 100.0f * Time::DeltaTime();
		}
		if (Input::GetKey(keyCode::A))
		{
			pos.x -= 100.0f * Time::DeltaTime();
		}
		if (Input::GetKey(keyCode::W))
		{
			pos.y -= 100.0f * Time::DeltaTime();
		}
		if (Input::GetKey(keyCode::S))
		{
			pos.y += 100.0f * Time::DeltaTime();
		}
		tr->SetPosition(pos);
		if(Input::GetKeyUp(keyCode::D)|| Input::GetKeyUp(keyCode::A) || Input::GetKeyUp(keyCode::W) || 
			Input::GetKeyUp(keyCode::S))
		{
			mstate = PlayerScript::eState::SitDown;
			mAnimator->PlayAnimation(L"SitDown", false);
		}
	}
}
