#pragma once
namespace ugina
{
	namespace enums
	{
		enum class eComponentType
		{
			Transform,
			Collider,
			Script,
			SpriteRenderer,
			Animator,
			Camera,
			End
		};
		enum class eLayerType
		{
			None,
			BackGround,
			Animal,
			Player,
			Particle,
			Max = 16,

		};
		enum class eResourceType
		{
			Texture,
			AudioClip,
			Animation,
			Prefab,
			Count
		};
		enum class eColliderType
		{
			Circle2D,
			Rect2D,
			End
		};
	}
}