#include "StartMapLogo.h"
#include <EngineCore/EngineCore.h>

AStartMapLogo::AStartMapLogo()
{
}

AStartMapLogo::~AStartMapLogo()
{
}

void AStartMapLogo::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* Renderer = CreateImageRenderer();
	
	Renderer->SetImage("Mario_Title.png");
	SetActorLocation({ 0, 0 });
	Renderer->SetTransform({ GEngine->MainWindow.GetWindowScale().Half2D(), GEngine->MainWindow.GetWindowScale() });
	Renderer->SetImageCuttingTransform({ {0,0}, {200, 200} });
}

void AStartMapLogo::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}