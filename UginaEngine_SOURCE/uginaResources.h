#pragma once
#include "uginaResource.h"
namespace ugina
{
	class Resources
	{
	public:
		template<typename T>
		static T* Find(const std::wstring& key)
		{
			//auto = std::map<std::wstring, Resource*>::iterator
			auto iter = mResources.find(key);
			if (iter == mResources.end())
			{
				return nullptr;
			}

			return dynamic_cast<T*>(iter->second);

		}

		template<typename T>
		static T* Load(const std::wstring& key, const std::wstring& path)
		{
			//���ҽ��� �ε��ϱ����� �ϴ� ���� �̸��� ���ҽ��� �ִ��� ã�ƺ�
			T* resource = Resources::Find<T>(key);
			//�����Ѵٸ� �ε����ʿ䰡 ������ �ٷ� �� ���ҽ��� ����
			if (resource != nullptr)
			{
				return resource;
			}
			//���ٸ� ���ο� ���ҽ��� ����
			resource = new T();
			// �� ���ҽ� ��ü�� ������ �ִ� �ε��Լ��� ������Ѽ� ���ҽ��� �ε��Ŵ
			if (FAILED(resource->Load(path)))
			{
				assert(false);
			}
			//�ε�� ���ҼҴ� mResources �ʿ� ����
			resource->SetName(key);
			resource->SetPath(path);
			mResources.insert(std::make_pair(key, resource));
			

			return resource;
		}

		static void Insert(const std::wstring& key, Resource* resource)
		{
			if (key == L"")
			{
				return;
			}
			if (resource == nullptr)
			{
				return;
			}
			mResources.insert(std::make_pair(key, resource));
		}
		static void Release()
		{
			//auto = std::pair<const std::wstring,Resource*> map�� ù��° ���� ���������� const�� ��
			for (auto& iter : mResources)
			{
				delete iter.second;
				iter.second = nullptr;
			}
		}
	private:

		//���� ���ο��� ����� �̸��� Ű(ex BG,Player), value�� �ȿ� �� ���ҽ���ü�� ������
		static std::map<std::wstring, Resource*> mResources;
	};
}

