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

		HDC GetHdc() { return mHdc; }             
		UINT GetWidth() { return mWidth; }
		UINT Getheight() { return mHeight; }
	private:
		void clearRenderTarget();
		void copyRenderTarget(HDC source, HDC dest);
		void adjustWidowRect(HWND hwnd, UINT width, UINT height);
		void createBuffer(UINT width, UINT height);
		void initializeEtc();
	private:
		//�� ������ �ڵ�
		HWND mhwnd;
		//��¥ ȭ��
		HDC mHdc;

		//ȭ����� 
		HDC mBackHdc;
		HBITMAP mBackBitmap;

		UINT mWidth;
		UINT mHeight;

		
	};

}

