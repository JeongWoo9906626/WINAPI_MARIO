#pragma once
#include <EngineBase/Transform.h>
#include "ActorComponent.h"

// ���� : ��ġ�� ��Ÿ���� Ŭ����
// -> Tick�� �ڽ��� �����ϴ� Actor�� ��Ÿ��
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
	/// �ڽ��� ��ġ�� ����
	/// </summary>
	/// <param name="_Value">��ġ</param>
	void SetPosition(const FVector& _Value)
	{
		Transform.SetPosition(_Value);
	}

	/// <summary>
	/// �ڽ��� ũ�⸦ ����
	/// </summary>
	/// <param name="_Value">ũ��</param>
	void SetScale(const FVector & _Value)
	{
		Transform.SetScale(_Value);
	}

	/// <summary>
	/// ��ġ, ũ�� ����
	/// </summary>
	/// <param name="_Value">��ġ, ũ��</param>
	void SetTransform(const FTransform& _Value)
	{
		Transform = _Value;
	}

	/// <summary>
	/// ũ�⸦ ��ȯ
	/// </summary>
	/// <returns></returns>
	FTransform GetTransform()
	{
		return Transform;
	}

protected:

private:
	// ��ġ, ũ��
	FTransform Transform;
};

