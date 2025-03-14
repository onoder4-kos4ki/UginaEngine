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
			T* resource = Resources::Find<T>(key);
			if (resource != nullptr)
			{
				return resource;
			}
			resource = new T();
			if (FAILED(resource->Load(path)))
			{
				assert(false);
			}
			mResources.insert(std::make_pair(key, resource));
			resource->SetName(key);
			resource->SetPath(path);

			return resource;
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

