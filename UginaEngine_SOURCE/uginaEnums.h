#pragma once
namespace ugina
{
	namespace enums
	{
		enum class eComponentType
		{
			Transform,
			SpriteRenderer,
			Animator,
			Script,
			Camera,
			End
		};
		enum class eLayerType
		{
			None,
			BackGround,
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
	}
}