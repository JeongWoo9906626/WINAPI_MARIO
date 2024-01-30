#pragma once
#include <EnginePlatform\WindowImage.h>
#include "SceneComponent.h"

class UImageRenderer : public USceneComponent
{
public:
	UImageRenderer();
	~UImageRenderer();

	UImageRenderer(const UImageRenderer& _Other) = delete;
	UImageRenderer(UImageRenderer&& _Other) noexcept = delete;
	UImageRenderer& operator=(const UImageRenderer& _Other) = delete;
	UImageRenderer& operator=(UImageRenderer&& _Other) noexcept = delete;

	void SetOrder(int _Order) override;
	void Render(float _DeltaTime);

	// �̹����� �����ϴ� ���Ҹ� �ϰ�
	void SetImage(std::string_view _Name, bool _IsImageScale = false);
	// �̹����� �����ϸ鼭 �̹����� ũ��� �������� �������� �����ϴ°͵� �Բ��ϴ� �Լ�
	void SetImageToScale(std::string_view _Name);

protected:
	void BeginPlay() override;
	
private:
	UWindowImage* Image;
};

