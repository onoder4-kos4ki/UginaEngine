#include "uginaPlayerScript.h"
#include "uginaInput.h"
#include "uginaTransform.h"
#include "uginaTime.h"
#include "uginaGameObject.h"
#include "uginaAnimator.h"

namespace ugina
{

	PlayerScript::PlayerScript()
		:mstate(PlayerScript::eState::Idle)
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
		case ugina::PlayerScript::eState::Idle:
			Idle();
			break;
		case ugina::PlayerScript::eState::Walk:
			move();
			break;
		case ugina::PlayerScript::eState::Sleep:
			break;
		case ugina::PlayerScript::eState::GiveWater:
			GiveWater();
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
	
	void PlayerScript::Idle()
	{
		//마우스 왼쪽 버튼을 누를시 물을 주는 애니메이션 재생
		if (Input::GetKey(keyCode::LButton))
		{
			mstate = PlayerScript::eState::GiveWater;
			mAnimator->PlayAnimation(L"FRONTGIVEWATER", false);

			Vector2 mousePos = Input::GetMousePosition();
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
			mstate = PlayerScript::eState::Idle;
			mAnimator->PlayAnimation(L"SITDOWN", false);
		}
	}
	void PlayerScript::GiveWater()
	{
		if(mAnimator->iscom)
	}
}
