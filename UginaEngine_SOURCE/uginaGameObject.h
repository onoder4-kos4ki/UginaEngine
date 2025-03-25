#pragma once
#include "CommonInclude.h"
#include "uginaComponent.h"
namespace ugina
{
	class GameObject
	{
	public:
		enum class eState
		{
			//Ȱ��
			Active,
			//������
			Paused,
			//����
			Dead,
			End
		};

		GameObject();
		~GameObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render(HDC hdc);

		template <typename T>
		T* AddComponent()
		{
			T* component = new T();
			component->Initialize();
			component->SetOwner(this);

			//������ ���� Ǫ�� ���Լ��� ���� ��ſ� enums Ÿ���� �ε����� ���
			//mComponets.push_back(comp);
			mComponents[(UINT)component->GetType()] = component;
			return component;
		}
		template <typename T>
		T* GetComponent()
		{

			T* component = nullptr;
			for (Component* comp : mComponents)
			{
				//mComponents�ȿ� �ִ� ������Ʈ���� �ϳ��ϳ� ĳ�����غ�
				component = dynamic_cast<T*>(comp);
				//ĳ�����Ѱ��� �ߵǼ� component�ȿ� ���� �ݺ��� Ż��
				if (component)
				{
					break;
				}
			}
			return component;
		}
		eState GetActive() { return mState; }
		void SetActive(bool power)
		{
			if (power == true)
			{
				mState = eState::Active;
			}
			if (power == false)
			{
				mState = eState::Paused;
			}
		}
		void Death() { mState = eState::Dead; }                    

	private:
		void initializeTransform();
	private:
		eState mState;
		std::vector<Component*> mComponents;

	};
}


