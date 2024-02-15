#include "TitleLogo.h"
#include <EngineCore/EngineCore.h>

ATitleLogo::ATitleLogo() 
{
}

ATitleLogo::~ATitleLogo() 
{
}

void ATitleLogo::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* Renderer = CreateImageRenderer();

	Renderer->SetImage(/*TODO Ÿ��Ʋ �ΰ� ���� �̸�*/"Mario_Title.png");
	// TODO
	// ��ġ ����
	FVector WindowScale = GEngine->MainWindow.GetWindowScale();
	Renderer->SetTransform({ WindowScale.Half2D(), WindowScale });
}

void ATitleLogo::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}

