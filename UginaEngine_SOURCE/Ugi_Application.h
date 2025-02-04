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

		void Initialize(HWND hwnd);
		void Run();

		void Update();
		void LateUpdate();
		void Render();


	private:
		HWND mhwnd;
		HDC mHdc;

		GameObject mPlayer;
	};

}

