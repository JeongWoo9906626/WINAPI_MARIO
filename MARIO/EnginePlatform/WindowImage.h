#pragma once
#include <EngineBase\PathObject.h>
#include <EngineBase\EngineMath.h>
#include <EngineBase\Transform.h>
#include <Windows.h>

// 설명 : 이미지의 종류
enum class EWIndowImageType
{
	IMG_NONE,
	IMG_BMP,
	IMG_PNG
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
	/// 이미지의 스케일을 반환하는 함수
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
	/// 
	/// </summary>
	/// <param name="_CopyImage">복사할 이미지</param>
	/// <param name="_CopyTrans"></param>
	/// <param name="_ImageTrans"></param>
	/// <param name="_Color">출력에서 제외할 색상</param>
	void TransCopy(UWindowImage* _CopyImage, const FTransform& _CopyTrans, const FTransform& _ImageTrans, Color8Bit _Color = Color8Bit::Black);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="_Image"></param>
	/// <param name="_Scale"></param>
	/// <returns></returns>
	bool Create(UWindowImage* _Image, const FVector& _Scale);

protected:
	    
private:
	// 이미지 데이터
	HBITMAP hBitMap = 0;
	// 윈도우에 그리는 권한
	HDC ImageDC = 0;
	// 이미지의 정보
	BITMAP BitMapInfo = BITMAP();
	// 이미지의 타입
	EWIndowImageType ImageType = EWIndowImageType::IMG_NONE;

	/// <summary>
	/// 이미지의 HDC 권한 설정하는 함수
	/// </summary>
	/// <param name="_MainDC"></param>
	/// <returns></returns>
	bool Create(HDC _MainDC);
};

