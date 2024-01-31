#pragma once
#include <EngineBase/Transform.h>
#include "ActorComponent.h"

// 설명 : 위치를 나타내는 클래스
// -> Tick과 자신을 소유하는 Actor을 나타냄
class USceneComponent : public UActorComponent
{
public:
	USceneComponent();
	~USceneComponent();

	USceneComponent(const USceneComponent& _Other) = delete;
	USceneComponent(USceneComponent&& _Other) noexcept = delete;
	USceneComponent& operator=(const USceneComponent& _Other) = delete;
	USceneComponent& operator=(USceneComponent&& _Other) noexcept = delete;

	/// <summary>
	/// 자신의 위치를 설정
	/// </summary>
	/// <param name="_Value">위치</param>
	void SetPosition(const FVector& _Value)
	{
		Transform.SetPosition(_Value);
	}

	/// <summary>
	/// 자신의 크기를 설정
	/// </summary>
	/// <param name="_Value">크기</param>
	void SetScale(const FVector & _Value)
	{
		Transform.SetScale(_Value);
	}

	/// <summary>
	/// 위치, 크기 설정
	/// </summary>
	/// <param name="_Value">위치, 크기</param>
	void SetTransform(const FTransform& _Value)
	{
		Transform = _Value;
	}

	/// <summary>
	/// 크기를 반환
	/// </summary>
	/// <returns></returns>
	FTransform GetTransform()
	{
		return Transform;
	}

protected:

private:
	// 위치, 크기
	FTransform Transform;
};

