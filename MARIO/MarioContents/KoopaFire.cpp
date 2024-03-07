#include "KoopaFire.h"

AKoopaFire::AKoopaFire()
{
}

AKoopaFire::~AKoopaFire()
{
}

void AKoopaFire::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Fire);
	Renderer->SetImage("Koopa_Left.png");
	Renderer->SetTransform({ {0, 0}, {512, 512} });

	Renderer->CreateAnimation("KoopaFire", "Koopa_Left.png", 6, 7, 0.1f, true);
	Renderer->ChangeAnimation("KoopaFire");

	Collision = CreateCollision(ECollisionOrder::Goomba);
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetTransform({ {0, -20}, {90, 35} });
}

void AKoopaFire::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
