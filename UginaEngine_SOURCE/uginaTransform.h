#pragma once
#include "uginaEntity.h"
#include "uginaComponent.h"
namespace ugina
{
	using namespace math;
	class Transform :public Component
	{
	public:
		Transform();
		~Transform();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		void SetPos(Vector2 pos) { mPosition.x = pos.x; mPosition.y = pos.y; }
		Vector2 GetPosition() { return mPosition; }

	private:
		Vector2 mPosition;

	};
}

