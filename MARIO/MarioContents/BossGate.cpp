#include "BossGate.h"

ABossGate::ABossGate()
{
}

ABossGate::~ABossGate()
{
}

void ABossGate::BeginPlay()
{
	AActor::BeginPlay();

	Collision = CreateCollision(ECollisionOrder::Gate);
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetPosition({ 0, 55 });
	Collision->SetScale({ 20, 500 });
}

void ABossGate::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> MarioKoopaGateResult;
	if (true == Collision->CollisionCheck(ECollisionOrder::Player, MarioKoopaGateResult))
	{
		UContentsHelper::IsBossStage = true;
	}
}
