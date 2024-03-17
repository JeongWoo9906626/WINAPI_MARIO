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

	Collision = CreateCollision(ECollisionOrder::Gate);
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
		AMario* Player = static_cast<AMario*>(MarioPosition->GetOwner());

		FTransform MarioCollision = MarioPosition->GetActorBaseTransform();
		FTransform MyTransform = Collision->GetActorBaseTransform();

		Player->Renderer->ActiveOff();
		Player->IsStageEnd = true;
		Player->StateChange(EPlayState::Ending);

		TimeToScore(_DeltaTime);
	}
}

void AGate::TimeToScore(float _DeltaTime)
{
	if (UContentsHelper::Time <= 1000)
	{
		UContentsHelper::Time = 1000;
		StageChange();
		return;
	}

	if (Time >= 1.0f && UContentsHelper::Time >= 1000)
	{
		Time = 0.0f;
		if (CurScoreUpSoundTime >= ScoreUpSoundTime)
		{
			CurScoreUpSoundTime = 0.0f;
			SoundPlayer = UEngineSound::SoundPlay("CoinDestroy.wav");
		}
		UContentsHelper::Time--;
		UContentsHelper::Score += 100;
	}
	Time += _DeltaTime * 100;
	CurScoreUpSoundTime += _DeltaTime;
}


void AGate::StageChange()
{
	UContentsHelper::Time = 1300;
	UContentsHelper::SubStage = 4;
	UContentsHelper::KoopaWake = false;
	UContentsHelper::KoopaIsFire = false;
	UContentsHelper::KoopaDie = false;
	UContentsHelper::MapName = "FinalStage";
	GEngine->ChangeLevel("Loading");
	return;
}

