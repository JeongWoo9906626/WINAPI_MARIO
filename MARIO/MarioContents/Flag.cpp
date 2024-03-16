#include "Flag.h"
#include "Mario.h"

AFlag::AFlag()
{
}

AFlag::~AFlag()
{
}

void AFlag::BeginPlay()
{
	Renderer = CreateImageRenderer(ERenderOrder::Flag);
	Renderer->SetImage("Flag.png");
	Renderer->SetTransform({ { -33, -440 }, { 128, 128 } });

	FlagCollision = CreateCollision(ECollisionOrder::Flag);
	FlagCollision->SetColType(ECollisionType::Rect);
	FlagCollision->SetPosition({ 0, -230 });
	FlagCollision->SetScale({ 10, 600 });
}

void AFlag::Tick(float _DeltaTime)
{
	std::vector<UCollision*> MarioResult;
	if (true == FlagCollision->CollisionCheck(ECollisionOrder::Player, MarioResult))
	{
		IsFlagCollision = true;
		AMario* Mario = static_cast<AMario*>(MarioResult[0]->GetOwner());
		Mario->StateChange(EPlayState::FinishMove);
		return;
	}

	if (true == IsFlagCollision)
	{
		FlagDown(_DeltaTime);
	}
}

void AFlag::FlagDown(float _DeltaTime)
{
	if (DownRange <= CurDownY)
	{
		IsFlagCollision = false;
		UContentsHelper::IsFlagDown = true;
	}
	
	CurDownY += DownSpeed * _DeltaTime;
	AddActorLocation(FVector::Down * DownSpeed * _DeltaTime);
}
