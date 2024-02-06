#pragma once
#include <EnginePlatform\WindowImage.h>
#include "SceneComponent.h"
#include <map>

// ���� : ������ �̹������� ������ �ִϸ��̼��� ������ �����ϴ� Ŭ����
class UAnimationInfo
{
public:
	UWindowImage* Image = nullptr;
	int Start = -1;
	int End = -1;
	int CurFrame = 0;
	float CurTime = 0.0f;
	bool Loop = false;
	std::vector<float> Times;
	std::vector<int> Indexs;

	/// <summary>
	/// �ִϸ��̼��� ���(����)�� ������Ʈ �ϴ� �Լ� 
	/// </summary>
	/// <param name="_DeltaTime"></param>
	/// <returns></returns>
	int Update(float _DeltaTime);
};



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

	/// <summary>
	/// �̹��� ���� �Լ�
	/// </summary>
	/// <param name="_Name">�̹��� �̸�</param>
	/// <param name="_InfoIndex">�̹��� �ε���</param>
	void SetImage(std::string_view _Name, int _InfoIndex = 0);
	
	/// <summary>
	/// �̹����� �ε��� ���� �Լ�
	/// </summary>
	/// <param name="_InfoIndex">�ε���</param>
	void SetImageIndex(int _InfoIndex)
	{
		InfoIndex = _InfoIndex;
	}

	/// <summary>
	/// ������Ʈ�� ��ġ, ũ�� ����
	/// </summary>
	/// <param name="_Value">������ ��ġ, ũ��</param>
	void SetTransform(const FTransform& _Value)
	{
		USceneComponent::SetTransform(_Value);
	}

	/// <summary>
	/// �̹����� �ڸ� ũ��, ��ġ
	/// </summary>
	/// <param name="_Value">ũ��, ��ġ</param>
	void SetImageCuttingTransform(const FTransform& _Value)
	{
		ImageCuttingTransform = _Value;
	}

	/// <summary>
	/// ���忡 �ִϸ��̼��� �������� ��� ���� ��� ���
	/// �̸��� �ش��ϴ� �̹����� ã�� AnimationInfo�� ���� ���� �� AnimationInfos map�� �����ϴ� �Լ�
	/// </summary>
	/// <param name="_AnimationName">���ϸ��̼� ���� �̸�(Key)</param>
	/// <param name="_ImageName">�̹��� �̸�</param>
	/// <param name="_Start">���� �������� ���ϸ��̼� ����</param>
	/// <param name="_End">���� �������� ���ϸ��̼� ��</param>
	/// <param name="_Inter">���� ���� �ð�</param>
	/// <param name="Loop">�ݺ� ����</param>
	void CreateAnimation(
		std::string_view _AnimationName,
		std::string_view _ImageName,
		int _Start,
		int _End,
		float _Inter,
		bool Loop = true
	);
	
	/// <summary>
	/// ���ϸ��̼� ���� (key�� �ش��ϴ� ���ϸ��̼�����)
	/// </summary>
	/// <param name="_AnimationName">���ϸ��̼� ���� �̸�</param>
	void ChangeAnimation(std::string_view _AnimationName);

	/// <summary>
	/// ���ϸ��̼� �ʱ�ȭ
	/// </summary>
	void AnimationReset();

	/// <summary>
	/// ������ (0 ~ 1)�� (0 ~ 255)�� �����ϴ� �Լ�
	/// </summary>
	/// <param name="_Alpha">����</param>
	void SetAlpha(float _Alpha)
	{
		if (0.0f >= _Alpha)
		{
			_Alpha = 0.0f;
		}

		if (1.0f <= _Alpha)
		{
			_Alpha = 1.0f;
		}

		TransColor.A = static_cast<char>(_Alpha * 255.0f);
	}

	// �̹��� ��ȯ �Լ�
	UWindowImage* GetImage()
	{
		return Image;
		int a = 0;
	}

protected:
	void BeginPlay() override;
	
private:
	// �̹��� �迭�� �ε���
	int InfoIndex = 0;

	// �׸� �̹���
	UWindowImage* Image = nullptr;

	// �ڸ� �̹����� ũ��, ��ġ
	FTransform ImageCuttingTransform;

	// �̹����� ����
	Color8Bit TransColor;

	// ���ϸ��̼� ���� �̸����� ���ϸ��̼� ������ �����ϴ� map
	std::map<std::string, UAnimationInfo> AnimationInfos;
	
	// ���� ���ϸ��̼�
	UAnimationInfo* CurAnimation = nullptr;
};

