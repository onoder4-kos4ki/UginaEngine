#pragma once
#include "CommonInclude.h"
#include "uginaComponent.h"
namespace ugina
{
	class GameObject
	{
	public:
		GameObject();
		~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		template <typename T>
		T* AddComponent()
		{
			T* comp = new T();
			comp->Initialize();
			comp->SetOwner(this);

			//������ ���� Ǫ�� ���Լ��� ���� ��ſ� enums Ÿ���� �ε����� ���
			//mComponets.push_back(comp);
			mComponents[(UINT)comp->GetType()] = comp;
			return comp;
		}
		template <typename T>
		T* GetComponent()
		{
			
			T* comp = nullptr;
			for (Component* com : mComponents)
			{
				comp = dynamic_cast<T*>(com);
					if (comp != nullptr)
					{
						return comp;
					}
			}
			return comp;
		}
	
	private: 
		void initializeTransform();
	private:

		std::vector<Component*> mComponents;
		
	};
}


