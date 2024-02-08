#pragma once
#include <EngineBase\PathObject.h>
#include <EngineBase\EngineMath.h>
#include <EngineBase\Transform.h>
#include <Windows.h>

// ���� : �̹����� �ε� ����
// �� ������ ���� �̹����� ����ִ� Ÿ��
// �� �̹��� �ȿ� ���� ������ ����ִ� Ÿ��
enum class EImageLoadType
{
	IMG_Folder,
	IMG_Cutting,
};

// ���� : �̹����� ����
enum class EWIndowImageType
{
	IMG_NONE,
	IMG_BMP,
	IMG_PNG
};

// ���� : �̹����� ������ �����ϴ� Ŭ����
class UImageInfo
{
public:
	HBITMAP hBitMap;
	HDC ImageDC = nullptr;
	FTransform CuttingTrans;
	EWIndowImageType ImageType = EWIndowImageType::IMG_NONE;
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
	/// ������ �ִ� ���� �̹����� �ҷ����� �Լ�
	/// </summary>
	/// <param name="_Image">�̹��� �̸�</param>
	/// <returns></returns>
	bool LoadFolder(UWindowImage* _Image);

	/// <summary>
	/// �̹����� ũ�⸦ ��ȯ�ϴ� �Լ�
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
	/// ����� ��ġ�� �����ϰ� �ش� ��ġ�� �̹����� ũ�⸦ �߶� ����ϴ� �Լ�
	/// </summary>
	/// <param name="_CopyImage">����� �̹���</param>
	/// <param name="_CopyTrans">����� �̹����� ��ġ</param>
	/// <param name="_ImageTrans">����� �κ��� ��ġ</param>
	/// <param name="_Color">��¿��� ������ ����</param>
	void TransCopy(UWindowImage* _CopyImage, const FTransform& _CopyTrans, int _Index, Color8Bit _Color = Color8Bit::Black);

	/// <summary>
	/// ����� ��ġ�� �����ϰ� �ش� ��ġ�� �̹����� ������ ����ϴ� �Լ� 
	/// </summary>
	/// <param name="_CopyImage"></param>
	/// <param name="_Trans"></param>
	/// <param name="_Index"></param>
	/// <param name="_Color"></param>
	void AlphaCopy(UWindowImage* _CopyImage, const FTransform& _Trans, int _Index, Color8Bit _Color = Color8Bit::Black);

	/// <summary>
	/// �̹����� ������ ũ��� ����
	/// </summary>
	/// <param name="_Image">�̹���</param>
	/// <param name="_Scale">ũ��</param>
	/// <returns></returns>
	bool Create(UWindowImage* _Image, const FVector& _Scale);

	/// <summary>
	/// �� �̹����� ������ ������ ���� �� �ڸ��� �Լ�
	/// </summary>
	/// <param name="_X">X�� ����</param>
	/// <param name="_Y">Y�� ����</param>
	void Cutting(int _X, int _Y);

	/// <summary>
	/// X, Y ��ġ�� �ش��ϴ� ���� ��ȯ
	/// </summary>
	/// <param name="_X">X ��ġ</param>
	/// <param name="_Y">Y ��ġ</param>
	/// <returns></returns>
	Color8Bit GetColor(int _X, int _Y, Color8Bit _DefaultColor);

	/// <summary>
	/// �̹��� Ÿ�� ��ȯ(BMP, PNG)
	/// </summary>
	/// <returns></returns>
	EWIndowImageType GetImageType()
	{
		return ImageType;
	}

protected:
	    
private:
	// �̹����� �޸��� ���� (�̹��� ������)
	HBITMAP hBitMap = 0;
	// �����쿡 �׸��� ����
	HDC ImageDC = 0;
	// �̹����� ����
	BITMAP BitMapInfo = BITMAP();
	// �̹����� Ÿ��
	EWIndowImageType ImageType = EWIndowImageType::IMG_NONE;
	// �̹��� �ε� Ÿ��
	EImageLoadType LoadType = EImageLoadType::IMG_Cutting;

	// �̹��� �������� �����ϴ� vector
	std::vector<UImageInfo> Infos;

	/// <summary>
	/// �̹����� HDC �����ϴ� �Լ�
	/// </summary>
	/// <param name="_MainDC">HDC</param>
	/// <returns></returns>
	bool Create(HDC _MainDC);
};

