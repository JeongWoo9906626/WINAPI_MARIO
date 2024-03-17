#include "BreakBrick.h"
#include "Mario.h"
#include "BreakOne.h"

ABreakBrick::ABreakBrick()
{
}

ABreakBrick::~ABreakBrick()
{
	ABreakOne* LeftTop = GetWorld()->SpawnActor<ABreakOne>(ERenderOrder::BreakOne);
	LeftTop->SetActorLocation(GetActorLocation() + (FVector::Up * 40.0f) + (FVector::Left * 20.0f));
	LeftTop->SetName("Left");

	ABreakOne* LeftBottom = GetWorld()->SpawnActor<ABreakOne>(ERenderOrder::BreakOne);
	LeftBottom->SetActorLocation(GetActorLocation()/* + (FVector::Down * 20.0f)*/ + (FVector::Left * 20.0f));
	LeftBottom->SetName("Left");

	ABreakOne* RightTop = GetWorld()->SpawnActor<ABreakOne>(ERenderOrder::BreakOne);
	RightTop->SetActorLocation(GetActorLocation() + (FVector::Up * 40.0f) + (FVector::Right * 20.0f));
	RightTop->SetName("Right");
	
	ABreakOne* RightBottom = GetWorld()->SpawnActor<ABreakOne>(ERenderOrder::BreakOne);
	RightBottom->SetActorLocation(GetActorLocation()/* + (FVector::Down * 20.0f)*/ + (FVector::Right * 20.0f));
	RightBottom->SetName("Right");
}

void ABreakBrick::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(ERenderOrder::Brick);
	Renderer->SetImage("OpenWorldBrick.png");
	Renderer->SetTransform({ { 0, 0 }, { 256, 256 } });

	Renderer->CreateAnimation("BrickIdle", "OpenWorldBrick.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("BrickHit", "OpenWorldBrick.png", 0, 0, 0.1f, true);

	LeftCollision = CreateCollision(ECollisionOrder::Box);
	LeftCollision->SetColType(ECollisionType::Rect);
	LeftCollision->SetPosition({ -28, -28 });
	LeftCollision->SetScale({ 10, 55 });

	RightCollision = CreateCollision(ECollisionOrder::Box);
	RightCollision->SetColType(ECollisionType::Rect);
	RightCollision->SetPosition({ +28, -28 });
	RightCollision->SetScale({ 10, 55 });

	TopCollision = CreateCollision(ECollisionOrder::BoxTop);
	TopCollision->SetColType(ECollisionType::Rect);
	TopCollision->SetPosition({ 0, -60 });
	TopCollision->SetScale({ 64, 10 });

	BottomCollision = CreateCollision(ECollisionOrder::Box);
	BottomCollision->SetColType(ECollisionType::Rect);
	BottomCollision->SetPosition({ 0, -5 });
	BottomCollision->SetScale({ 60, 10 });


	StateChange(EBoxState::Idle);
}

void ABreakBrick::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> BottomResult;
	if (true == BottomCollision->CollisionCheck(ECollisionOrder::PlayerHead, BottomResult))
	{
		UCollision* MarioPosition = BottomResult[0];
		AMario* Player = static_cast<AMario*>(MarioPosition->GetOwner());
		MarioState = Player->SizeState;

		if (EBoxState::Idle == State)
		{
			Player->JumpVector = FVector::Zero;
			Player->AddActorLocation(FVector::Down * 10);
  			StateChange(EBoxState::Hit);
			return;
		}
	}

	std::vector<UCollision*> LeftResult;
	if (true == LeftCollision->CollisionCheck(ECollisionOrder::Player, LeftResult))
	{
		UCollision* MarioPosition = LeftResult[0];
		AMario* Player = static_cast<AMario*>(MarioPosition->GetOwner());

		Player->MoveVector.X = 0.0f;
		Player->AddActorLocation(FVector::Left);
		return;
	}

	std::vector<UCollision*> RightResult;
	if (true == RightCollision->CollisionCheck(ECollisionOrder::Player, RightResult))
	{
		UCollision* MarioPosition = RightResult[0];
		AMario* Player = static_cast<AMario*>(MarioPosition->GetOwner());

		Player->MoveVector.X = 0.0f;
		Player->AddActorLocation(FVector::Right);
		return;
	}

	StateUpdate(_DeltaTime);
}

void ABreakBrick::StateChange(EBoxState _State)
{
	if (State != _State)
	{
		switch (_State)
		{
		case EBoxState::Idle:
			IdleStart();
			break;
		case EBoxState::Hit:
			HitStart();
			break;
		case EBoxState::Break:
			BreakStart();
			break;
		default:
			break;
		}
	}

	State = _State;
}

void ABreakBrick::StateUpdate(float _DeltaTime)
{
	switch (State)
	{
	case EBoxState::Idle:
		Idle(_DeltaTime);
		break;
	case EBoxState::Hit:
		Hit(_DeltaTime);
		break;
	case EBoxState::Break:
		Break(_DeltaTime);
		break;
	default:
		break;
	}
}

void ABreakBrick::IdleStart()
{
	MoveUpPos = FVector::Zero;
	MoveDownPos = FVector::Zero;
	Renderer->ChangeAnimation("BrickIdle");
}

void ABreakBrick::HitStart()
{
	SoundPlayer = UEngineSound::SoundPlay("MarioFireAndBrickBlock.wav");
	FirstPos = GetActorLocation();
	Renderer->ChangeAnimation("BrickHit");
}

void ABreakBrick::BreakStart()
{
	SoundPlayer = UEngineSound::SoundPlay("BrickBreak.wav");
	Renderer->ActiveOff();

	TopCollision->ActiveOff();
	BottomCollision->ActiveOff();
	LeftCollision->ActiveOff();
	RightCollision->ActiveOff();
}

void ABreakBrick::Idle(float _DeltaTime)
{
}

void ABreakBrick::Hit(float _DeltaTime)
{
	if (EMarioSizeState::Small != MarioState)
	{
		StateChange(EBoxState::Break);
		return;
	}

	if (abs(MoveUpPos.Y) >= MaxHitUpSize)
	{
		if (abs(MoveDownPos.Y) >= MaxHitUpSize)
		{
			SetActorLocation(FirstPos);
			StateChange(EBoxState::Idle);
			return;
		}
		else
		{
			MoveDownPos += FVector::Down * HitUpSpeed * _DeltaTime;
			AddActorLocation(FVector::Down * HitUpSpeed * _DeltaTime);
		}
	}
	else
	{
		MoveUpPos += FVector::Up * HitUpSpeed * _DeltaTime;
		AddActorLocation(FVector::Up * HitUpSpeed * _DeltaTime);
	}
}

void ABreakBrick::Break(float _DeltaTime)
{
	Destroy();
}