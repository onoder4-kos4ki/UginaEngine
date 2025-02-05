#include "Ugi_Application.h"
#include "uginaInput.h"


ugina::Application::Application() : mhwnd(nullptr), mHdc(nullptr), mWidth(0)
, mHeight(0)
, mBackHdc(NULL)
, mBackBitmap(NULL)
{
	
}

ugina::Application::~Application()
{
	
}

void ugina::Application::Initialize(HWND hwnd,UINT width,UINT height)
{
	mhwnd = hwnd;
	mHdc = GetDC(hwnd);

	RECT rect = {0,0,width,height};
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	mPlayer.SetPosition(0, 0);
	Input::Initialize();
}

void ugina::Application::Run()
{
	Update();
	LateUpdate();
	Render();
}

void ugina::Application::Update()
{
	Input::Update();
	mPlayer.Update();
}

void ugina::Application::LateUpdate()
{
}

void ugina::Application::Render()
{
	mPlayer.Render(mHdc);
}

