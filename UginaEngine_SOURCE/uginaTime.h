#pragma once
#include "CommonInclude.h"
namespace ugina
{
	class Time
	{
	public:
		static void Initailize();
		static void Update();
		static void Render(HDC hdc);

		static float DeltaTime() { return DeltaTimeValue; }

	private:
		//컴퓨터 cpu의 고유진동수
		static LARGE_INTEGER CpuFrequency;
		//이전 프레잉에 측정한 진동수
		static LARGE_INTEGER PrevFrequency;
		//이전 프레잉에 현재 진동수
		static LARGE_INTEGER CurrentFrequency;

		
		static float DeltaTimeValue;
		static float displayFps;
	};
}

