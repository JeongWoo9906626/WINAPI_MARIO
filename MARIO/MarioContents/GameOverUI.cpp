#include "GameOverUI.h"

AGameOverUI::AGameOverUI()
{
}

AGameOverUI::~AGameOverUI()
{
}

void AGameOverUI::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Loading);
	Renderer->SetImage("GameOver.png");
	Renderer->SetTransform({ {0, 0}, {GEngine->MainWindow.GetWindowScale()} });
	Renderer->CameraEffectOff();
}

void AGameOverUI::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
