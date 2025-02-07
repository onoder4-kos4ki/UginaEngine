#include "Ugi_Application.h"
#include "uginaInput.h"


ugina::Application::Application() : mhwnd(nullptr), mHdc(nullptr), mWidth(0)
, mHeight(0)
, mBackHdc(nullptr)
, mBackBitmap(nullptr)
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
	mWidth = rect.right-rect.left;
	mHeight = rect.bottom- rect.top;

	SetWindowPos(mhwnd, nullptr, 0, 0, mWidth, mHeight, 0);
	ShowWindow(mhwnd, true);
	

	//HBRUSH backbrush = WHITE_BRUSH;
	
	mBackBitmap = CreateCompatibleBitmap(mHdc, width, height);

	mBackHdc = CreateCompatibleDC(mHdc);

	HBITMAP oldBitmap=(HBITMAP)SelectObject(mBackHdc, mBackBitmap);
	
	DeleteObject(oldBitmap);
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
	//mPlayer.Render(mBackHdc);
	Rectangle(mBackHdc, 0, 0, 1600, 900);
	//메모리 버퍼dc에있는 내용을 현재dc로 옮기기
	BitBlt(mHdc, 0, 0, mWidth, mHeight, mBackHdc, 0, 0, SRCCOPY);
}

