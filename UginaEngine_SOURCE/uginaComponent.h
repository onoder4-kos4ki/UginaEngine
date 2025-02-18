#pragma once
#include "uginaEntity.h"
namespace ugina
{	
	class GameObject;
	class Component:public Entity
	{
	public:

		Component();
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		void SetOwner(GameObject* owner) { mOwner = owner; }
		GameObject* getOwner() { return mOwner; }
	
	private:
		GameObject* mOwner;
	};
}


