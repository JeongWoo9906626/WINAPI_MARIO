#include "Plant.h"

APlant::APlant()
{
}

APlant::~APlant()
{
}

void APlant::BeginPlay()
{
	AActor::BeginPlay();

	{
		Renderer = CreateImageRenderer(ERenderOrder::Monster);
		Renderer->SetImage("Plant.png");
		Renderer->SetTransform({ { 0, 0 }, { 256 * 3.0f, 256 * 3.0f } });
	}

	{
		Renderer->CreateAnimation("PlantIdle", "Plant.png", 0, 1, 0.2f, true);
	}

	{
		BodyCollision = CreateCollision(ECollisionOrder::Monster);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetPosition({ 0, -30 });
		BodyCollision->SetScale({ 40, 40 });
	}
	Renderer->ChangeAnimation("PlantIdle");
}

void APlant::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);


}
