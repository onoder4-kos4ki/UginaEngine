#include "Ugi_Application.h"
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
		//화면 지워주기
		Rectangle(mBackHdc, -1, -1, 1601, 901);
	}

	void Application::copyRenderTarget(HDC source, HDC dest)
	{
		//메모리 버퍼dc에있는 내용을 현재dc로 옮기기
		BitBlt(dest, 0, 0, mWidth, mHeight
			, source, 0, 0, SRCCOPY);
	}

	void Application::adjustWidowRect(HWND hwnd, UINT width, UINT height)
	{
		mhwnd = hwnd;
		mHdc = GetDC(hwnd);
		RECT rect = { 0, 0, width, height };
		//원래의 윈도우는 메뉴영역을 포함한 크기를 조정했지만 이함수는 작업영역의 크기를 조정함
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		mWidth = rect.right - rect.left;
		mHeight = rect.bottom - rect.top;

		SetWindowPos(hwnd, nullptr, 0, 0, mWidth, mHeight, 0);
		ShowWindow(hwnd, true);
	}

	void Application::createBuffer(UINT width, UINT height)
	{
		//윈도우 해상도에 맞는 백버퍼(도화지)생성
		mBackBitmap = CreateCompatibleBitmap(mHdc, width, height);
		//백버퍼를 가르킬 DC생성
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