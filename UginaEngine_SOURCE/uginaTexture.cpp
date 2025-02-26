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

		//텍스쳐를 일단 게임의 메모리에 올리는 함수
		HRESULT Texture::Load(const std::wstring& path)
		{
			//aaaa.png파일이면 .이후부터 끝까지의 문자열을 반환 (즉 png(확장자)를 반환)
			std::wstring ext = path.substr(path.find_last_of(L'.') + 1);
			
			if (ext == L"bmp")
			{
				mType = eTextureType::Bmp;
				//BMP파일 이미지를 로드해서 HBITMAP을 통해서 참조
				mBitmap = (HBITMAP)LoadImageW(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
				
				//null을 반환하는 실패
				if (mBitmap == nullptr)
				{
					return S_FALSE;
				}
				//비트맵 구조체를 통해서 HBITMAP의 내용을 저장
				BITMAP info = {};
			
				GetObject(mBitmap, sizeof(BITMAP), &info);
				
				mWidth = info.bmWidth;
				mHeight = info.bmHeight;

				//현재 게임에 사용되고 있는 메인dc를 가져온다
				HDC maicDc = api.GetHdc();
				//비트맵을 그릴 DC(mhdc)를 메인DC에 호환되는 DC로 맞춘다.
				mHdc = CreateCompatibleDC(maicDc);
				
				//이 비트맵을 그릴 dc의 비트맵을 이미지를 가져온 비트맵으로 바꾼다.
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
