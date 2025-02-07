#pragma once
#include "CommonInclude.h"
namespace ugina
{
	class Time
	{
	public:
		static void Initailize();
		static void Update();
		static void Render();

		static float DeltaTime() { return DeltaTimeValue; }

	private:

		static float DeltaTimeValue;
	};
}

