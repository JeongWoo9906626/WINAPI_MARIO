#pragma once
#include "TickObject.h"

class AActor;

// 설명 : 액터에게 소유되는 것을 알리는 클래스
class UActorComponent : public UTickObject
{
	friend AActor;

public:
	UActorComponent();
	~UActorComponent();

	UActorComponent(const UActorComponent& _Other) = delete;
	UActorComponent(UActorComponent&& _Other) noexcept = delete;
	UActorComponent& operator=(const UActorComponent& _Other) = delete;
	UActorComponent& operator=(UActorComponent&& _Other) noexcept = delete;

	/// <summary>
	/// 자신을 소유하는 액터 반환
	/// </summary>
	/// <returns></returns>
	AActor* GetOwner()
	{
		return Owner;
	}

protected:

private:
	// 자신을 소유하는 액터
	AActor* Owner = nullptr;

	/// <summary>
	/// 자신을 소유하는 액터 설정
	/// </summary>
	/// <param name="_Owner"></param>
	void SetOwner(AActor* _Owner)
	{
		Owner = _Owner;
	}
};

