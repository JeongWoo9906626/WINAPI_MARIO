#include "BackGround.h"

#include <EngineCore\EngineResourcesManager.h>

#include "ContentsHelper.h"

ABackGround::ABackGround()
{
}

ABackGround::~ABackGround()
{
}

void ABackGround::SetMapImage(std::string_view _MapImageName)
{
	Renderer->SetImage(_MapImageName);
	UWindowImage* Image = Renderer->GetImage();
	FVector ImageScale = Image->GetScale();
	Renderer->SetTransform({ ImageScale.Half2D(), ImageScale });
}

void ABackGround::SetColMapImage(std::string_view _MapImageName)
{
	CollisionRenderer->SetImage(_MapImageName);
	UWindowImage* Image = CollisionRenderer->GetImage();
	UContentsHelper::MapColImage = Image;
	FVector ImageScale = Image->GetScale();
	CollisionRenderer->SetTransform({ ImageScale.Half2D(), ImageScale });
}

void ABackGround::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);



	if (UEngineInput::IsDown('O'))
	{
		SwitchDebug();
	}
}


void ABackGround::SwitchDebug()
{
	if (true == Renderer->IsActive())
	{
		Renderer->SetActive(false);
		CollisionRenderer->SetActive(true);
	}
	else
	{
		Renderer->SetActive(true);
		CollisionRenderer->SetActive(false);
	}

}
void ABackGround::BeginPlay()
{
	Renderer = CreateImageRenderer(RenderOrder::Map);
	CollisionRenderer = CreateImageRenderer(RenderOrder::Map);
	CollisionRenderer->SetActive(false);
}