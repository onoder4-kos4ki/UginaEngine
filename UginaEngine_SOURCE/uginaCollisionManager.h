#pragma once
#include "CommonInclude.h"
#include "uginaBoxCollider2D.h"	;
#include "uginaCircleCollider2D.h"
namespace ugina
{
	using namespace enums;
	union CollisionID
	{
		struct
		{
			UINT32 left;
			UINT32 right;
		};
		UINT64 id;
	};
	class CollisionManager
	{
	public :
		static void Initialize();
		static void Update();
		static void LateUpdate();
		static void Render(HDC hdc);

		static void CollisionLayerCheck(eLayerType left, eLayerType right, bool enable);
		static void LayerCollision(class Scene* scene, eLayerType left, eLayerType right);
		static void colliderCollision(Collider* left, Collider* right);
		static bool Intersect(Collider* left, Collider* right);

	private:
		//
		static std::bitset<(UINT)eLayerType::Max> mCollisionLayerMatrix[(UINT)eLayerType::Max];

		static std::unordered_map<UINT64, bool> mCollisionMap;
	};
}


