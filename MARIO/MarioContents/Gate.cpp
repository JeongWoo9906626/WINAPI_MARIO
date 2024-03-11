#include "Gate.h"
#include "Mario.h"
#include "FinalLevel.h"

AGate::AGate()
{
}

AGate::~AGate()
{
}

void AGate::BeginPlay()
{
	AActor::BeginPlay();

	Collision = CreateCollision(ECollisionOrder::HiddenCoin);
	Collision->SetColType(ECollisionType::Rect);
	Collision->SetPosition({ 0, -30 });
	Collision->SetScale({ 65, 70 });
}

void AGate::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> Result;
	if (true == Collision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		UCollision* MarioPosition = Result[0];
		AMario* Player = (AMario*)MarioPosition->GetOwner();

		FTransform MarioCollision = MarioPosition->GetActorBaseTransform();
		FTransform MyTransform = Collision->GetActorBaseTransform();

		Player->Renderer->ActiveOff();
		Player->IsStageEnd = true;
		Player->StateChange(EPlayState::Ending);

		if (CurChangeLevelTime >= ChangeLevelTime)
		{
			UContentsHelper::Time = 1400;
			GEngine->CreateLevel<UFinalLevel>("Final");
			GEngine->ChangeLevel("Final");
			return;
		}
		CurChangeLevelTime += _DeltaTime;
	}
}