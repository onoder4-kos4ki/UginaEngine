#include "uginaTime.h"


namespace ugina
{
	//��ǻ�� cpu�� ����������
	LARGE_INTEGER Time::CpuFrequency = {};
	//���� �����׿� ������ ������
	LARGE_INTEGER Time::PrevFrequency = {};
	//���� �����׿� ���� ������
	LARGE_INTEGER Time::CurrentFrequency = {};
	float Time::DeltaTimeValue = 0.0f;
	float Time::displayFps = 0.0f;

	void Time::Initailize()
	{
		//cpu�� ����������(�ʴ� ī��Ʈ��)�� �Ű������� ��ȯ���ִ� �Լ�(cpu�� Ŭ������ �ٸ�)
		QueryPerformanceFrequency(&CpuFrequency);
		//�ý����� ���õ� ���ĺ��� �����ϴ� ī��Ʈ���� ��ȯ(�� ī��Ʈ����QueryPerformanceFrequency�� ��ȯ���ִ� �ʴ� ī��Ʈ���� ���� ������)

		//ó�� �� ī��Ʈ ��
		QueryPerformanceCounter(&PrevFrequency);
	}

	void Time::Update()
	{
		//���Ŀ� �� ���� ī��Ʈ��
		QueryPerformanceCounter(&CurrentFrequency);

		//���� ī��Ʈ �� �� ���� ī��Ʈ ���� �� = ���� �����ӿ��� ���� �����ӱ����� ������(ī��Ʈ ��)
		float differenceFrequency = static_cast<float>(CurrentFrequency.QuadPart - PrevFrequency.QuadPart);
		//���� �����ӿ��� ���� �����ӱ����� ������ ���� �ʴ� �������� ������=���� �����ӿ��� ���� �����ӱ��� �ɸ� �ð�
		DeltaTimeValue = differenceFrequency / static_cast<float>(CpuFrequency.QuadPart);

		//���� �������� ���� ���� �������� ���� �������� ��
		PrevFrequency.QuadPart = CurrentFrequency.QuadPart;
	}

	void Time::Render(HDC hdc)
	{
		//static float time = 0.0f;

		//time += DeltaTime();
		//wchar_t str[50] = L"";

		//float Fps = 1.0f / DeltaTime();
		//
		//swprintf_s(str, L"Fps : %f", displayFps);
		//int len = wcsnlen_s(str, 50);
		//if (time > 1.0)
		//{
		//	//�ʴ� �����Ӽ�
		//	displayFps = Fps;
		//	time = 0.0;
		//}
		//
		//TextOut(hdc, 0, 0, str, len);

		//
		static float time = 0.0f;

		time += DeltaTimeValue;
		float fps = 1.0f / DeltaTimeValue;

		wchar_t str[50] = L"";
		swprintf_s(str, 50, L"Time : %d", (int)fps);
		int len = wcsnlen_s(str, 50);

		TextOut(hdc, 0, 0, str, len);
	}

}
