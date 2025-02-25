#pragma once
namespace ugina
{
	namespace enums
	{
		enum class eLayerType
		{
			None,
			BackGround,
			Player,
			Max = 16,

		};
		enum class eResourceType
		{
			Texture,
			AudioClip,
			Prefab,
			Count
		};
	}
}