#include "BrickBase.h"
#include "Mario.h"

ABrickBase::ABrickBase()
{
}

ABrickBase::~ABrickBase()
{
}

void ABrickBase::BeginPlay()
{
}

void ABrickBase::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	std::vector<UCollision*> BottomResult;
	if (true == BottomCollision->CollisionCheck(ECollisionOrder::PlayerHead, BottomResult))
	{
		UCollision* MarioPosition = BottomResult[0];
		AMario* Player = static_cast<AMario*>(MarioPosition->GetOwner());

		if (EBoxState::Idle == State)
		{
			MarioState = Player->SizeState;
			Player->JumpVector = FVector::Zero;
			//Player->AddActorLocation(FVector::Down * 10);
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

void ABrickBase::StateChange(EBoxState _State)
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

void ABrickBase::StateUpdate(float _DeltaTime)
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

void ABrickBase::IdleStart()
{
	MoveUpPos = FVector::Zero;
	MoveDownPos = FVector::Zero;
}

void ABrickBase::HitStart()
{
	SoundPlayer = UEngineSound::SoundPlay("MarioFireAndBrickBlock.wav");
	FirstPos = GetActorLocation();
}

void ABrickBase::BreakStart()
{
}

void ABrickBase::Idle(float _DeltaTime)
{
}

void ABrickBase::Hit(float _DeltaTime)
{
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

void ABrickBase::Break(float _DeltaTime)
{
}
