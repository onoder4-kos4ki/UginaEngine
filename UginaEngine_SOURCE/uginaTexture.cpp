#include "uginaTexture.h"
#include "uginaApplication.h"
extern ugina::Application api;
namespace ugina
{
	
	namespace graphics
	{

		Texture::Texture()
			:Resource(ugina::enums::eResourceType::Texture)
		{


		}

		Texture::~Texture()
		{
		}

		//�ؽ��ĸ� �ϴ� ������ �޸𸮿� �ø��� �Լ�
		HRESULT Texture::Load(const std::wstring& path)
		{
			//aaaa.png�����̸� .���ĺ��� �������� ���ڿ��� ��ȯ (�� png(Ȯ����)�� ��ȯ)
			std::wstring ext = path.substr(path.find_last_of(L'.') + 1);
			
			if (ext == L"bmp")
			{
				mType = eTextureType::Bmp;
				//BMP���� �̹����� �ε��ؼ� HBITMAP�� ���ؼ� ����
				mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				
				//null�� ��ȯ�ϴ� ����
				if (mBitmap == nullptr)
				{
					return S_FALSE;
				}
				//��Ʈ�� ����ü�� ���ؼ� HBITMAP�� ������ ����
				BITMAP info = {};
			
				GetObject(mBitmap, sizeof(BITMAP), &info);
				
				mWidth = info.bmWidth;
				mHeight = info.bmHeight;

				//���� ���ӿ� ���ǰ� �ִ� ����dc�� �����´�
				HDC maicDc = api.GetHdc();
				//��Ʈ���� �׸� DC(mhdc)�� ����DC�� ȣȯ�Ǵ� DC�� �����.
				mHdc = CreateCompatibleDC(maicDc);
				
				//�� ��Ʈ���� �׸� dc�� ��Ʈ���� �̹����� ������ ��Ʈ������ �ٲ۴�.
				HBITMAP oldBitmap = (HBITMAP)SelectObject(mHdc, mBitmap);
				DeleteObject(oldBitmap);
				
					
			}
			else if (ext == L"png")
			{
				mType = eTextureType::Png;
				mImage = Gdiplus::Image::FromFile(path.c_str());
				if (mImage == nullptr)
				{
					return S_FALSE;
				}
				mWidth=mImage->GetWidth();
				mHeight=mImage->GetHeight();
			}

			return S_FALSE;
		}
	}
}
