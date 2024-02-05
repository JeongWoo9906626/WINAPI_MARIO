#include "WindowImage.h"

#include <Windows.h>
#include <objidl.h>
#include <gdiplus.h>

#include <EngineBase\EngineDebug.h>
#include <EngineBase\EngineString.h>
#include <EngineBase\EngineDirectory.h>
#include <EngineBase\EngineFile.h>

#pragma comment(lib, "Msimg32.lib")
#pragma comment(lib, "Gdiplus.lib")

UWindowImage::UWindowImage()
{
}

UWindowImage::~UWindowImage()
{
	switch (LoadType)
	{
	case EImageLoadType::IMG_Folder:
	{
		for (size_t i = 0; i < Infos.size(); i++)
		{
			DeleteObject(Infos[i].hBitMap);
			DeleteDC(Infos[i].ImageDC);
		}
		break;
	}
	case EImageLoadType::IMG_Cutting:
		DeleteObject(hBitMap);
		DeleteDC(ImageDC);
		break;
	default:
		break;
	}
}

bool UWindowImage::LoadFolder(UWindowImage* _Image)
{
	LoadType = EImageLoadType::IMG_Folder;

	UEnginePath EnginePath = GetEnginePath();
	if (false == EnginePath.IsDirectory())
	{
		MsgBoxAssert("디렉토리가 아닌 경로로 폴더로드를 하려고 했습니다");
	}
	
	UEngineDirectory Dir = EnginePath;

	std::list<UEngineFile> NewList = Dir.AllFile({ ".png", ".bmp" }, false);
	Infos.reserve(NewList.size());

	for (UEngineFile& File : NewList)
	{
		UEnginePath Path = File;

		std::string UpperExt = UEngineString::ToUpper(Path.GetExtension());

		if (".BMP" == UpperExt)
		{
			HANDLE ImageHandle = LoadImageA(nullptr, Path.GetFullPath().c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			hBitMap = reinterpret_cast<HBITMAP>(ImageHandle);
			ImageType = EWIndowImageType::IMG_BMP;
		}
		else if (".PNG" == UpperExt)
		{
			ULONG_PTR gdiplusToken = 0;
			Gdiplus::GdiplusStartupInput gdistartupinput;
			Gdiplus::GdiplusStartup(&gdiplusToken, &gdistartupinput, nullptr);
			std::wstring wPath = UEngineString::AnsiToUniCode(Path.GetFullPath());
			Gdiplus::Image* pImage = Gdiplus::Image::FromFile(wPath.c_str());
			Gdiplus::Bitmap* pBitMap = reinterpret_cast<Gdiplus::Bitmap*>(pImage->Clone());
			Gdiplus::Status stat = pBitMap->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &hBitMap);
			if (Gdiplus::Status::Ok != stat)
			{
				MsgBoxAssert("Png 형식 리소스 로드에 실패했습니다.");
			}

			ImageType = EWIndowImageType::IMG_PNG;
		}
		ImageDC = CreateCompatibleDC(_Image->ImageDC);

		if (nullptr == ImageDC)
		{
			MsgBoxAssert("이미지 생성에 실패했습니다");
			return false;
		}

		HBITMAP OldBitMap = reinterpret_cast<HBITMAP>(SelectObject(ImageDC, hBitMap));
		DeleteObject(OldBitMap);
		GetObject(hBitMap, sizeof(BITMAP), &BitMapInfo);

		ImageInfo Info;
		Info.hBitMap = hBitMap;
		Info.ImageDC = ImageDC;
		Info.CuttingTrans.SetPosition({ 0, 0 });
		Info.CuttingTrans.SetScale(GetScale());
		Infos.push_back(Info);
	}

	return true;
}

FVector UWindowImage::GetScale()
{
	// 이미지 데이터의 정보에서 크기 반환
	return FVector(BitMapInfo.bmWidth, BitMapInfo.bmHeight);
}

bool UWindowImage::Create(HDC _MainDC)
{
	ImageDC = _MainDC;

	if (nullptr == ImageDC)
	{
		return false;
	}

	return true;
}

bool UWindowImage::Load(UWindowImage* _Image)
{
	LoadType = EImageLoadType::IMG_Cutting;

	UEnginePath Path = GetEnginePath();

	std::string UpperExt = UEngineString::ToUpper(Path.GetExtension());
	
	// 이미지의 확장자가 BMP인 경우
	if (".BMP" == UpperExt)
	{
		HANDLE ImageHandle = LoadImageA(nullptr, Path.GetFullPath().c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		hBitMap = reinterpret_cast<HBITMAP>(ImageHandle);
		ImageType = EWIndowImageType::IMG_BMP;
	}
	// 이미지의 확장자가 PNG인 경우
	else if (".PNG" == UpperExt)
	{
		ULONG_PTR gdiplusToken = 0;
		Gdiplus::GdiplusStartupInput gdistartupinput;
		Gdiplus::GdiplusStartup(&gdiplusToken, &gdistartupinput, nullptr);
	
		std::wstring wPath = UEngineString::AnsiToUniCode(Path.GetFullPath());
	
		Gdiplus::Image* pImage = Gdiplus::Image::FromFile(wPath.c_str());
		Gdiplus::Bitmap* pBitMap = reinterpret_cast<Gdiplus::Bitmap*>(pImage->Clone());
		
		Gdiplus::Status stat = pBitMap->GetHBITMAP(Gdiplus::Color(0, 0, 0, 0), &hBitMap);
	
		if (Gdiplus::Status::Ok != stat)
		{
			MsgBoxAssert("Png 형식 리소스 로드에 실패했습니다.");
		}

		ImageType = EWIndowImageType::IMG_PNG;
	}

	ImageDC = CreateCompatibleDC(_Image->ImageDC);
	if (nullptr == ImageDC)
	{
		MsgBoxAssert("이미지 생성에 실패했습니다");
		return false;
	}
	
	HBITMAP OldBitMap = reinterpret_cast<HBITMAP>(SelectObject(ImageDC, hBitMap));
	DeleteObject(OldBitMap);

	// 그릴 이미지의 정보(HBITMAP)를 BITMAP에 저장
	GetObject(hBitMap, sizeof(BITMAP), &BitMapInfo);

	ImageInfo Info;
	Info.hBitMap = hBitMap;
	Info.ImageDC = ImageDC;
	Info.CuttingTrans.SetPosition({ 0,0 });
	Info.CuttingTrans.SetScale(GetScale());
	Info.ImageType = ImageType;
	Infos.push_back(Info);

	return true;
}

bool UWindowImage::Create(UWindowImage* _Image, const FVector& _Scale)
{
	// BITMAP생성(입력한 크기의 사이즈로)
	// -> 1x1의 HANDLE생성(색상 X = 검정색)
	HANDLE ImageHandle = CreateCompatibleBitmap(_Image->ImageDC, _Scale.iX(), _Scale.iY());

	if (nullptr == ImageHandle)
	{
		MsgBoxAssert("이미지 생성에 실패했습니다");
		return false;
	}

	hBitMap = reinterpret_cast<HBITMAP>(ImageHandle);
	ImageDC = CreateCompatibleDC(_Image->ImageDC);

	if (nullptr == ImageDC)
	{
		MsgBoxAssert("이미지 생성에 실패했습니다");
		return false;
	}

	HBITMAP OldBitMap = reinterpret_cast<HBITMAP>(SelectObject(ImageDC, hBitMap));
	DeleteObject(OldBitMap);

	// 그릴 이미지의 정보(HBITMAP)를 BITMAP에 저장
	GetObject(hBitMap, sizeof(BITMAP), &BitMapInfo);

	return true;
}

void UWindowImage::Cutting(int _X, int _Y)
{
	Infos.clear();

	// 이미지 1개의 x, y 크기
	FVector CuttingScale = { GetScale().X / _X, GetScale().Y / _Y };
	// 자르기 시작할 위치
	FVector CuttingPos = { 0,0 };

	for (int i = 0; i < _Y; i++)
	{
		for (int i = 0; i < _X; i++)
		{
			ImageInfo Info;
			Info.ImageDC = ImageDC;
			Info.CuttingTrans.SetPosition(CuttingPos);
			Info.CuttingTrans.SetScale(CuttingScale);
			Infos.push_back(Info);

			CuttingPos.X += CuttingScale.X;
		}

		CuttingPos.X = 0.0f;
		CuttingPos.Y += CuttingScale.Y;
	}
}

void UWindowImage::BitCopy(UWindowImage* _CopyImage, FTransform _Trans)
{
	if (nullptr == _CopyImage)
	{
		MsgBoxAssert("nullptr 인 이미지를 복사할 수 없습니다");
	}

	// 윈도우 HDC
	HDC hdc = ImageDC;
	// 이미지 HDC
	HDC hdcSrc = _CopyImage->ImageDC;

	BitBlt(
		hdc,
		_Trans.iLeft(),
		_Trans.iTop(),
		_Trans.GetScale().iX(),
		_Trans.GetScale().iY(),
		hdcSrc,
		0,
		0,
		SRCCOPY
	);
}

void UWindowImage::TransCopy(UWindowImage* _CopyImage, const FTransform& _Trans, int _Index, Color8Bit _Color)
{
	if (nullptr == _CopyImage)
	{
		MsgBoxAssert("nullptr 인 이미지를 복사할 수 없습니다");
	}

	if (_Index >= _CopyImage->Infos.size())
	{
		MsgBoxAssert(GetName() + "이미지 정보의 인덱스를 오버하여 사용했습니다");
	}

	FTransform& ImageTrans = _CopyImage->Infos[_Index].CuttingTrans;

	// 그릴 위치 설정
	int RenderLeft = _Trans.iLeft();
	int RenderTop = _Trans.iTop();
	// 그릴 크기 설정
	int RenderScaleX = _Trans.GetScale().iX();
	int RenderScaleY = _Trans.GetScale().iY();

	// 그려질 이미지의 위치
	int ImageLeft = ImageTrans.GetPosition().iX();
	int ImageTop = ImageTrans.GetPosition().iY();
	// 그려질 이미지의 크기
	int ImageScaleX = ImageTrans.GetScale().iX();
	int ImageScaleY = ImageTrans.GetScale().iY();

	HDC hdc = ImageDC;
	HDC hdcSrc = _CopyImage->ImageDC;
	TransparentBlt(
		hdc,			// 윈도우에 그리는 권한
		RenderLeft,		// 그릴 X위치
		RenderTop,		// 그릴 Y위치
		RenderScaleX,	// 그릴 X크기
		RenderScaleY,	// 그릴 Y크기
		hdcSrc,			// 그릴 이미지
		ImageLeft,		// 출력할 이미지를 자를 X위치
		ImageTop,		// 출력할 이미지를 자를 Y위치
		ImageScaleX,	// 출력할 이미지의 X크기
		ImageScaleY,	// 출력할 이미지의 Y크기
		_Color.Color	// 출력에서 제외할 색상
	);
}

void UWindowImage::AlphaCopy(UWindowImage* _CopyImage, const FTransform& _Trans, int _Index, Color8Bit _Color)
{
	if (nullptr == _CopyImage)
	{
		MsgBoxAssert("nullptr 인 이미지를 복사할 수 없습니다");
	}

	if (_Index >= _CopyImage->Infos.size())
	{
		MsgBoxAssert(GetName() + "이미지 정보의 인덱스를 오버하여 사용했습니다");
	}


	FTransform& ImageTrans = _CopyImage->Infos[_Index].CuttingTrans;

	int RenderLeft = _Trans.iLeft();
	int RenderTop = _Trans.iTop();
	int RenderScaleX = _Trans.GetScale().iX();
	int RenderScaleY = _Trans.GetScale().iY();

	int ImageLeft = ImageTrans.GetPosition().iX();
	int ImageTop = ImageTrans.GetPosition().iY();
	int ImageScaleX = ImageTrans.GetScale().iX();
	int ImageScaleY = ImageTrans.GetScale().iY();


	HDC hdc = ImageDC;
	HDC hdcSrc = _CopyImage->Infos[_Index].ImageDC;

	BLENDFUNCTION Function;
	Function.BlendOp = AC_SRC_OVER;
	Function.BlendFlags = 0;
	Function.SourceConstantAlpha = _Color.A;
	Function.AlphaFormat = AC_SRC_ALPHA;

	AlphaBlend(
		hdc, 			// 윈도우에 그리는 권한
		RenderLeft, 	// 그릴 X위치
		RenderTop, 		// 그릴 Y위치
		RenderScaleX,	// 그릴 X크기
		RenderScaleY,	// 그릴 Y크기
		hdcSrc,			// 그릴 이미지
		ImageLeft,   	// 출력할 이미지를 자를 X위치 
		ImageTop,   	// 출력할 이미지를 자를 Y위치  
		ImageScaleX, 	// 출력할 이미지의 X크기 
		ImageScaleY, 	// 출력할 이미지의 Y크기 
		Function		// 출력에서 제외할 함수
	);
}

Color8Bit UWindowImage::GetColor(int _X, int _Y)
{
	Color8Bit Color;

	Color.Color = ::GetPixel(ImageDC, _X, _Y);

	return Color;
}