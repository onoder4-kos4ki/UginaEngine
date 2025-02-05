#pragma once
#include "CommonInclude.h"
#include "uginaGameObject.h"
//에디터 어플리케이션 헤더
namespace ugina
{
	class Application
	{
	public:
		Application();
		~Application();

		void Initialize(HWND hwnd,UINT width, UINT height);
		void Run();

		void Update();
		void LateUpdate();
		void Render();


	private:
		//이 윈도우 핸들
		HWND mhwnd;
		//진짜 화면
		HDC mHdc;

		HDC mBackHdc;
		HBITMAP mBackBitmap;

		UINT mWidth;
		UINT mHeight;

		GameObject mPlayer;
	};

}

