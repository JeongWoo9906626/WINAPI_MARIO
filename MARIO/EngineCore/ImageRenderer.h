#pragma once
#include <EnginePlatform\WindowImage.h>
#include "SceneComponent.h"
#include <map>

// 설명 : 한장의 이미지에서 나오는 애니메이션의 정보를 저장하는 클래스
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
	/// 애니메이션의 출력(순서)를 업데이트 하는 함수 
	/// </summary>
	/// <param name="_DeltaTime"></param>
	/// <returns></returns>
	int Update(float _DeltaTime);
};



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

	/// <summary>
	/// 이미지 설정 함수
	/// </summary>
	/// <param name="_Name">이미지 이름</param>
	/// <param name="_InfoIndex">이미지 인덱스</param>
	void SetImage(std::string_view _Name, int _InfoIndex = 0);
	
	/// <summary>
	/// 이미지의 인덱스 설정 함수
	/// </summary>
	/// <param name="_InfoIndex">인덱스</param>
	void SetImageIndex(int _InfoIndex)
	{
		InfoIndex = _InfoIndex;
	}

	/// <summary>
	/// 컴포넌트의 위치, 크기 설정
	/// </summary>
	/// <param name="_Value">설정할 위치, 크기</param>
	void SetTransform(const FTransform& _Value)
	{
		USceneComponent::SetTransform(_Value);
	}

	/// <summary>
	/// 이미지의 자를 크기, 위치
	/// </summary>
	/// <param name="_Value">크기, 위치</param>
	void SetImageCuttingTransform(const FTransform& _Value)
	{
		ImageCuttingTransform = _Value;
	}

	/// <summary>
	/// 한장에 애니메이션의 사진들이 담겨 있을 경우 사용
	/// 이름에 해당하는 이미지를 찾고 AnimationInfo의 값을 세팅 후 AnimationInfos map에 저장하는 함수
	/// </summary>
	/// <param name="_AnimationName">에니메이션 동작 이름(Key)</param>
	/// <param name="_ImageName">이미지 이름</param>
	/// <param name="_Start">사진 순서에서 에니메이션 시작</param>
	/// <param name="_End">사진 순서에서 에니메이션 끝</param>
	/// <param name="_Inter">사진 유지 시간</param>
	/// <param name="Loop">반복 여부</param>
	void CreateAnimation(
		std::string_view _AnimationName,
		std::string_view _ImageName,
		int _Start,
		int _End,
		float _Inter,
		bool Loop = true
	);
	
	/// <summary>
	/// 에니메이션 변경 (key에 해당하는 에니메이션으로)
	/// </summary>
	/// <param name="_AnimationName">에니메이션 동작 이름</param>
	void ChangeAnimation(std::string_view _AnimationName);

	/// <summary>
	/// 에니메이션 초기화
	/// </summary>
	void AnimationReset();

	/// <summary>
	/// 투명도를 (0 ~ 1)를 (0 ~ 255)로 변경하는 함수
	/// </summary>
	/// <param name="_Alpha">투명도</param>
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

	// 이미지 반환 함수
	UWindowImage* GetImage()
	{
		return Image;
		int a = 0;
	}

protected:
	void BeginPlay() override;
	
private:
	// 이미지 배열의 인덱스
	int InfoIndex = 0;

	// 그릴 이미지
	UWindowImage* Image = nullptr;

	// 자를 이미지의 크기, 위치
	FTransform ImageCuttingTransform;

	// 이미지의 색상
	Color8Bit TransColor;

	// 에니메이션 동작 이름으로 에니메이션 정보를 저장하는 map
	std::map<std::string, UAnimationInfo> AnimationInfos;
	
	// 현재 에니메이션
	UAnimationInfo* CurAnimation = nullptr;
};

