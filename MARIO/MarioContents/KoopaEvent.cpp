#include "KoopaEvent.h"

AKoopaEvent::AKoopaEvent()
{
}

AKoopaEvent::~AKoopaEvent()
{
}

void AKoopaEvent::BeginPlay()
{
	AActor::BeginPlay();

	Collision = CreateCollision(ECollisionOrder::Gate);
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetTransform({ {0, -120}, {40, 320} });
}

void AKoopaEvent::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> MarioResult;
	if (true == Collision->CollisionCheck(ECollisionOrder::Player, MarioResult))
	{
		UContentsHelper::KoopaWake = true;
	}
}
