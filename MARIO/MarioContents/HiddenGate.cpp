#include "HiddenGate.h"

AHiddenGate::AHiddenGate()
{
}

AHiddenGate::~AHiddenGate()
{
}

void AHiddenGate::BeginPlay()
{
	AActor::BeginPlay();

	BodyCollision = CreateCollision(ECollisionOrder::Box);
	BodyCollision->SetColType(ECollisionType::Rect);
	BodyCollision->SetPosition({ 0, 0 });
	BodyCollision->SetScale({ 60, 10 });
}

void AHiddenGate::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	/*std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		UCollision* MarioPosition = Result[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();

		FTransform MarioCollision = MarioPosition->GetActorBaseTransform();
		FTransform MyTransform = BodyCollision->GetActorBaseTransform();

		Player->Renderer->ActiveOff();
		if (CurChangeLevelTime >= ChangeLevelTime)
		{
			GEngine->ChangeLevel(StageName);
		}
		CurChangeLevelTime += _DeltaTime;
	}*/
}
