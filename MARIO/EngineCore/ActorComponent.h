#pragma once
#include "TickObject.h"

class AActor;

// ���� : ���Ϳ��� �����Ǵ� ���� �˸��� Ŭ����
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
	/// �ڽ��� �����ϴ� ���� ��ȯ
	/// </summary>
	/// <returns></returns>
	AActor* GetOwner()
	{
		return Owner;
	}

protected:

private:
	// �ڽ��� �����ϴ� ����
	AActor* Owner = nullptr;

	/// <summary>
	/// �ڽ��� �����ϴ� ���� ����
	/// </summary>
	/// <param name="_Owner"></param>
	void SetOwner(AActor* _Owner)
	{
		Owner = _Owner;
	}
};

