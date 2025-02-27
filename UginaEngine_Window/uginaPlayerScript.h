#pragma once
#include "..\\UginaEngine_SOURCE\\uginaScript.h"
namespace ugina
{
	class PlayerScript :public Script
	{
	public:
		PlayerScript();
		~PlayerScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render(HDC hdc) override;

	private:
	};
}

