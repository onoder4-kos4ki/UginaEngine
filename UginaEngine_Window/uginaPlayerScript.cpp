#include "uginaPlayerScript.h"
#include "uginaInput.h"
#include "uginaTransform.h"
#include "uginaTime.h"
#include "uginaGameObject.h"
#include "uginaAnimator.h"
#include "uginaResources.h"
#include "uginaCat.h"
#include "uginaObject.h"
#include "uginaCatScript.h"
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

	void PlayerScript::AttackEffect()
	{
		Cat* cat = object::Instantiate<Cat>(enums::eLayerType::Animal);
		cat->AddComponent<CatScript>();

		graphics::Texture* catTex = Resources::Find<graphics::Texture>(L"CAT");
		Animator* catAnimator = cat->AddComponent<Animator>();
		catAnimator->CreateAnimation(L"DOWNWALK", catTex
			, Vector2(0.0f, 0.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		catAnimator->CreateAnimation(L"RIGHTWALK", catTex
			, Vector2(0.0f, 32.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		catAnimator->CreateAnimation(L"UPWALK", catTex
			, Vector2(0.0f, 64.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		catAnimator->CreateAnimation(L"LEFTWALK", catTex
			, Vector2(0.0f, 96.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		catAnimator->CreateAnimation(L"SITDOWN", catTex
			, Vector2(0.0f, 128.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		catAnimator->CreateAnimation(L"GROOMING", catTex
			, Vector2(0.0f, 160.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
		catAnimator->CreateAnimation(L"LAYDOWN", catTex
			, Vector2(0.0f, 192.0f), Vector2(32.0f, 32.0f), Vector2::Zero, 4, 0.1f);
	
		catAnimator->PlayAnimation(L"SITDOWN", false);
		cat->GetComponent<Transform>()->SetPosition(Vector2(200.0f, 200.0f));
		cat->GetComponent<Transform>()->SetScale(Vector2(2.0f, 2.0f));
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
		if (Input::GetKeyUp(keyCode::D) || Input::GetKeyUp(keyCode::A) || Input::GetKeyUp(keyCode::W) ||
			Input::GetKeyUp(keyCode::S))
		{
			mstate = PlayerScript::eState::Idle;
			mAnimator->PlayAnimation(L"SITDOWN", false);
		}
	}
	void PlayerScript::GiveWater()
	{
		if (mAnimator->IsComplete())
		{
			mstate = eState::Idle;
			mAnimator->PlayAnimation(L"IDLE", false);
		}
	}
}
