#pragma once
#include <EngineBase\PathObject.h>
#include <EngineBase\EngineMath.h>
#include <EngineBase\Transform.h>
#include <Windows.h>

// 설명 : 이미지의 로드 종류
// 한 폴더에 여러 이미지가 들어있는 타입
// 한 이미지 안에 여러 사진이 들어있는 타입
enum class EImageLoadType
{
	IMG_Folder,
	IMG_Cutting,
};

// 설명 : 이미지의 종류
enum class EWIndowImageType
{
	IMG_NONE,
	IMG_BMP,
	IMG_PNG
};

// 설명 : 이미지의 정보를 저장하는 클래스
class UImageInfo
{
public:
	HBITMAP hBitMap;
	HDC ImageDC = nullptr;
	FTransform CuttingTrans;
	EWIndowImageType ImageType = EWIndowImageType::IMG_NONE;
};

class UEngineWindow;

// 설명 : 윈도우에서 사용하는 이미지 클래스
class UWindowImage : public UPathObject
{
	friend UEngineWindow;

public:
	UWindowImage();
	~UWindowImage();

	UWindowImage(const UWindowImage& _Other) = delete;
	UWindowImage(UWindowImage&& _Other) noexcept = delete;
	UWindowImage& operator=(const UWindowImage& _Other) = delete;
	UWindowImage& operator=(UWindowImage&& _Other) noexcept = delete;

	/// <summary>
	/// 이미지에 해당하는 BITMAP을 얻는 함수 
	/// </summary>
	/// <param name="_Image">이미지</param>
	/// <returns></returns>
	bool Load(UWindowImage* _Image);

	/// <summary>
	/// 폴더에 있는 여러 이미지를 불러오는 함수
	/// </summary>
	/// <param name="_Image">이미지 이름</param>
	/// <returns></returns>
	bool LoadFolder(UWindowImage* _Image);

	/// <summary>
	/// 이미지의 크기를 반환하는 함수
	/// </summary>
	/// <returns></returns>
	FVector GetScale();

	/// <summary>
	/// 이미지를 복사하여 출력하는 함수
	/// </summary>
	/// <param name="_CopyImage">출력할 이미지</param>
	/// <param name="_Trans">출력할 위치</param>
	void BitCopy(UWindowImage* _CopyImage, FTransform _Trans);

	/// <summary>
	/// 출력할 위치를 지정하고 해당 위치에 이미지의 크기를 잘라서 출력하는 함수
	/// </summary>
	/// <param name="_CopyImage">출력할 이미지</param>
	/// <param name="_CopyTrans">출력할 이미지의 위치</param>
	/// <param name="_ImageTrans">출력할 부분의 위치</param>
	/// <param name="_Color">출력에서 제외할 색상</param>
	void TransCopy(UWindowImage* _CopyImage, const FTransform& _CopyTrans, int _Index, Color8Bit _Color = Color8Bit::Black);

	/// <summary>
	/// 출력할 위치를 지정하고 해당 위치에 이미지의 투명도를 출력하는 함수 
	/// </summary>
	/// <param name="_CopyImage"></param>
	/// <param name="_Trans"></param>
	/// <param name="_Index"></param>
	/// <param name="_Color"></param>
	void AlphaCopy(UWindowImage* _CopyImage, const FTransform& _Trans, int _Index, Color8Bit _Color = Color8Bit::Black);

	/// <summary>
	/// 이미지를 지정한 크기로 생성
	/// </summary>
	/// <param name="_Image">이미지</param>
	/// <param name="_Scale">크기</param>
	/// <returns></returns>
	bool Create(UWindowImage* _Image, const FVector& _Scale);

	/// <summary>
	/// 한 이미지에 사진이 여러개 있을 때 자르는 함수
	/// </summary>
	/// <param name="_X">X의 개수</param>
	/// <param name="_Y">Y의 개수</param>
	void Cutting(int _X, int _Y);

	/// <summary>
	/// X, Y 위치에 해당하는 색상 반환
	/// </summary>
	/// <param name="_X">X 위치</param>
	/// <param name="_Y">Y 위치</param>
	/// <returns></returns>
	Color8Bit GetColor(int _X, int _Y, Color8Bit _DefaultColor);

	/// <summary>
	/// 이미지 타입 반환(BMP, PNG)
	/// </summary>
	/// <returns></returns>
	EWIndowImageType GetImageType()
	{
		return ImageType;
	}

protected:
	    
private:
	// 이미지의 메모리적 권한 (이미지 데이터)
	HBITMAP hBitMap = 0;
	// 윈도우에 그리는 권한
	HDC ImageDC = 0;
	// 이미지의 정보
	BITMAP BitMapInfo = BITMAP();
	// 이미지의 타입
	EWIndowImageType ImageType = EWIndowImageType::IMG_NONE;
	// 이미지 로드 타입
	EImageLoadType LoadType = EImageLoadType::IMG_Cutting;

	// 이미지 정보들을 저장하는 vector
	std::vector<UImageInfo> Infos;

	/// <summary>
	/// 이미지의 HDC 설정하는 함수
	/// </summary>
	/// <param name="_MainDC">HDC</param>
	/// <returns></returns>
	bool Create(HDC _MainDC);
};

