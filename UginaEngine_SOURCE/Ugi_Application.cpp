#include "Ugi_Application.h"



ugina::Application::Application() : mhwnd(nullptr), mHdc(nullptr) 
{

}

ugina::Application::~Application()
{
}

void ugina::Application::Initialize(HWND hwnd)
{
	mhwnd = hwnd;
	mHdc = GetDC(hwnd);
}

void ugina::Application::Run()
{
	Update();
	LateUpdate();
	Render();
}

void ugina::Application::Update()
{
	mPlayer.Update();
}

void ugina::Application::LateUpdate()
{
}

void ugina::Application::Render()
{
	mPlayer.Render(mHdc);
}

