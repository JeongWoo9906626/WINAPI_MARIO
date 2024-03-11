#include "EndingGate.h"
#include "Mario.h"

AEndingGate::AEndingGate()
{
}

AEndingGate::~AEndingGate()
{
}

void AEndingGate::BeginPlay()
{
	AActor::BeginPlay();

	Collision = CreateCollision(ECollisionOrder::HiddenCoin);
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetPosition({ 0, -30 });
	Collision->SetScale({ 65, 70 });
}

void AEndingGate::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> Result;
	if (true == Collision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		UCollision* MarioPosition = Result[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();
		
		Player->StateChange(EPlayState::Ending);


		if (CurChangeLevelTime >= ChangeLevelTime)
		{
			GEngine->ChangeLevel("Title");
			return;
		}
		CurChangeLevelTime += _DeltaTime;
	}
}
