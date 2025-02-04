#include "uginaInput.h"

void ugina::uginaInput::Update()
{
	for (int i = 0; i < keyCode::Count; i++)
	{
		
	}
}

void ugina::uginaInput::Initialize()
{
	for (int i = 0; i < keyCode::Count; i++)
	{
		Keys.push_back(Key{ false,keyState::None,static_cast<keyCode>(i)});
	}
	
}
