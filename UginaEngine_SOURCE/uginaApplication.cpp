#include "uginaApplication.h"
#include "uginaInput.h"
#include "uginaTime.h"
#include "uginaSceneManager.h"
namespace ugina
{

	Application::Application() 
		: mhwnd(nullptr)
		, mHdc(nullptr)
		, mWidth(0)
		, mHeight(0)
		, mBackHdc(nullptr)
		, mBackBitmap(nullptr)
	{

	}

	Application::~Application()
	{

	}

	void Application::Initialize(HWND hwnd, UINT width, UINT height)
	{
		adjustWidowRect(hwnd, width, height);
		//HBRUSH backbrush = WHITE_BRUSH;

		mBackBitmap = CreateCompatibleBitmap(mHdc, width, height);

		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBitmap);

		DeleteObject(oldBitmap);

		initializeEtc();

		SceneManager::Initialize();

	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();

	}

	void Application::Update()
	{
		Input::Update();
		Time::Update();
		SceneManager::Update();
	}

	void Application::LateUpdate()
	{
		SceneManager::LateUpdate();
	}

	void Application::Render()
	{


		clearRenderTarget();
		Time::Render(mBackHdc);
		SceneManager::Render(mBackHdc);
		
		copyRenderTarget(mBackHdc, mHdc);

	}

	void Application::clearRenderTarget()
	{
		//ȭ�� �����ֱ�
		Rectangle(mBackHdc, -1, -1, 1601, 901);
	}

	void Application::copyRenderTarget(HDC source, HDC dest)
	{
		//�޸� ����dc���ִ� ������ ����dc�� �ű��
		BitBlt(dest, 0, 0, mWidth, mHeight
			, source, 0, 0, SRCCOPY);
	}

	void Application::adjustWidowRect(HWND hwnd, UINT width, UINT height)
	{
		mhwnd = hwnd;
		mHdc = GetDC(hwnd);
		RECT rect = { 0, 0, width, height };
		//������ ������� �޴������� ������ ũ�⸦ ���������� ���Լ��� �۾������� ũ�⸦ ������
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		SetWindowPos(hwnd, nullptr, 0, 0, mWidth, mHeight, 0);
		ShowWindow(hwnd, true);
	}

	void Application::createBuffer(UINT width, UINT height)
	{
		//������ �ػ󵵿� �´� �����(��ȭ��)����
		mBackBitmap = CreateCompatibleBitmap(mHdc, width, height);
		//����۸� ����ų DC����
		mBackHdc = CreateCompatibleDC(mHdc);

		HBITMAP oldBitmap = (HBITMAP)SelectObject(mBackHdc, mBackBitmap);
		DeleteObject(oldBitmap);
	}

	void Application::initializeEtc()
	{
		Input::Initialize();
		Time::Initailize();
	}
}