#pragma once
#include "uginaEntity.h"
namespace ugina
{
	class Resource abstract : public Entity
	{
	public :
		Resource(enums::eResourceType type);
		virtual ~Resource();

		//HRESULT�� bool�� ����
		//���������Լ� �����޸� �Ҵ��� �Ұ��������� �����̴�.(����ؼ� ���)
		virtual HRESULT Load(const std::wstring& path) = 0;

		const std::wstring& GetPath() { return mPath; }
		void SetPath(const std::wstring& path) { mPath = path; }
	private:
		//���� ���ҽ��� Ÿ���� ���� �����,�ؽ��Ŀ� ����
		const enums::eResourceType mType;
		//���ҽ� ������ ��θ� ����
		std::wstring mPath;
	};
}
