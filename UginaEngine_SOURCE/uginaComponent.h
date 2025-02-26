#pragma once
#include "uginaEntity.h"
namespace ugina
{	
	class GameObject;
	class Component:public Entity
	{
	public:

		Component(enums::eCompnentType type);
		~Component();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		void SetOwner(GameObject* owner) { mOwner = owner; }
		GameObject* getOwner() { return mOwner; }
		enums::eCompnentType GetType() { return mType; }
	
	private:
		GameObject* mOwner;
		enums::eCompnentType mType;
	};
}


