#include "UI.h"

#include <EnginePlatform\EngineInput.h>
#include <EngineBase\EngineDebug.h>

#include "ContentsHelper.h"

AUI::AUI()
{
}

AUI::~AUI()
{
}

void AUI::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::UI);
	Renderer->SetImage("UIBar.png");

	FVector UIScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ { 296,-136 }, { 1024, 108 } });
	Renderer->CameraEffectOff();
}

void AUI::Tick(float _DeltaTime)
{
}
