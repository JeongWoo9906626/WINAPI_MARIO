#include "ImageRenderer.h"
#include "EngineCore.h"
#include "Actor.h"
#include "Level.h"
#include <EngineCore\EngineResourcesManager.h>

UImageRenderer::UImageRenderer()
{
}

UImageRenderer::~UImageRenderer()
{
}

void UImageRenderer::SetOrder(int _Order)
{
	AActor* Owner = GetOwner();
	ULevel* Level = Owner->GetWorld();

	std::map<int, std::list<UImageRenderer*>>& Renderers = Level->Renderers;
	Renderers[GetOrder()].remove(this);
	
	UTickObject::SetOrder(_Order);
	Renderers[GetOrder()].push_back(this);
}

void UImageRenderer::Render(float _DeltaTime)
{
	if (nullptr == Image)
	{
		MsgBoxAssert("�̹����� �������� �ʴ� ������ �Դϴ�");
	}

	// �������� ��ġ
	FTransform ThisTrans = GetTransform();
	// ������ ��ġ(�θ�)
	FTransform OwnerTrans = GetOwner()->GetTransform();

	// ������Ʈ�� ��ġ�� �θ𿡰Լ� �����
	// ��½ÿ��� �θ��� ��ġ�� ������� �Ѵ�.
	ThisTrans.AddPosition(OwnerTrans.GetPosition());

	GEngine->MainWindow.GetWindowImage()->TransCopy(Image, ThisTrans, ImageCuttingTransform);
}

void UImageRenderer::BeginPlay()
{
	USceneComponent::BeginPlay();
}

void UImageRenderer::SetImage(std::string_view _Name)
{
	// �̹��� ����
	Image = UEngineResourcesManager::GetInst().FindImg(_Name);

	// ���� �ߴµ� �̹����� ���� ���
	if (nullptr == Image)
	{
		MsgBoxAssert(std::string(_Name) + "�̹����� �������� �ʽ��ϴ�.");
		return;
	}
}