#include "StartMapLogo.h"

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

	Renderer->SetImage("Title.png");
	SetActorLocation({ 50, 50 });
	Renderer->SetTransform({ {50,50}, {100, 100} });
	Renderer->SetImageCuttingTransform({ {0,0}, {200, 200} });
}

void AStartMapLogo::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}