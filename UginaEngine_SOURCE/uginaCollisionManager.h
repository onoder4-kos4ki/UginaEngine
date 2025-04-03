#pragma once
#include "CommonInclude.h"
#include "uginaBoxCollider2D.h"	;
#include "uginaCircleCollider2D.h"
namespace ugina
{
	using namespace enums;
	class CollisionManager
	{
	public :
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);

		static void CollisionLayerCheck(eLayerType left, eLayerType right, bool enable);
		static void LayerCollision(class Scene* scene, eLayerType right);
		static void colliderCollision(Collider* left, Collider* right);
	};
}


