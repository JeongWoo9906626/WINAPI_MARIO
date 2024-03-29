#include "Sunflower.h"
#include "Mario.h"
#include "ScoreUI.h"

ASunflower::ASunflower()
{
}

ASunflower::~ASunflower()
{
}

void ASunflower::BeginPlay()
{
	AActor::BeginPlay();

	SoundPlayer = UEngineSound::SoundPlay("MushRoomAndSunflower.wav");

	{
		Renderer = CreateImageRenderer(ERenderOrder::Monster);
		Renderer->SetImage("MarioItem.png");
		Renderer->SetTransform({ { 0, 0 }, { 64 * 1.7f, 64 * 1.7f } });
	}

	{
		Renderer->CreateAnimation("Sunflower", "MarioItem.png", 2, 2, 0.1f, true);
	}

	{
		BodyCollision = CreateCollision(ECollisionOrder::Item);
		BodyCollision->SetColType(ECollisionType::Rect);
		BodyCollision->SetPosition({ 0, -30 });
		BodyCollision->SetScale({ 30, 55 });
	}

	{
		BottomCollision = CreateCollision(ECollisionOrder::Item);
		BottomCollision->SetColType(ECollisionType::Rect);
		BottomCollision->SetPosition({ 0, 0 });
		BottomCollision->SetScale({ 30, 3 });
	}

	Renderer->ChangeAnimation("Sunflower");
	StateChange(EItemState::Spawn);
}

void ASunflower::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> MarioResult;
	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, MarioResult))
	{
		UCollision* MarioPosition = MarioResult[0];
		AMario* Player = static_cast<AMario*>(MarioPosition->GetOwner());

		ScoreUI* Score = GetWorld()->SpawnActor<ScoreUI>(ERenderOrder::UI);
		FVector MonsterLocation = GetActorLocation();
		Score->SetActorLocation(MonsterLocation);
		Score->SetScore(1000);

		Renderer->ActiveOff();
		BodyCollision->ActiveOff();
		Destroy();


		if (EMarioSizeState::Red != Player->SizeState)
		{
			Player->SizeState = EMarioSizeState::Red;
			Player->StateChange(EPlayState::ChangeRed);
			return;
		}
	}

	std::vector<UCollision*> BoxTopResult;
	if (true == BottomCollision->CollisionCheck(ECollisionOrder::BoxTop, BoxTopResult))
	{
		for (UCollision* BoxPosition : BoxTopResult)
		{
			IsBoxCollision = true;
		}
	}
	else
	{
		IsBoxCollision = false;
	}

	StateUpdate(_DeltaTime);
}

void ASunflower::StateChange(EItemState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EItemState::Spawn:
			SpawnStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void ASunflower::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EItemState::Spawn:
		Spawn(_DeltaTime);
		break;
	}
}

void ASunflower::SpawnStart()
{
	DestroyValue = false;
}

void ASunflower::Spawn(float _DeltaTime)
{
	if (false == IsBoxCollision)
	{
		AddActorLocation(FVector::Up * SpawnUpSpeed * _DeltaTime);
	}
}
