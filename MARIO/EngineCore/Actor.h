#pragma once

#include <EngineBase/Transform.h>
#include <EngineBase\NameObject.h>

#include "TickObject.h"
#include "ImageRenderer.h"
#include "Level.h"

class ULevel;
class UActorComponent;
class UImageRenderer;

// ���� : ��ġ(FTransform)�� ���� ������Ʈ (��µ� ��ü)
// -> �̸�, ������Ʈ ������� ���� ����
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
	/// ������ ��ġ ��ȯ
	/// </summary>
	/// <returns></returns>
	FVector GetActorLocation()
	{
		return Transform.GetPosition();
	}

	/// <summary>
	/// ������ ��ġ ����
	/// </summary>
	/// <param name="_Value">��ġ</param>
	void SetActorLocation(FVector _Value)
	{
		Transform.SetPosition(_Value);
	}

	/// <summary>
	/// ������ ��ġ �̵�(��ġ ���ϱ�)
	/// </summary>
	/// <param name="_Value">��ġ</param>
	void AddActorLocation(FVector _Value)
	{
		Transform.AddPosition(_Value);
	}

	/// <summary>
	/// ������ ��ġ ��ȯ
	/// </summary>
	/// <returns></returns>
	FTransform GetTransform()
	{
		return Transform;
	}

	/// <summary>
	/// ���Ͱ� ���� ���� ��ȯ
	/// </summary>
	/// <returns></returns>
	ULevel* GetWorld()
	{
		return World;
	}

	/// <summary>
	/// ������ �̹����� �����ϴ� �Լ�
	/// </summary>
	/// <param name="_Order">������ ����</param>
	/// <returns></returns>
	UImageRenderer* CreateImageRenderer(int _Order = 0);

	/// <summary>
	/// ������ �̹��� ����(�ı�)
	/// </summary>
	/// <param name="_DestroyTime"></param>
	void Destroy(float _DestroyTime /*= 0.0f*/) override;

	/// <summary>
	/// ������ �ð��� ������ ������ �̹��� ����(�ı�)
	/// </summary>
	/// <param name="_DeltaTime">�ð�</param>
	void DestroyUpdate(float _DeltaTime) override;

	void ActiveUpdate(float _DeltaTime) override;

protected:
	void Tick(float _DeltaTime) override;

private:
	// ���Ͱ� ������ �ִ� �̹���(���Ϳ� ��Ÿ���� �̹���)
	std::list<UImageRenderer*> Renderers;
	
	// ���Ͱ� �����ϴ� ����
	ULevel* World = nullptr;
	
	// ������ ��ġ
	FTransform Transform;

	/// <summary>
	/// ���Ͱ� �����ϴ� ���� ����
	/// </summary>
	/// <param name="_Value">����</param>
	void SetWorld(ULevel* _Value)
	{
		World = _Value;
	}
};

