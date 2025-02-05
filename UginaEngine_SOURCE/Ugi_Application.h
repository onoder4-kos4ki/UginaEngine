#pragma once
#include "CommonInclude.h"
#include "uginaGameObject.h"
//������ ���ø����̼� ���
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
		//�� ������ �ڵ�
		HWND mhwnd;
		//��¥ ȭ��
		HDC mHdc;

		HDC mBackHdc;
		HBITMAP mBackBitmap;

		UINT mWidth;
		UINT mHeight;

		GameObject mPlayer;
	};

}

