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
		//��ǻ�� cpu�� ����������
		static LARGE_INTEGER CpuFrequency;
		//���� �����׿� ������ ������
		static LARGE_INTEGER PrevFrequency;
		//���� �����׿� ���� ������
		static LARGE_INTEGER CurrentFrequency;

		
		static float DeltaTimeValue;
		static float displayFps;
	};
}

