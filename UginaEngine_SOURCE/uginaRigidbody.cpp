#include "uginaRigidbody.h"
#include "uginaTime.h"
#include "uginaTransform.h"
#include "uginaGameObject.h"
namespace ugina
{
	Rigidbody::Rigidbody()
		:Component(enums::eComponentType::Rigidbody)
		, mbGround(false)
		, mMass(1.0f)
		, mFriction(10.0f)
		,mForce(Vector2::Zero)
		,mVelocity(Vector2::Zero)
		,mLimitedVelocity(Vector2(200.0f,1000.0f))
		,mGravity(Vector2(0.0f,800.0f))
		,mAccelation(Vector2::Zero)
	{
	}

	Rigidbody::~Rigidbody()
	{
	}

	void Rigidbody::Initialize()
	{
	}

	void Rigidbody::Update()
	{
		// f(힘)= m(질량)a(가속도)
		// 
		mAccelation = mForce / mMass;

		mVelocity += mAccelation * Time::DeltaTime();
		if (!(mVelocity == Vector2::Zero))
		{
			Vector2 friction = -mVelocity;
			friction = friction.normalize() * mFriction * mMass * Time::DeltaTime();
			if (mVelocity.length() <= friction.length())
			{
				mVelocity = Vector2::Zero;
			}
			else
			{
				mVelocity += friction;
			}
			Transform* tr = getOwner()->GetComponent<Transform>();
			Vector2 pos = tr->GetPosition();
			pos = pos + mVelocity * Time::DeltaTime();
			tr->SetPosition(pos);

			mForce.clear();
		}
	}

	void Rigidbody::LateUpdate()
	{
	}

	void Rigidbody::Render(HDC hdc)
	{
	}
}