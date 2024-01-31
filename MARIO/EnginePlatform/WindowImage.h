#pragma once
#include <EngineBase\PathObject.h>
#include <EngineBase\EngineMath.h>
#include <EngineBase\Transform.h>
#include <Windows.h>

// ���� : �̹����� ����
enum class EWIndowImageType
{
	IMG_NONE,
	IMG_BMP,
	IMG_PNG
};

class UEngineWindow;

// ���� : �����쿡�� ����ϴ� �̹��� Ŭ����
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
	/// �̹����� �ش��ϴ� BITMAP�� ��� �Լ� 
	/// </summary>
	/// <param name="_Image">�̹���</param>
	/// <returns></returns>
	bool Load(UWindowImage* _Image);

	/// <summary>
	/// �̹����� �������� ��ȯ�ϴ� �Լ�
	/// </summary>
	/// <returns></returns>
	FVector GetScale();

	/// <summary>
	/// �̹����� �����Ͽ� ����ϴ� �Լ�
	/// </summary>
	/// <param name="_CopyImage">����� �̹���</param>
	/// <param name="_Trans">����� ��ġ</param>
	void BitCopy(UWindowImage* _CopyImage, FTransform _Trans);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="_CopyImage">������ �̹���</param>
	/// <param name="_CopyTrans"></param>
	/// <param name="_ImageTrans"></param>
	/// <param name="_Color">��¿��� ������ ����</param>
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
	// �̹��� ������
	HBITMAP hBitMap = 0;
	// �����쿡 �׸��� ����
	HDC ImageDC = 0;
	// �̹����� ����
	BITMAP BitMapInfo = BITMAP();
	// �̹����� Ÿ��
	EWIndowImageType ImageType = EWIndowImageType::IMG_NONE;

	/// <summary>
	/// �̹����� HDC ���� �����ϴ� �Լ�
	/// </summary>
	/// <param name="_MainDC"></param>
	/// <returns></returns>
	bool Create(HDC _MainDC);
};

