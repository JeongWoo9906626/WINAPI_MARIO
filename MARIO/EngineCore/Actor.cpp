#include "Actor.h"

AActor::AActor()
{
}

/// <summary>
/// ���Ͱ� ����� �� ������(�̹���)�� ���� �Ҹ�
/// </summary>
AActor::~AActor()
{
	for (UImageRenderer* ImageRenderer : Renderers)
	{
		if (nullptr == ImageRenderer)
		{
			MsgBoxAssert("�̹��� �������� nullptr�� ��Ȳ�� �־����ϴ�");
		}

		delete ImageRenderer;
		ImageRenderer = nullptr;
	}

	Renderers.clear();
}

UImageRenderer* AActor::CreateImageRenderer(int _Order)
{
	UImageRenderer* NewRenderer = new UImageRenderer();
	UActorComponent* ActorCom = NewRenderer;

	// ���� ����
	ActorCom->SetOwner(this);
	// ������ ���� ����
	ActorCom->SetOrder(_Order);
	// �̹��� �����Ǹ� �� ��(�ʱ� ����?)
	ActorCom->BeginPlay();

	// ������ ��ü�� ������ �ִ� ������ ����Ʈ�� �߰�
	Renderers.push_back(NewRenderer);

	return NewRenderer;
}

void AActor::Destroy(float _DestroyTime /*= 0.0f*/)
{
	UTickObject::Destroy(_DestroyTime);
	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->Destroy(_DestroyTime);
	}
}

void AActor::DestroyUpdate(float _DeltaTime)
{
	UTickObject::DestroyUpdate(_DeltaTime);
	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->DestroyUpdate(_DeltaTime);
	}
}

void AActor::ActiveUpdate(float _DeltaTime)
{
	UTickObject::ActiveUpdate(_DeltaTime);
	for (UImageRenderer* Renderer : Renderers)
	{
		Renderer->ActiveUpdate(_DeltaTime);
	}
}

void AActor::Tick(float _DeltaTime)
{
	UTickObject::Tick(_DeltaTime);
}
