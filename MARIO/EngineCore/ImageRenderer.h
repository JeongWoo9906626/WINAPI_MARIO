#pragma once
#include <EnginePlatform\WindowImage.h>
#include "SceneComponent.h"

class UWindowImage;

// ���� : ������ ����, �̹��� ��� & ����, �̹��� �����̽� Ŭ����
class UImageRenderer : public USceneComponent
{
public:
	UImageRenderer();
	~UImageRenderer();

	UImageRenderer(const UImageRenderer& _Other) = delete;
	UImageRenderer(UImageRenderer&& _Other) noexcept = delete;
	UImageRenderer& operator=(const UImageRenderer& _Other) = delete;
	UImageRenderer& operator=(UImageRenderer&& _Other) noexcept = delete;

	/// <summary>
	/// ������ ���� ����
	/// </summary>
	/// <param name="_Order">������ ����</param>
	void SetOrder(int _Order) override;

	/// <summary>
	/// �̹��� ���(�׸� �̹���, �׸� ��ġ, �ڸ��� Transform)
	/// �׸� �̹��� = Image
	/// �ڸ��� Transform = ImageCuttingTransform
	/// </summary>
	/// <param name="_DeltaTime"></param>
	void Render(float _DeltaTime);

	// �̹����� �����ϴ� ���Ҹ� �ϰ�
	
	/// <summary>
	/// �̹��� ���� �Լ�
	/// </summary>
	/// <param name="_Name"></param>
	/// <param name="_IsImageScale"></param>
	void SetImage(std::string_view _Name);
	
	/// <summary>
	/// ������Ʈ�� ��ġ, ũ�� ����
	/// </summary>
	/// <param name="_Value">������ ��ġ, ũ��</param>
	void SetTransform(const FTransform& _Value)
	{
		USceneComponent::SetTrasnform(_Value);
	}

	/// <summary>
	/// �̹����� �ڸ� ũ��, ��ġ
	/// </summary>
	/// <param name="_Value">ũ��, ��ġ</param>
	void SetImageCuttingTransform(const FTransform& _Value)
	{
		ImageCuttingTransform = _Value;
	}

protected:
	void BeginPlay() override;
	
private:
	// �׸� �̹���
	UWindowImage* Image;

	// �ڸ� �̹����� ũ��, ��ġ
	FTransform ImageCuttingTransform;
};

