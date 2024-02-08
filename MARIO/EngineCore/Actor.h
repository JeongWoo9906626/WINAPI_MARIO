#pragma once

#include <EngineBase/Transform.h>
#include <EngineBase\NameObject.h>

#include "TickObject.h"
#include "ImageRenderer.h"
#include "Level.h"

class ULevel;
class UActorComponent;
class UImageRenderer;

// 설명 : 위치(FTransform)를 가진 오브젝트 (출력될 객체)
// -> 이름, 업데이트 상속으로 가진 상태
class AActor : public UNameObject, public UTickObject
{
	friend ULevel;

public:
	AActor();
	~AActor();

	AActor(const AActor& _Other) = delete;
	AActor(AActor&& _Other) noexcept = delete;
	AActor& operator=(const AActor& _Other) = delete;
	AActor& operator=(AActor&& _Other) noexcept = delete;

	/// <summary>
	/// 액터의 위치 반환
	/// </summary>
	/// <returns></returns>
	FVector GetActorLocation()
	{
		return Transform.GetPosition();
	}

	/// <summary>
	/// 액터의 위치 설정
	/// </summary>
	/// <param name="_Value">위치</param>
	void SetActorLocation(FVector _Value)
	{
		Transform.SetPosition(_Value);
	}

	/// <summary>
	/// 액터의 위치 이동(위치 더하기)
	/// </summary>
	/// <param name="_Value">위치</param>
	void AddActorLocation(FVector _Value)
	{
		Transform.AddPosition(_Value);
	}

	/// <summary>
	/// 액터의 위치 반환
	/// </summary>
	/// <returns></returns>
	FTransform GetTransform()
	{
		return Transform;
	}

	/// <summary>
	/// 액터가 속한 레벨 반환
	/// </summary>
	/// <returns></returns>
	ULevel* GetWorld()
	{
		return World;
	}

	/// <summary>
	/// 랜더링 이미지를 생성하는 함수
	/// </summary>
	/// <param name="_Order">랜더링 순서</param>
	/// <returns></returns>
	UImageRenderer* CreateImageRenderer(int _Order = 0);

	/// <summary>
	/// 렌더링 이미지 삭제(파괴)
	/// </summary>
	/// <param name="_DestroyTime"></param>
	void Destroy(float _DestroyTime /*= 0.0f*/) override;

	/// <summary>
	/// 지정한 시간이 지나면 렌더링 이미지 삭제(파괴)
	/// </summary>
	/// <param name="_DeltaTime">시간</param>
	void DestroyUpdate(float _DeltaTime) override;

	void ActiveUpdate(float _DeltaTime) override;

protected:
	void Tick(float _DeltaTime) override;

private:
	// 액터가 가지고 있는 이미지(액터에 나타나는 이미지)
	std::list<UImageRenderer*> Renderers;
	
	// 액터가 존재하는 레벨
	ULevel* World = nullptr;
	
	// 액터의 위치
	FTransform Transform;

	/// <summary>
	/// 액터가 존재하는 레벨 설정
	/// </summary>
	/// <param name="_Value">레벨</param>
	void SetWorld(ULevel* _Value)
	{
		World = _Value;
	}
};

