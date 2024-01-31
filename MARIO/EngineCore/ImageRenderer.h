#pragma once
#include <EnginePlatform\WindowImage.h>
#include "SceneComponent.h"

class UWindowImage;

// 설명 : 랜더링 순서, 이미지 출력 & 설정, 이미지 슬라이싱 클래스
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
	/// 랜더링 순서 설정
	/// </summary>
	/// <param name="_Order">랜더링 순서</param>
	void SetOrder(int _Order) override;

	/// <summary>
	/// 이미지 출력(그릴 이미지, 그릴 위치, 자르는 Transform)
	/// 그릴 이미지 = Image
	/// 자르는 Transform = ImageCuttingTransform
	/// </summary>
	/// <param name="_DeltaTime"></param>
	void Render(float _DeltaTime);

	// 이미지를 세팅하는 역할만 하고
	
	/// <summary>
	/// 이미지 설정 함수
	/// </summary>
	/// <param name="_Name"></param>
	/// <param name="_IsImageScale"></param>
	void SetImage(std::string_view _Name);
	
	/// <summary>
	/// 컴포넌트의 위치, 크기 설정
	/// </summary>
	/// <param name="_Value">설정할 위치, 크기</param>
	void SetTransform(const FTransform& _Value)
	{
		USceneComponent::SetTrasnform(_Value);
	}

	/// <summary>
	/// 이미지의 자를 크기, 위치
	/// </summary>
	/// <param name="_Value">크기, 위치</param>
	void SetImageCuttingTransform(const FTransform& _Value)
	{
		ImageCuttingTransform = _Value;
	}

protected:
	void BeginPlay() override;
	
private:
	// 그릴 이미지
	UWindowImage* Image;

	// 자를 이미지의 크기, 위치
	FTransform ImageCuttingTransform;
};

