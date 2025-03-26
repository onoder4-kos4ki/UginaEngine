#include "uginaCatScript.h"
#include "uginaGameObject.h"
#include "uginaTime.h"
#include "uginaAnimator.h"
#include "uginaObject.h"
namespace ugina
{
	CatScript::CatScript()
		:mState(CatScript::eState::SitDown)
		, mAnimator(nullptr)
		, mTime(0.0f)
		, mDeathTime(0.0f)
	{
	}
	CatScript::~CatScript()
	{
	}
	void CatScript::Initialize()
	{
	}
	void CatScript::Update()
	{
		mDeathTime += Time::DeltaTime();
		if (mDeathTime > 6.0f)
		{

		}
		if (mAnimator == nullptr)
		{
			mAnimator = getOwner()->GetComponent<Animator>();
		}
		switch (mState)
		{
		case ugina::CatScript::eState::SitDown:
			sitDown();
			break;
		case ugina::CatScript::eState::Walk:
			move();
			break;
		case ugina::CatScript::eState::Sleep:
			break;
		case ugina::CatScript::eState::LayDown:
			break;
		case ugina::CatScript::eState::Attack:
			break;
		case ugina::CatScript::eState::Count:
			break;
		default:
			break;
		}
	}
	void CatScript::LateUpdate()
	{
	}
	void CatScript::Render(HDC hdc)
	{
	}
	void CatScript::sitDown()
	{
		mTime += Time::DeltaTime();
		//����� �ð��� 3�ʰ� ������..
		if (mTime > 3.0f)
		{
			//���¸� �ȱ�� ��ȯ�Ѵ�
			mState = CatScript::eState::Walk;
			//������ �������� 4����
			int direction = (rand() % 4);
			mDirection = (eDirection)direction;
			PlayWalAnimationByDirection(mDirection);
			//�ð� �ʱ�ȭ
			mTime = 0.0f;
		}
	}
	void CatScript::move()
	{
		mTime += Time::DeltaTime();
		if (mTime > 2.0f)
		{
			int isLayDown = rand() % 2;
			if (isLayDown)
			{
				mState = eState::LayDown;
				mAnimator->PlayAnimation(L"LAYDOWN", false);
			}
			else
			{
				mState = eState::SitDown;
				mAnimator->PlayAnimation(L"SITDOWN", false);
			}
		}

		Transform* tr = getOwner()->GetComponent<Transform>();
		translate(tr);
	}
	void CatScript::laydDown()
	{
	}
	void CatScript::PlayWalAnimationByDirection(eDirection dir)
	{
		switch (dir)
		{
		case ugina::CatScript::eDirection::Left:
			mAnimator->PlayAnimation(L"LEFTWALK", true);
			break;
		case ugina::CatScript::eDirection::Right:
			mAnimator->PlayAnimation(L"RIGHTWALK", true);
			break;
		case ugina::CatScript::eDirection::Down:
			mAnimator->PlayAnimation(L"DOWNWALK", true);
			break;
		case ugina::CatScript::eDirection::Up:
			mAnimator->PlayAnimation(L"UPWALK", true);
			break;
		case ugina::CatScript::eDirection::End:
			break;
		default:
			assert(false);
			break;
		}
	}
	void CatScript::translate(Transform* tr)
	{

		Vector2 pos = tr->GetPosition();
		switch (mDirection)
		{
		case ugina::CatScript::eDirection::Left:
			pos.x -= 100.0f * Time::DeltaTime();
			break;
		case ugina::CatScript::eDirection::Right:
			pos.x += 100.0f * Time::DeltaTime();
			break;
		case ugina::CatScript::eDirection::Down:
			pos.y += 100.0f * Time::DeltaTime();
			break;
		case ugina::CatScript::eDirection::Up:
			pos.y -= 100.0f * Time::DeltaTime();
			break;
		case ugina::CatScript::eDirection::End:
			break;
		default:
			assert(false);
			break;
		}
		tr->SetPosition(pos);
	}
}