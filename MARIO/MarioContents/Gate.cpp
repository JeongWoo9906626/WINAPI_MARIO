#include "Gate.h"
#include "Mario.h"

AGate::AGate()
{
}

AGate::~AGate()
{
}

void AGate::BeginPlay()
{
	AActor::BeginPlay();

	BodyCollision = CreateCollision(ECollisionOrder::Box);
	BodyCollision->SetColType(ECollisionType::Rect);
	BodyCollision->SetPosition({ 0, -30 });
	BodyCollision->SetScale({ 65, 70 });
}

void AGate::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> Result;
	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		UCollision* MarioPosition = Result[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();

		FTransform MarioCollision = MarioPosition->GetActorBaseTransform();
		FTransform MyTransform = BodyCollision->GetActorBaseTransform();

		Player->Renderer->ActiveOff();
		if (CurChangeLevelTime >= ChangeLevelTime)
		{
			GEngine->ChangeLevel("Title");
		}
		CurChangeLevelTime += _DeltaTime;
	}
}